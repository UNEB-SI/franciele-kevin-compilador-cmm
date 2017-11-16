#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "libs/analex.c"
#include "libs/analex.h"
#include "libs/anasin.c"
#include "libs/anasin.h"


/**
 * Franciele Portugal
 * Kevin Oliveira
 * 12 nov 2017
*/


void main(){
    fp = fopen("sample.cmm","r");
    // temptoken = analex(fp);
    // E(fp);



    // do{
    //     // temptoken = analex(fp);
    //     // mostraToken(temptoken);
    //     getToken();
    // }while(!eof(viewToken()));

    
    // op_rel();
    // tipos_param();
    // tipos_p_opc();

    // fator();
    // termo();
    // expr_simp();
    // prog();
    // getToken();
    // getToken();
    // getToken();
    // printf("----\n");
    // cmd();

    prog();
}