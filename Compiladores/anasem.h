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
    for(i=id_inicio;i<topo_tabela_de_simbolos;i++){
        if(i != id && !tabela_de_simbolos[i].sem_nome){
            if(
                !strcmp(tabela_de_simbolos[i].nome, tabela_de_simbolos[id].nome) &&
                tabela_de_simbolos[i].escopo == escopoTS_local &&
                tabela_de_simbolos[i].zumbi == false
            ){
                erroSem("Redefinição de variável local ou Parametro duplicado");
            }
        }
    }
}

void verificaExistenciaDaFuncao(char * nomeFunc){
    int i;
    bool encontrado = false;

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
            }else if(tabela_de_simbolos[i].zumbi == false){
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
            }else if(tabela_de_simbolos[i].zumbi == false){
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
    // mostraTabela();
    switch(token.categoria){
        case CAT_id:
            tipo = verificaTipoTabelaDeSimbolos(ID_TABLE[token.codigo]);
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
                        tipo == tipoTS_inteiro && tabela_de_simbolos[id_funcao_atual+num_param].tipo == tipoTS_inteiro ||
                        tipo == tipoTS_caracter && tabela_de_simbolos[id_funcao_atual+num_param].tipo == tipoTS_caracter
                    ) ||
                        tipo == tipoTS_inteiro && tabela_de_simbolos[id_funcao_atual+num_param].tipo == tipoTS_booleano
                ) break;
                
                erroSem("Tipo incompativel na chamada da função");
            }
            break;
        case CAT_constanteInteira:
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
            break;
        case tipoTS_booleano:
            if(
                novoTipo == tipoTS_booleano ||
                novoTipo == tipoTS_inteiro
            ){
            }else{
                erroSem("Expresão composta de tipos incompativeis");
            }
            break;
        case tipoTS_caracter:
            if(
                novoTipo == tipoTS_caracter ||
                novoTipo == tipoTS_inteiro
            ){
            }else{
                erroSem("Expresão composta de tipos incompativeis");
            }break;
        case tipoTS_inteiro:
            if(
                novoTipo == tipoTS_inteiro ||
                novoTipo == tipoTS_caracter
            ){
            }else{
                erroSem("Expresão composta de tipos incompativeis");
            }break;
        case tipoTS_real:
            if(
                novoTipo == tipoTS_real
            ){
            }else{
                erroSem("Expresão composta de tipos incompativeis");
            }break;
    }
}

void verificaTipoDeRetorno(){
    switch(tabela_de_simbolos[id_corpo_de_funcao_atual()].tipo){
        case tipoTS_semretorno:

            if(
                tipoAtualUtilizado == -1
            ){
            }else{
                erroSem("tipo de retorno incompativel, Essa função não pode retornar valores");
            }
            break;

        case tipoTS_inteiro:
            if(
                tipoAtualUtilizado == tipoTS_inteiro ||
                tipoAtualUtilizado == tipoTS_caracter
            ){
            }else{
                erroSem("tipo de retorno incompativel, Esperado inteiro ou caracter");
            }
            break;
        case tipoTS_real:
            if(
                tipoAtualUtilizado == tipoTS_real
            ){
            }else{
                erroSem("tipo de retorno incompativel, Esperado real");
            }
            break;
        case tipoTS_caracter:
            if(
                tipoAtualUtilizado == tipoTS_caracter ||
                tipoAtualUtilizado == tipoTS_inteiro
            ){
            }else{
                erroSem("tipo de retorno incompativel, Esperado caracter ou inteiro");
            }
            break;
        case tipoTS_booleano:
            if(
                tipoAtualUtilizado == tipoTS_booleano ||
                tipoAtualUtilizado == tipoTS_inteiro
            ){
            }else{
                erroSem("tipo de retorno incompativel, Esperado booleano ou inteiro");
            }
            break;
    }
}


void verificaRetornoObrigatorio(){
    if(
        tabela_de_simbolos[id_corpo_de_funcao_atual()].tipo == tipoTS_semretorno
    ){
        // tudo certo
    }else if(!possui_retorno){
        erroSem("Faltado retorno na função");
    }
}

void verificaPrototipoCompativelComFuncao(){

    int fn_id = id_corpo_de_funcao_atual();
    if(fn_id == -1) return;
    int pro_id = -1;
    int i,j;

    for(i=0;i<topo_tabela_de_simbolos;i++){
        if(
            tabela_de_simbolos[i].escopo == escopoTS_global &&
            tabela_de_simbolos[i].categoria == categoriaTS_prototipo &&
            !strcmp(tabela_de_simbolos[i].nome,tabela_de_simbolos[fn_id].nome)
        ){
            pro_id = i;
        }
    }

    if(pro_id != -1){

        if(
            tabela_de_simbolos[fn_id].tipo != tabela_de_simbolos[pro_id].tipo
        ) erroSin("Conlito entre o retorno da assinatura e o retorno da função");


        i = fn_id+1;
        j = pro_id+1;
        while(
                tabela_de_simbolos[i].categoria == categoriaTS_parametro ||
                tabela_de_simbolos[j].categoria == categoriaTS_parametro_prototipo 
            ){

            if(
                tabela_de_simbolos[i].categoria == categoriaTS_parametro &&
                tabela_de_simbolos[j].categoria == categoriaTS_parametro_prototipo &&
                tabela_de_simbolos[i].tipo == tabela_de_simbolos[j].tipo
            ){
                // allmost fine
                if(
                    tabela_de_simbolos[j].sem_nome == false &&
                     strcmp(tabela_de_simbolos[i].nome,tabela_de_simbolos[j].nome)
                )erroSin("Conlito entre os nomes dos parametros da assinatura os nomes dos parametros da função");
            }else{
                erroSin("Conlito entre os tipos dos parametros da assinatura os tipos dos parametros da função");
            }

            i++;
            j++;
        }
    }
}

void erroSem(char * string){
    printf("Erro Semântico: %s\n", string);
    exit(1);
}

#endif
