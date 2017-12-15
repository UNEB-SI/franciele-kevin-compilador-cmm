#ifndef GERENTS
#define GERENTS


#include "anasin.h"
#include "anasem.h"
#include <stdbool.h>

void mostraSimbolo(int id);
int armazenar_simbolo(int escopo,int categoria, int tipo, char nomeID[20]);
void mostraTabela();
void limparSimbolosLocais(int i);

typedef struct struct_tabela_de_simbolos{
    char nome[20];
    int tipo;
    int categoria;
    int escopo;
    int enderecoRelativo;
    bool zumbi;
    bool sem_nome;
} struct_tabela_de_simbolos;

struct_tabela_de_simbolos tabela_de_simbolos[200];
int topo_tabela_de_simbolos = 0;
int contador_simbolos_globais = 0;
int contador_simbolos_locais = 0;
int inicio_escopo_funcao = 0;
int id_funcao_atual = 0;
int numParamFuncao = 0;
int tipoAtualUtilizado = -1;


enum tipoTS{
    tipoTS_inteiro,
    tipoTS_real,
    tipoTS_caracter,
    tipoTS_booleano,
    tipoTS_semretorno
};

char tipoTS_nomes[][20] = {
    "inteiro",
    "real",
    "caracter",
    "booleano",
    "sem retorno"
};

enum categoriaTS{
    categoriaTS_variavel,
    categoriaTS_parametro,
    categoriaTS_funcao,
    categoriaTS_prototipo,
    categoriaTS_parametro_prototipo
};

char categoriaTS_nomes[][20] = {
    "variavel",
    "parametro",
    "funcao",
    "prototipo",
    "param de proto"
};

enum escopoTS{
    escopoTS_global,
    escopoTS_local
};

int armazenar_simbolo(int escopo,int categoria, int tipo, char nomeID[20]){
    strcpy(tabela_de_simbolos[topo_tabela_de_simbolos].nome,nomeID);
    tabela_de_simbolos[topo_tabela_de_simbolos].sem_nome = !strcmp(nomeID,"");
    tabela_de_simbolos[topo_tabela_de_simbolos].tipo = tipo;
    tabela_de_simbolos[topo_tabela_de_simbolos].categoria = categoria;
    tabela_de_simbolos[topo_tabela_de_simbolos].escopo = escopo;

    switch(escopo){
            case escopoTS_global:
                tabela_de_simbolos[topo_tabela_de_simbolos].enderecoRelativo = contador_simbolos_globais;
                contador_simbolos_globais++;
                break;
            case escopoTS_local:
                tabela_de_simbolos[topo_tabela_de_simbolos].enderecoRelativo = contador_simbolos_locais;
                contador_simbolos_locais++;
                break;
            default:
                break;
                // erro
    }
    if(categoria == categoriaTS_parametro){
        tabela_de_simbolos[topo_tabela_de_simbolos].zumbi = true;
    }else{
        tabela_de_simbolos[topo_tabela_de_simbolos].zumbi = false;
    }
    topo_tabela_de_simbolos++;
    // printf("armazenado --> ");
    // mostraSimbolo(topo_tabela_de_simbolos-1);

    mostraTabela();
    if(escopo == escopoTS_global){
        verificaIDGlobalDuplicado(topo_tabela_de_simbolos-1);
    }else{
        verificaIDLocalDuplicado(inicio_escopo_funcao,topo_tabela_de_simbolos-1);
    }

    // if(escopo == escopoTS_global && categoria == categoriaTS_funcao)
        // id_funcao_atual = topo_tabela_de_simbolos-1;


    return topo_tabela_de_simbolos-1;
}



void mostraSimbolo(int id){
    printf("<<N %s |Es %s |Er %d |T %s |C %s |Z %s |SN %s>>\n", tabela_de_simbolos[id].nome ,
                                                            tabela_de_simbolos[id].escopo? "Local" :"Global" ,
                                                            tabela_de_simbolos[id].enderecoRelativo,
                                                            tipoTS_nomes[tabela_de_simbolos[id].tipo] ,
                                                            categoriaTS_nomes[tabela_de_simbolos[id].categoria] ,
                                                            tabela_de_simbolos[id].zumbi ? "Zombie" : "Not Zombie" ,
                                                            tabela_de_simbolos[id].sem_nome ? "sim" : "não");
}



void mostraTabela(){
    int i;

    printf("\n--TABELA-------------------------------------------\n");
    for (i=0;i<topo_tabela_de_simbolos;i++){
        printf("[%.2d]",i);
        mostraSimbolo(i);
    }
    printf("---------------------------------------------------\n");
}


void limparSimbolosLocais(int i){
    topo_tabela_de_simbolos = i;
}




#endif
