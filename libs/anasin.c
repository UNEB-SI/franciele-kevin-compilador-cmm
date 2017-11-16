#include "./anasin.h"
#include <stdbool.h>



// Protipos -----------------
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
bool op_rel(token token);
void erroSin();

token viewToken();
token viewNext();
token viewNextNext();

bool debugSin = false;
// Token ---------------

void getToken(){
    if( tokenNaoInicializados){
        //printf("primeira chamada\n");

        tokenAtual = analex(fp);
        tokenProx = analex(fp);
        tokenProxProx = analex(fp);
        
        // tokenProx = analex(fp);
        // tokenAtual = tokenProx;
        // tokenProx = analex(fp);
        tokenNaoInicializados = false;
    }else{
        // printf("não é a primeira chamada\n");
        tokenAtual = tokenProx;
        tokenProx = tokenProxProx;
        tokenProxProx = analex(fp);
    }
    // tokenAtual = analex(fp);
  
    // printf("TOKEN ATUAL");mostraToken(viewToken());
    // printf("TOKEN PROX");mostraToken(viewNext());
    // printf("TOKEN PROXPROX");mostraToken(viewNextNext());
    
    mostraTokens();
}

token viewToken(){
    return tokenAtual;
}

token viewNext(){
    return tokenProx;
}

token viewNextNext(){
    return tokenProxProx;
}

// Checagem ---------------

// ok
bool categoria(token token, int cat){
    if( token.categoria == cat){
        return true;
    }else{
        return false;
    }
}

// ok
bool sinal(token token, int sinal){
    if( token.categoria == CAT_sinais &&
        token.codigo == sinal){
        return true;
    }else{
        return false;
    }
}

// ok
bool id(token token){
    if( token.categoria == CAT_id){
        return true;
    }else{
        return false;
    }
}

// ok
bool pr(token token, int pr){
    if( token.categoria == CAT_palavraReservada &&
        token.codigo == pr){
        return true;
    }else{
        return false;
    }
}

// ok
bool eof(token token){
    if(token.categoria == CAT_fimDeArquivo) return true;
    else return false;
}

// ok
bool tipo(token token){
    if(debugSin){
        printf("DBGsin: tipo()=>");
        mostraTokens();
    }
    // getToken();
    if(
        pr(token,caracter) ||
        pr(token,inteiro) ||
        pr(token,real) ||
        pr(token,booleano) 
    ){
        // all fine
        return true;
    }else{
        return false;
    }
}

// ok
bool op_rel(token token){
    if(debugSin){
        printf("DBGsin: op_rel()=>");
        mostraTokens();
    }
    // getToken();
    if(
        sinal(token, SN_igualdade) ||
        sinal(token, SN_difente) ||
        sinal(token, SN_menorIgualQue) ||
        sinal(token, SN_menorQue) ||
        sinal(token, SN_maiorIgualQue) ||
        sinal(token, SN_maiorQue) 
    ){
        // all fine
        if(debugSin){
            printf("DBGsin: op_rel() <==");
            mostraTokens();
        }
        return true;
    }else{
        if(debugSin){
            printf("DBGsin: op_rel() <==");
            mostraTokens();
        }
        return false;
    }
}

// Execução ---------------


void prog(){
    if(debugSin){
        printf("DBGsin: prog()=>");
        mostraTokens();
    }
}

// ok
void tipos_param(){
    if(debugSin){
        printf("DBGsin: tipos_param()=>");
        mostraTokens();
    }
    
    
    getToken();

    if(pr(viewToken(),semparam)){
        printf("SEM PARAMETOS\n");
    }else if(tipo(viewToken())){
        getToken();
        if(id(viewToken())){
            if(sinal(viewNext(),SN_virgula)){
                getToken();
                do{
                    if(sinal(viewNext(),SN_virgula)) getToken();
                    getToken();
                    if(tipo(viewToken())){
                        getToken();
                        if(id(viewToken())){
                            // All fine
                        }else{
                            erroSin();
                            // esperado um id
                        }
                    }else{
                        erroSin();
                        // esperado um tipo
                    }
                }while(sinal(viewNext(),SN_virgula));
            }else;
        }else{
            erroSin();
        }
    }else{
        erroSin();
    }

}

// ok
void tipos_p_opc(){
    if(debugSin){
        printf("DBGsin: tipos_p_opc()=>");
        mostraTokens();
    }

    getToken();
    
    if(pr(viewToken(),semparam)){
        //all fine
    }else if(tipo(viewToken())){
        getToken();
        if(id(viewToken())) getToken();
        if(sinal(viewToken(),SN_virgula)){
            do{ 
                getToken();
                if(sinal(viewToken(),SN_virgula)) getToken();

                if(tipo(viewToken())){
                    if(id(viewNext())){
                        getToken();
                    }

                }else{
                    erroSin();
                }
            }while(sinal(viewNext(),SN_virgula));
        }else;
        
    }else{
        erroSin(); // argumentos invalidos
    }

}

void cmd(){
    if(debugSin){
        printf("DBGsin: cmd()=>");
        mostraTokens();
    }
    // getToken();
    // if(viw)
}

// ok
void atrib(){
    if(debugSin){
        printf("DBGsin: atrib()=>");
        mostraTokens();
    }
    getToken();
    if(id(viewToken())){
        getToken();
        if(sinal(viewToken(),SN_atribuicao)){
            expr();
        }else{
            erroSin(); // Esperado sinal de igualdade
        }
    }else{
        erroSin(); // esperado identificador
    }
}

//ok
void expr(){
    if(debugSin){
        printf("DBGsin: expr()=>");
        mostraTokens();
    }
    expr_simp();
    if(op_rel(viewNext())){
        getToken();
        expr_simp();
    }
    if(debugSin){
        printf("DBGsin: expr() <==");
        mostraTokens();
    }

}

//ok 
void expr_simp(){
    if(debugSin){
        printf("DBGsin: expr_simp()=>");
        mostraTokens();
    }
    if(
        sinal(viewNext(),SN_soma) ||
        sinal(viewNext(),SN_subtracao)
    ){
        getToken();
    }
    termo();
    while(
        sinal(viewNext(),SN_soma) ||
        sinal(viewNext(),SN_subtracao) ||
        sinal(viewNext(),SN_ouCondicional)
    ){
        getToken();
        termo();
    }
    if(debugSin){
        printf("DBGsin: expr_simp() <==");
        mostraTokens();
    }
}

// ok
void termo(){
    if(debugSin){
        printf("DBGsin: termo()=>");
        mostraTokens();
    }
    fator();
    while(
        sinal(viewNext(),SN_mutiplicacao) ||
        sinal(viewNext(),SN_divisao) ||
        sinal(viewNext(),SN_eCondicional)
    ){
        getToken();
        fator();
    }
    if(debugSin){
        printf("DBGsin: termo() <==");
        mostraTokens();
    }
}

// ok 
void fator(){
    if(debugSin){
        printf("DBGsin: fator()=>");
        mostraTokens();
    }

    getToken();
    if(id(viewToken())){
        // 2 cases
        if(sinal(viewNext(),SN_abreParenteses)){
            getToken();
            if(sinal(viewNext(),SN_fechaParenteses)){
                // all fine
                getToken();
            }else{
                // expr
                // NOT TESTED
                expr();
                while(sinal(viewNext(),SN_virgula)){
                    getToken();
                    expr();
                }
            }
        }else{
            // all fine
        }
    }else if(categoria(viewToken(),CAT_constanteInteira)){
        // all fine
    }else if(categoria(viewToken(),CAT_constanteReal)){
        // all fine
    }else if(categoria(viewToken(),CAT_constanteCaracter)){
        // all fine
    }else if (sinal(viewToken(),SN_abreParenteses)){
        // expr
        expr();
        getToken();
        if(sinal(viewToken(),SN_fechaParenteses));
        else erroSin();
    }else if(sinal(viewToken(),SN_negacao)){
        // fator
        fator();
    }else{
        erroSin();
    }
    if(debugSin){
        printf("DBGsin: fator() <==");
        mostraTokens();
    }
}



// ok
void erroSin(){
    printf("ERRO SINTATICO!!!!!\n");
    exit(1);
}