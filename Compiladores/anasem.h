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
                tabela_de_simbolos[i].escopo == escopoTS_global
            ){
                erroSem("Redefinição de variável global");
            }
        }
    }

}

void verificaIDLocalDuplicado(int id_inicio, int id){
    int i;
    printf("------------------------------------inicio: %d\n",id_inicio);
    for(i=id_inicio;i<topo_tabela_de_simbolos;i++){
        if(i != id){
            if(
                !strcmp(tabela_de_simbolos[i].nome, tabela_de_simbolos[id].nome) &&
                tabela_de_simbolos[i].escopo == escopoTS_local
            ){
                erroSem("Redefinição de variável local ou Parametro duplicado");
            }
        }
    }
}



void erroSem(char * string){
    printf("Erro Semântico: %s\n", string);
    exit(1);
}

#endif
