#ifndef ANASEM
#define ANASEM

#include "analex.h"
#include "anasin.h"
#include "GerenciadorTS.h"
#include <stdbool.h>



void verificaIDGlobalDuplicado(int id);
void erroSem(char * string);


void verificaIDGlobalDuplicado(int id){
    int i;
    for(i=0;i<topo_tabela_de_simbolos;i++){
        if(i != id){
            if(
                !strcmp(tabela_de_simbolos[i].nome, tabela_de_simbolos[id].nome) &&
                tabela_de_simbolos[i].escopo == escopoTS_global &&
                (
                    tabela_de_simbolos[i].categoria != categoriaTS_prototipo ||
                    tabela_de_simbolos[id].categoria != categoriaTS_funcao
                )
            ){
                erroSem("Redefinição de variável global ou função");
            }
        }
    }

}

void verificaIDLocalDuplicado(int id_inicio, int id){
    int i;
    printf("------------------------------------inicio: %d\n",id_inicio);
    for(i=id_inicio;i<topo_tabela_de_simbolos;i++){
        if(i != id && !tabela_de_simbolos[i].sem_nome){
            if(
                !strcmp(tabela_de_simbolos[i].nome, tabela_de_simbolos[id].nome) &&
                tabela_de_simbolos[i].escopo == escopoTS_local
            ){
                erroSem("Redefinição de variável local ou Parametro duplicado");
            }
        }
    }
}

void verificaExistenciaDaFuncao(char * nomeFunc){
    int i;
    bool encontrado = false;
    // printf(">>>>>>>>>>>>>>>>>>>>>.%s\n",nomeFunc);

    for(i=0;i<topo_tabela_de_simbolos;i++){
        if(
            !strcmp(tabela_de_simbolos[i].nome, nomeFunc) &&
            (
                tabela_de_simbolos[i].categoria == categoriaTS_funcao ||
                tabela_de_simbolos[i].categoria == categoriaTS_prototipo
            )   
        ){
            encontrado = true;
        }
    }
    if(!encontrado){
         erroSem("Função indefinida");
    }


}

int verificaTipoTabelaDeSimbolos(char * nome){
    int i;
    int id_local_encontrado = -1;
    int id_global_encontrado = -1;
    for(i=0;i<topo_tabela_de_simbolos;i++){
        if(!strcmp(tabela_de_simbolos[i].nome, nome)){
            if(tabela_de_simbolos[i].escopo == escopoTS_global){
                id_global_encontrado = i;
            }else{
                id_local_encontrado = i;
            }
        }
    }

    if( id_local_encontrado != -1 ){
        return tabela_de_simbolos[id_local_encontrado].tipo;
    }else if (id_global_encontrado != -1){
        return tabela_de_simbolos[id_global_encontrado].tipo;
    }else{
        erroSem("Referencia ao Identificador não encontrada");
    }
}

int verificaPosicaoTabelaDeSimbolos(char * nome){
    int i;
    int id_local_encontrado = -1;
    int id_global_encontrado = -1;
    for(i=0;i<topo_tabela_de_simbolos;i++){
        if(!strcmp(tabela_de_simbolos[i].nome, nome)){
            if(tabela_de_simbolos[i].escopo == escopoTS_global){
                id_global_encontrado = i;
            }else{
                id_local_encontrado = i;
            }
        }
    }

    if( id_local_encontrado != -1 ){
        return id_local_encontrado;
    }else if (id_global_encontrado != -1){
        return id_global_encontrado;
    }else{
        erroSem("Referencia ao Identificador não encontrada");
    }
}

void verificadorDeTipos(token token,int num_param){
    int tipo;
    printf("---------> %d\n",id_funcao_atual+num_param);
    mostraTabela();
    switch(token.categoria){
        case CAT_id:
            printf("********************************ID\n");
            tipo = verificaTipoTabelaDeSimbolos(ID_TABLE[token.codigo]);
            printf("%s :: %s | ",ID_TABLE[token.codigo],tabela_de_simbolos[id_funcao_atual].nome);
            printf("%s == %s?\n",tipoTS_nomes[tipo],tipoTS_nomes[tabela_de_simbolos[id_funcao_atual+num_param].tipo]);
            if(
                tipo == tabela_de_simbolos[id_funcao_atual+num_param].tipo &&
                (
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro ||
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro_prototipo 
                )
            );
            else{
                if(
                    (
                        tipo == tipoTS_inteiro && tabela_de_simbolos[id_funcao_atual+num_param].tipo == tipoTS_caracter ||
                        tipo == tipoTS_caracter && tabela_de_simbolos[id_funcao_atual+num_param].tipo == tipoTS_inteiro
                    ) ||
                        tipo == tipoTS_inteiro && tabela_de_simbolos[id_funcao_atual+num_param].tipo == tipoTS_booleano
                ) break;
                erroSem("Tipo incompativel na chamada da função");
            }
            break;
        case CAT_constanteInteira:
            printf("********************************CI\n");
            if(
                tipoTS_inteiro == tabela_de_simbolos[id_funcao_atual+num_param].tipo  ||
                tipoTS_caracter == tabela_de_simbolos[id_funcao_atual+num_param].tipo ||
                tipoTS_booleano == tabela_de_simbolos[id_funcao_atual+num_param].tipo &&
                (
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro ||
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro_prototipo 
                )
            );
            else erroSem("Tipo incompativel na chamada da função");
            break;
        case CAT_constanteReal:
            printf("********************************CR\n");
            if(
                tipoTS_real == tabela_de_simbolos[id_funcao_atual+num_param].tipo &&
                (
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro ||
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro_prototipo 
                )
            );
            else erroSem("Tipo incompativel na chamada da função");
            break;
        case CAT_constanteCaracter:
            printf("********************************CC\n");
            if(
                tipoTS_caracter == tabela_de_simbolos[id_funcao_atual+num_param].tipo ||
                tipoTS_inteiro == tabela_de_simbolos[id_funcao_atual+num_param].tipo  &&
                (
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro ||
                    tabela_de_simbolos[id_funcao_atual+num_param].categoria == categoriaTS_parametro_prototipo 
                )
            );
            else erroSem("Tipo incompativel na chamada da função");
            break;
    }
}

void verificaQuantidadeDeParametros(int num_param){
    int i,contParam = 0;
    i = id_funcao_atual;
    while(
            tabela_de_simbolos[i+1].categoria == categoriaTS_parametro ||
            tabela_de_simbolos[i+1].categoria == categoriaTS_parametro_prototipo
        ){
        printf("verificando %d...\n",i);
        i++;
        contParam++;
    }
    if(contParam != num_param){
        erroSem("Quantidade de parametros incorreta em chamada de função");
    }
}



int id_corpo_de_funcao_atual(){
    int i = topo_tabela_de_simbolos;
    do{
        i--;
    }while(tabela_de_simbolos[i].categoria != categoriaTS_funcao);
    return i;
} 

void trocaTipo(int novoTipo){
    switch(tipoAtualUtilizado){
        case -1:
            tipoAtualUtilizado = novoTipo;
            printf(">>>Definindo primeiro tipo como %s\n",tipoTS_nomes[novoTipo]);
            break;
        case tipoTS_booleano:
            if(
                novoTipo == tipoTS_booleano ||
                novoTipo == tipoTS_inteiro
            ){
                printf(">>>Troca de tipo %s -> %s\n",tipoTS_nomes[tipoAtualUtilizado],tipoTS_nomes[novoTipo]);
            }else erroSem("Expresão composta de tipos incompativeis");
            break;
        case tipoTS_caracter:
            if(
                novoTipo == tipoTS_caracter ||
                novoTipo == tipoTS_inteiro
            ){
                printf(">>>Troca de tipo %s -> %s\n",tipoTS_nomes[tipoAtualUtilizado],tipoTS_nomes[novoTipo]);
            }else erroSem("Expresão composta de tipos incompativeis");
            break;
        case tipoTS_inteiro:
            if(
                novoTipo == tipoTS_inteiro ||
                novoTipo == tipoTS_caracter
            ){
                printf(">>>Troca de tipo %s -> %s\n",tipoTS_nomes[tipoAtualUtilizado],tipoTS_nomes[novoTipo]);
            }else erroSem("Expresão composta de tipos incompativeis");
            break;
        case tipoTS_real:
            if(
                novoTipo == tipoTS_real
            ){
                printf(">>>Troca de tipo %s -> %s\n",tipoTS_nomes[tipoAtualUtilizado],tipoTS_nomes[novoTipo]);
            }else erroSem("Expresão composta de tipos incompativeis");
            break;
    }
}



void erroSem(char * string){
    printf("Erro Semântico: %s\n", string);
    exit(1);
}

#endif
