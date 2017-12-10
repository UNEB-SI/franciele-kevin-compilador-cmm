#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "anasin.h"


/**
 * Franciele Portugal
 * Kevin Oliveira
 * 12 nov 2017
*/


int main(void){
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
    // tipos_p_opc();
    return 0;
}
