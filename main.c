#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my-lib.h"

void main(){
    // printf("Hello World!\n");

    // printf("\nSINAIS\n");
    // printf("SN_abreChaves -> %s\n",SN_TABLE[SN_abreChaves] );
    // printf("SN_fechaChaves -> %s\n",SN_TABLE[SN_fechaChaves] );
    // printf("SN_abreParenteses -> %s\n",SN_TABLE[SN_abreParenteses] );
    // printf("SN_fechaParenteses -> %s\n",SN_TABLE[SN_fechaParenteses] );
    // printf("SN_pontoEVirgula -> %s\n",SN_TABLE[SN_pontoEVirgula] );
    // printf("SN_divisao -> %s\n",SN_TABLE[SN_divisao] );
    // printf("SN_mutiplicacao -> %s\n",SN_TABLE[SN_mutiplicacao] );
    // printf("SN_soma -> %s\n",SN_TABLE[SN_soma] );
    // printf("SN_subtracao -> %s\n",SN_TABLE[SN_subtracao] );
    // printf("SN_virgula -> %s\n",SN_TABLE[SN_virgula] );
    // printf("SN_maiorQue -> %s\n",SN_TABLE[SN_maiorQue] );
    // printf("SN_maiorIgualQue -> %s\n",SN_TABLE[SN_maiorIgualQue] );
    // printf("SN_menorQue -> %s\n",SN_TABLE[SN_menorQue] );
    // printf("SN_menorIgualQue -> %s\n",SN_TABLE[SN_menorIgualQue] );
    // printf("SN_negacao -> %s\n",SN_TABLE[SN_negacao] );
    // printf("SN_difente -> %s\n",SN_TABLE[SN_difente] );
    // printf("SN_atribuicao -> %s\n",SN_TABLE[SN_atribuicao] );
    // printf("SN_igualdade -> %s\n",SN_TABLE[SN_igualdade] );
    // printf("SN_ouCondicional -> %s\n",SN_TABLE[SN_ouCondicional] );
    // printf("SN_eCondiciona -> %s\n",SN_TABLE[SN_eCondicional] );

    // printf("\nPALAVRAS RESERVADAS\n");
    // printf("inteiro -> %s\n",PR_TABLE[inteiro]);
    // printf("real -> %s\n",PR_TABLE[real]);
    // printf("booleano -> %s\n",PR_TABLE[booleano]);
    // printf("caracter -> %s\n",PR_TABLE[caracter]);
    // printf("retorne -> %s\n",PR_TABLE[retorne]);
    // printf("semretorno -> %s\n",PR_TABLE[semretorno]);
    // printf("semparam -> %s\n",PR_TABLE[semparam]);
    // printf("se -> %s\n",PR_TABLE[se]);
    // printf("para -> %s\n",PR_TABLE[para]);
    // printf("enquanto -> %s\n",PR_TABLE[enquanto]);
    // printf("principal -> %s\n",PR_TABLE[principal]);

    printf("\nLeitura de arquivo\n");

    FILE *fp;
    char c;
    fp = fopen("sample.cmm","r");
    while( (c = fgetc(fp)) != EOF )
        printf("%c",c);

    fclose(fp);
}


