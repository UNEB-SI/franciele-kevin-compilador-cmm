#include "./anasin.h"
#include <stdbool.h>


void prog();
bool tipo(token token);
void tipos_param();
void tipos_p_opc();
void cmd();
void atrib();
void expr();
void expr_simp();
void termo();
void fator();
void op_rel();
void erroSin();


void prog(){
    tokenAtual = analex(fp);
    mostraToken(tokenAtual);
    // printf("%s\n", tipo(tokenAtual) ? "é tipo" : "não é tipo");
    if(tipo(tokenAtual)){
        tokenAtual = analex(fp);
        mostraToken(tokenAtual);
        if(tokenAtual.categoria == CAT_id ){ // tipo id {',' id} ';'
            tokenAtual = analex(fp);
            mostraToken(tokenAtual);
            while( tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_virgula){
                    tokenAtual = analex(fp);
                    mostraToken(tokenAtual);
                    if(tokenAtual.categoria != CAT_id){
                        erroSin();
                    }else{
                        tokenAtual = analex(fp);
                        mostraToken(tokenAtual);
                    }
            }
            if( tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_abreParenteses){
                    printf("ABRE PARNTESES\n"); // chama tipos_param

            }else if(   tokenAtual.categoria != CAT_sinais ||
                        tokenAtual.codigo != SN_pontoEVirgula){
                    erroSin();
            }
        }
        else erroSin();
    }
}
bool tipo(token token){
    if(token.categoria == CAT_palavraReservada){
        switch(token.codigo){
            case caracter:
            case inteiro:
            case real:
            case booleano:
                return true;
            default:
                return false;
        }
    }else{
        return false;
    }
}
void tipos_param(){}
void tipos_p_opc(){}
void cmd(){}
void atrib(){}
void expr(){}
void expr_simp(){}
void termo(){}
void fator(){}
void op_rel(){}


void erroSin(){
    printf("ERRO SINTATICO!!!!!\n");
    exit(1);
}