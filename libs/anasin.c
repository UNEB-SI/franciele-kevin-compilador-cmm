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

bool debugSin = true;


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


void getToken(){
    tokenAtual = analex(fp);
    mostraToken(tokenAtual);
}

void prog(){
    if(debugSin){
        printf("DBGsin: prog()=>");
        mostraToken(tokenAtual);
    }
    getToken();
    
    // printf("%s\n", tipo(tokenAtual) ? "é tipo" : "não é tipo");
    if( tipo(tokenAtual) ){
        getToken();
        

        if( id(tokenAtual) ){ // tipo id {',' id} ';'
            getToken();
            

            while( sinal(tokenAtual,SN_virgula) ){
                    getToken();
                    

                    if( !id(tokenAtual) ){
                        erroSin();
                    }else{
                        getToken();
                        
                    }
            }
            if( sinal(tokenAtual,SN_abreParenteses) ){
                    // printf("ABRE PARNTESES\n"); // chama tipos_param
                    tipos_param();
                    if( sinal(tokenAtual,SN_fechaParenteses) ){
                            getToken();
                            
                            if( sinal(tokenAtual,SN_abreChaves) ){
                                    getToken();
                                    
                                    if(tipo(tokenAtual)){
                                        while(tipo(tokenAtual)){
                                            getToken();
                                            
                                            if( id(tokenAtual) ){
                                                getToken();
                                                
                                                if( sinal(tokenAtual,SN_virgula) ){
                                                    while(  sinal(tokenAtual,SN_virgula) ){
                                                        getToken();
                                                        
                                                        if( id(tokenAtual) ){
                                                            getToken();
                                                            
                                                        }else{
                                                            erroSin();
                                                        }
                                                    }
                                                    if( !sinal(tokenAtual,SN_pontoEVirgula) ){
                                                            erroSin();
                                                    }
                                                }
                                                if( !sinal(tokenAtual,SN_pontoEVirgula)){
                                                        erroSin();
                                                }else{
                                                    getToken();
                                                    
                                                }
                                            }else{
                                                erroSin();
                                            }
                                        }
                                    }/*if(false){ //CMD

                                    }*/
                                    do{
                                        cmd();
                                        getToken();
                                    }while(!sinal(tokenAtual,SN_fechaParenteses));

                                    
                            }else{
                                erroSin();
                            }
                    }else{
                        erroSin();
                    }
            }else if(   !sinal(tokenAtual,SN_pontoEVirgula)){
                    erroSin();
            }
        }
        else erroSin();
    }
}
bool tipo(token token){
    if(debugSin){
        printf("DBGsin: tipo()=>");
        mostraToken(tokenAtual);
    }


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
void tipos_param(){
    if(debugSin){
        printf("DBGsin: tipos_param()=>");
        mostraToken(tokenAtual);
    }
    getToken();
    

    if( pr(tokenAtual,semparam)){
            // printf("SEM PARAMETROS\n");
    }else if( tipo(tokenAtual)){
        getToken();
        
        if( id(tokenAtual) ){
            getToken();
            
            while(  sinal(tokenAtual,SN_virgula) ){
                getToken();
                
                if(tipo(tokenAtual)){
                    getToken();
                    
                    if( id(tokenAtual) ){
                        getToken();
                        
                    }else{
                        erroSin();
                    }
                }else{
                    erroSin();
                }
            }
            if( !sinal(tokenAtual,SN_virgula)  &&
                !sinal(tokenAtual,SN_fechaParenteses)
              ){
                  erroSin();
              }
            // printf("->");
            // mostraToken(tokenAtual);
        }else{
            erroSin();
        }

    }else{
        erroSin();
    }

    


}
void tipos_p_opc(){
    if(debugSin){
        printf("DBGsin: tipos_p_opc()=>");
        mostraToken(tokenAtual);
    }
}
void cmd(){
    if(debugSin){
        printf("DBGsin: cmd()=>");
        mostraToken(tokenAtual);
    }
    
    //getToken();
    
    if(tokenAtual.categoria == CAT_palavraReservada){
        switch(tokenAtual.codigo){
            case se:
                getToken();
                
                if(tokenAtual.categoria == CAT_sinais &&
                   tokenAtual.codigo == SN_abreParenteses){
                    expr();
                    if(tokenAtual.categoria == CAT_sinais &&
                        tokenAtual.codigo == SN_fechaParenteses){
                        cmd();
                        getToken();
                        
                        if( tokenAtual.categoria == CAT_palavraReservada &&
                            tokenAtual.codigo == senao){
                            cmd();
                        }
                    }else{
                        erroSin();
                    }
                }else{ 
                    erroSin();
                }
                break;

            case enquanto:
                getToken();
                
                if(tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_abreParenteses){
                    expr();
                    if(tokenAtual.categoria == CAT_sinais &&
                        tokenAtual.codigo == SN_fechaParenteses){
                        cmd();
                    }else{
                        erroSin();
                    }
                }else{ 
                    erroSin();
                }
                break;

            case para:
                getToken();
                
                if(tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_abreParenteses){
                    // PARAMOS AQUI
                    getToken();
                    
                    if( tokenAtual.categoria == CAT_sinais &&
                        tokenAtual.codigo == SN_pontoEVirgula){
                        getToken();
                        
                        if( tokenAtual.categoria == CAT_sinais &&
                            tokenAtual.codigo == SN_pontoEVirgula){
                            getToken();
                            
                            if( tokenAtual.categoria == CAT_sinais &&
                            tokenAtual.codigo == SN_fechaParenteses){
                                cmd();
                            }else{
                                atrib();
                            }
                        }else{
                            expr();
                        }
                    }else{
                        atrib();
                    }
                }
                break;
            case retorne:
                getToken();
                
                if(tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_pontoEVirgula){
                    // Nada a fazer, talvez chamar analex
                }else{
                    expr();
                }
            default:
                erroSin();
        }
    }else if(id(tokenAtual)){ // id '(' [expr { ',' expr } ] ')' ';'
        getToken();
        
        if( sinal(tokenAtual,SN_abreParenteses)){
            getToken();
            
            if(tokenAtual.categoria == CAT_sinais &&
            tokenAtual.codigo == SN_fechaParenteses){
                getToken();
                
                if(tokenAtual.categoria == CAT_sinais &&
                   tokenAtual.codigo == SN_pontoEVirgula){
                    // Talvez chamar analex
                }else{
                    erroSin();
                }
            }else{
                expr();
                if(tokenAtual.categoria == CAT_sinais &&
                   tokenAtual.codigo == SN_virgula){
                    while(tokenAtual.categoria == CAT_sinais &&
                          tokenAtual.codigo == SN_virgula){
                        expr();
                    }
                    if(tokenAtual.categoria == CAT_sinais &&
                       tokenAtual.codigo == SN_fechaParenteses){
                        getToken();
                        
                        if(tokenAtual.categoria == CAT_sinais &&
                           tokenAtual.codigo == SN_pontoEVirgula){
                            //Talvez chamar analex
                        }else{
                            erroSin();
                        }
                    }else{
                        erroSin();
                    }
                }else{
                    erroSin();
                }
               
            }
        }else if(tokenAtual,SN_atribuicao){
            atrib();
            if(tokenAtual,SN_pontoEVirgula){
                // DO SOMETHING
            }else{
                erroSin();
            }
        }
    }else if( sinal(tokenAtual,SN_abreChaves)){ // '{' { cmd } '}'
        getToken();
        
        if(tokenAtual.categoria != CAT_sinais &&
           tokenAtual.codigo != SN_fechaChaves){
               while(tokenAtual.categoria != CAT_sinais &&
                     tokenAtual.codigo != SN_fechaChaves){
               cmd();
            } 
        }else{
         // Não faz nada   
        }                  
    }else if( sinal(tokenAtual,SN_pontoEVirgula) ){// ';'
        // Não faz nada
    }/*else{ //  atrib ';' 
        atrib();
        getToken();
        
        if(tokenAtual.categoria == CAT_sinais &&
           tokenAtual.codigo == SN_pontoEVirgula){
            // Talvez chamar analex...
        }else{
            erroSin();
        }
    }*/
}
void atrib(){
    if(debugSin){
        printf("DBGsin: atrib()=>");
        mostraToken(tokenAtual);
    }
    // getToken();
    
    if( sinal(tokenAtual,SN_atribuicao)){
        expr();
        // THE END       
    }else{
        erroSin();
    }

    // if( id(tokenAtual) ){
    //         getToken();// <== ANALEX != ANALEXICO
            
    //         if( sinal(tokenAtual,SN_atribuicao)){
    //             expr();
    //             // THE END       
    //         }else{
    //             erroSin();
    //         }
    // }else{
    //     erroSin();
    // }
}
void expr(){
    if(debugSin){
        printf("DBGsin: expr()=>");
        mostraToken(tokenAtual);
    }
    expr_simp(); 
    // op_rel();    
    // expr_simp();  
}
void expr_simp(){
    if(debugSin){
        printf("DBGsin: expr_simp()=>");
        mostraToken(tokenAtual);
    }

    if( sinal(tokenAtual,SN_soma) ||
        sinal(tokenAtual,SN_subtracao)){
        getToken();
    }
    termo();

    // if( sinal(tokenAtual,SN_soma) ||
    //     sinal(tokenAtual,SN_subtracao)
    // ){
    //     termo();
    // }else{
    //     erroSin();
    // }
    // if( sinal(tokenAtual,SN_soma) ||
    //     sinal(tokenAtual,SN_subtracao) ||
    //     sinal(tokenAtual,SN_ouCondicional)
    // ){   
    //     while(  sinal(tokenAtual,SN_soma) ||
    //             sinal(tokenAtual,SN_subtracao)||
    //             sinal(tokenAtual,SN_ouCondicional)
    //     ){   
    //         termo();
    //     }
    // }else{
    //     erroSin();
    // }
    
}
void termo(){
    if(debugSin){
        printf("DBGsin: termo()=>");
        mostraToken(tokenAtual);
    }

    fator();
    while(
        sinal(tokenAtual,SN_mutiplicacao)||
        sinal(tokenAtual,SN_divisao)||
        sinal(tokenAtual,SN_eCondicional)
    ){
        fator();
    }
}
void fator(){
    if(debugSin){
        printf("DBGsin: fator()=>");
        mostraToken(tokenAtual);
    }
    
    getToken();
        

    switch(tokenAtual.categoria){
        case CAT_id:
            getToken();
             
            if( sinal(tokenAtual,SN_abreParenteses)){
                    getToken();
                     
                    while(sinal(tokenAtual,SN_fechaParenteses)){
                        expr();
                        while(sinal(tokenAtual,SN_virgula)){
                            expr();
                        }
                    }
            }
            break;
        case CAT_constanteInteira:
        case CAT_constanteReal:
        case CAT_constanteCaracter:
            getToken();
               
            break;
        case CAT_sinais:
            if(sinal(tokenAtual,SN_abreParenteses)){
                expr();
                if( sinal(tokenAtual,SN_fechaParenteses)){
                    erroSin();
                }
            }else if(tokenAtual.codigo == SN_negacao){
                fator();
            }else{
                erroSin();
            }
            break;
        default:
            erroSin();        
    }
}
void op_rel(){
    if(debugSin){
        printf("DBGsin: op_rel()=>");
        mostraToken(tokenAtual);
    }
    getToken();
    
    if(tokenAtual.categoria = CAT_sinais){
        switch(tokenAtual.codigo){
            case SN_igualdade:
            case SN_difente:
            case SN_menorIgualQue:
            case SN_menorQue:
            case SN_maiorIgualQue:
            case SN_maiorQue:
                getToken();
                
                break;
            default:
                erroSin();
        }
    }else{
        erroSin();
    }
}

void erroSin(){
    printf("ERRO SINTATICO!!!!!\n");
    exit(1);
}