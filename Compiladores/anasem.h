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
                tabela_de_simbolos[i].escopo == tabela_de_simbolos[id].escopo
            ){
                erroSem("Redefinição de variável global");
            }
        }
    }

}



void erroSem(char * string){
    printf("Erro Semântico: %s\n", string);
    exit(1);
}

#endif
