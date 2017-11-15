#include "./anasin.h"
#include <stdbool.h>


void prog();
bool tipo();
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

token viewToken();
token viewNext();


void getToken(){
    if( tokenNaoInicializados){
        //printf("primeira chamada\n");
        tokenProx = analex(fp);
        tokenAtual = tokenProx;
        tokenProx = analex(fp);
        tokenNaoInicializados = false;
    }else{
        // printf("não é a primeira chamada\n");
        tokenAtual = tokenProx;
        tokenProx = analex(fp);
    }
    // tokenAtual = analex(fp);
  
    // printf("TOKEN ATUAL");mostraToken(viewToken());
    // printf("TOKEN NEXT");mostraToken(viewNext());
    mostraTokens(viewToken(),viewNext());
}

token viewToken(){
    return tokenAtual;
}
token viewNext(){
    return tokenProx;
}

bool debugSin = false;


bool sinal(token token, int sinal){
    if( tokenAtual.categoria == CAT_sinais &&
        tokenAtual.codigo == sinal){
        return true;
    }else{
        return false;
    }
}

bool id(token token){
    if( tokenAtual.categoria == CAT_id){
        return true;
    }else{
        return false;
    }
}

bool pr(token token, int pr){
    if( tokenAtual.categoria == CAT_palavraReservada &&
        tokenAtual.codigo == pr){
        return true;
    }else{
        return false;
    }
}

bool eof(token token){
    if(token.categoria == CAT_fimDeArquivo) return true;
    else return false;
}



void prog(){
    if(debugSin){
        printf("DBGsin: prog()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
bool tipo(){
    if(debugSin){
        printf("DBGsin: tipo()=>");
        mostraTokens(viewToken(),viewNext());
    }
    getToken();
    if(
        pr(viewToken(),caracter) ||
        pr(viewToken(),inteiro) ||
        pr(viewToken(),real) ||
        pr(viewToken(),booleano) 
    ){
        
    }else{
        erroSin(); 
    }

}
void tipos_param(){
    if(debugSin){
        printf("DBGsin: tipos_param()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void tipos_p_opc(){
    if(debugSin){
        printf("DBGsin: tipos_p_opc()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void cmd(){
    if(debugSin){
        printf("DBGsin: cmd()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void atrib(){
    if(debugSin){
        printf("DBGsin: atrib()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void expr(){
    if(debugSin){
        printf("DBGsin: expr()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void expr_simp(){
    if(debugSin){
        printf("DBGsin: expr_simp()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void termo(){
    if(debugSin){
        printf("DBGsin: termo()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void fator(){
    if(debugSin){
        printf("DBGsin: fator()=>");
        mostraTokens(viewToken(),viewNext());
    }
}
void op_rel(){
    if(debugSin){
        printf("DBGsin: op_rel()=>");
        mostraTokens(viewToken(),viewNext());
    }
}

void erroSin(){
    printf("ERRO SINTATICO!!!!!\n");
    exit(1);
}