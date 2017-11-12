#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "libs/analex.c"
#include "libs/analex.h"
#include "libs/anasin.c"
#include "libs/anasin.h"
/**
 * Franciele Portugal
 * Kevin Oliveira
 * 12 nov 2017
*/
void mostraToken(token token){
    char tempVar[100];
    switch(token.categoria){
        case CAT_id:
            strcpy(tempVar,ID_TABLE[token.codigo]);
            break;
        case CAT_palavraReservada:
            strcpy(tempVar,PR_TABLE[token.codigo]);
            break;
        case CAT_sinais:
            strcpy(tempVar,SN_TABLE[token.codigo]);
            break;
        case CAT_constanteInteira:
            // strcpy(tempVar,CT_I_TABLE[token.codigo]);
            sprintf(tempVar,"%d",CT_I_TABLE[token.codigo]);
            break;
        case CAT_constanteReal:
            // strcpy(tempVar,CT_R_TABLE[token.codigo]);
            sprintf(tempVar,"%f",CT_R_TABLE[token.codigo]);
            break;
        case CAT_constanteCaracter:
            // strcpy(tempVar,CT_C_TABLE[token.codigo]);
            sprintf(tempVar,"%c",CT_C_TABLE[token.codigo]);
            break;
        case CAT_literal:
            strcpy(tempVar,LT[token.codigo]);
            break;
        case CAT_fimDeArquivo:
            strcpy(tempVar,tabela_categoria[token.categoria]);
            break;
        default:
            strcpy(tempVar,"Categoria indefinida");
            break;
    }
    printf("< %s , %s >\n",tabela_categoria[token.categoria], tempVar);
}


void main(){
    FILE* fp;
    fp = fopen("sample.cmm","r");
    // temptoken = analex(fp);
    // E(fp);
    token temptoken;
    do{
        temptoken = analex(fp);
        mostraToken(temptoken);
    }while(temptoken.categoria != CAT_fimDeArquivo);

}