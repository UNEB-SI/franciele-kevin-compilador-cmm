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
                    // printf("ABRE PARNTESES\n"); // chama tipos_param
                    tipos_param();
                    if( tokenAtual.categoria == CAT_sinais &&
                        tokenAtual.codigo == SN_fechaParenteses){
                            tokenAtual = analex(fp);
                            mostraToken(tokenAtual);
                            if( tokenAtual.categoria == CAT_sinais &&
                                tokenAtual.codigo == SN_abreChaves){
                                    tokenAtual = analex(fp);
                                    mostraToken(tokenAtual);
                                    if(tipo(tokenAtual)){
                                        while(tipo(tokenAtual)){
                                            tokenAtual = analex(fp);
                                            mostraToken(tokenAtual);
                                            if(tokenAtual.categoria == CAT_id){
                                                tokenAtual = analex(fp);
                                                mostraToken(tokenAtual);
                                                if( tokenAtual.categoria == CAT_sinais &&
                                                    tokenAtual.codigo == SN_virgula){
                                                    while(  tokenAtual.categoria == CAT_sinais &&
                                                            tokenAtual.codigo == SN_virgula){
                                                        tokenAtual = analex(fp);
                                                        mostraToken(tokenAtual);
                                                        if(tokenAtual.categoria == CAT_id){
                                                            tokenAtual = analex(fp);
                                                            mostraToken(tokenAtual);
                                                        }else{
                                                            erroSin();
                                                        }
                                                    }
                                                    if( tokenAtual.categoria != CAT_sinais ||
                                                        tokenAtual.codigo != SN_pontoEVirgula){
                                                            erroSin();
                                                    }
                                                }
                                                if( tokenAtual.categoria != CAT_sinais ||
                                                    tokenAtual.codigo != SN_pontoEVirgula){
                                                        erroSin();
                                                }else{
                                                    tokenAtual = analex(fp);
                                                    mostraToken(tokenAtual);
                                                }
                                            }else{
                                                erroSin();
                                            }
                                        }
                                    }if(false){ //CMD

                                    }

                                    
                            }else{
                                erroSin();
                            }
                    }else{
                        erroSin();
                    }
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
void tipos_param(){
    tokenAtual = analex(fp);
    mostraToken(tokenAtual);

    if( tokenAtual.categoria == CAT_palavraReservada &&
        tokenAtual.codigo == semparam){
            // printf("SEM PARAMETROS\n");
    }else if( tipo(tokenAtual)){
        tokenAtual = analex(fp);
        mostraToken(tokenAtual);
        if(tokenAtual.categoria == CAT_id){
            tokenAtual = analex(fp);
            mostraToken(tokenAtual);
            while(  tokenAtual.categoria == CAT_sinais &&
                    tokenAtual.codigo == SN_virgula ){
                tokenAtual = analex(fp);
                mostraToken(tokenAtual);
                if(tipo(tokenAtual)){
                    tokenAtual = analex(fp);
                    mostraToken(tokenAtual);
                    if(tokenAtual.categoria == CAT_id){
                        tokenAtual = analex(fp);
                        mostraToken(tokenAtual);
                    }else{
                        erroSin();
                    }
                }else{
                    erroSin();
                }
            }
            if( (tokenAtual.categoria!= CAT_sinais ||
                 tokenAtual.codigo != SN_virgula)  &&
                (tokenAtual.categoria!= CAT_sinais ||
                 tokenAtual.codigo != SN_fechaParenteses)
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
void tipos_p_opc(){}
void cmd(){
    tokenAtual = analex(fp);
    mostraToken(tokenAtual);
    if(tokenAtual.categoria == CAT_palavraReservada){
        switch(tokenAtual.codigo){
            case se:
                tokenAtual = analex(fp);
                mostraToken(tokenAtual);
                if(tokenAtual.categoria == CAT_sinais &&
                   tokenAtual.codigo == SN_abreParenteses){
                    expr();
                    if(tokenAtual.categoria == CAT_sinais &&
                        tokenAtual.codigo == SN_fechaParenteses){
                        cmd();
                        tokenAtual = analex(fp);
                        mostraToken(tokenAtual);
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
                tokenAtual = analex(fp);
                mostraToken(tokenAtual);
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
                tokenAtual = analex(fp);
                mostraToken(tokenAtual);
                if(tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_abreParenteses){
                    // PARAMOS AQUI
                    tokenAtual = analex(fp);
                    mostraToken(tokenAtual);
                    if( tokenAtual.categoria == CAT_sinais &&
                        tokenAtual.codigo == SN_pontoEVirgula){
                        tokenAtual = analex(fp);
                        mostraToken(tokenAtual);
                        if( tokenAtual.categoria == CAT_sinais &&
                            tokenAtual.codigo == SN_pontoEVirgula){
                            tokenAtual = analex(fp);
                            mostraToken(tokenAtual);
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
                tokenAtual = analex(fp);
                mostraToken(tokenAtual);
                if(tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_pontoEVirgula){
                    // Nada a fazer, talvez chamar analex
                }else{
                    expr();
                }
            default:
                erroSin();
        }
    }else if(tokenAtual.categoria == CAT_id){ // id '(' [expr { ',' expr } ] ')' ';'
        tokenAtual = analex(fp);
        mostraToken(tokenAtual);
        if(tokenAtual.categoria == CAT_sinais &&
           tokenAtual.codigo == SN_abreParenteses){
            tokenAtual = analex(fp);
            mostraToken(tokenAtual);
            if(tokenAtual.categoria == CAT_sinais &&
            tokenAtual.codigo == SN_fechaParenteses){
                tokenAtual = analex(fp);
                mostraToken(tokenAtual);
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
                        tokenAtual = analex(fp);
                        mostraToken(tokenAtual);
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
        }
    }else if(tokenAtual.categoria == CAT_sinais &&  // '{' { cmd } '}'
             tokenAtual.codigo == SN_abreChaves){
        tokenAtual = analex(fp);
        mostraToken(tokenAtual);
        if(tokenAtual.categoria != CAT_sinais &&
           tokenAtual.codigo != SN_fechaChaves){
               while(tokenAtual.categoria != CAT_sinais &&
                     tokenAtual.codigo != SN_fechaChaves){
               cmd();
            } 
        }else{
         // Não faz nada   
        }                  
    }else if(tokenAtual.categoria == CAT_sinais &&  // ';'
             tokenAtual.codigo == SN_pontoEVirgula){
        // Não faz nada
    }else{ //  atrib ';' 
        atrib();
        tokenAtual = analex(fp);
        mostraToken(tokenAtual);
        if(tokenAtual.categoria == CAT_sinais &&
           tokenAtual.codigo == SN_pontoEVirgula){
            // Talvez chamar analex...
        }else{
            erroSin();
        }
    }
}
void atrib(){
    tokenAtual = analex(fp);
    mostraToken(tokenAtual);
    if( tokenAtual.categoria == CAT_id){
            tokenAtual = analex(fp);// <== ANALEX != ANALEXICO
            mostraToken(tokenAtual);
            if( tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_igualdade){
                expr();
                // THE END       
            }else{
                erroSin();
            }
    }else{
        erroSin();
    }
}
void expr(){
    expr_simp(); 
    op_rel();    
    expr_simp();  
}
void expr_simp(){
    if( (tokenAtual.categoria == CAT_sinais &&
         tokenAtual.codigo == SN_soma) ||
        (tokenAtual.categoria == CAT_sinais &&
         tokenAtual.codigo == SN_subtracao)
    ){
        termo();
    }else{
        erroSin();
    }
    if( (tokenAtual.categoria == CAT_sinais &&
        tokenAtual.codigo == SN_soma) ||
       (tokenAtual.categoria == CAT_sinais &&
        tokenAtual.codigo == SN_subtracao) ||
       (tokenAtual.categoria == CAT_sinais &&
        tokenAtual.codigo == SN_ouCondicional)
    ){   
        while( (tokenAtual.categoria == CAT_sinais &&
            tokenAtual.codigo == SN_soma) ||
           (tokenAtual.categoria == CAT_sinais &&
            tokenAtual.codigo == SN_subtracao) ||
           (tokenAtual.categoria == CAT_sinais &&
            tokenAtual.codigo == SN_ouCondicional)
        ){   
            termo();
        }
    }else{
        erroSin();
    }
    
}
void termo(){
    fator();
    while(
        (tokenAtual.categoria == CAT_sinais &&
         tokenAtual.codigo == SN_mutiplicacao)||
        (tokenAtual.categoria == CAT_sinais &&
         tokenAtual.codigo == SN_divisao)||
        (tokenAtual.categoria == CAT_sinais &&
         tokenAtual.codigo == SN_eCondicional)
    ){
        fator();
    }
}
void fator(){
    tokenAtual = analex(fp);
    mostraToken(tokenAtual);    

    switch(tokenAtual.categoria){
        case CAT_id:
            tokenAtual = analex(fp);
            mostraToken(tokenAtual); 
            if( tokenAtual.categoria == CAT_sinais &&
                tokenAtual.codigo == SN_abreParenteses){
                    tokenAtual = analex(fp);
                    mostraToken(tokenAtual); 
                    while(tokenAtual.categoria != CAT_sinais ||
                          tokenAtual.codigo != SN_fechaParenteses){
                        expr();
                        while(tokenAtual.categoria == CAT_sinais &&
                              tokenAtual.codigo == SN_virgula){
                            expr();
                        }
                    }
            }
            break;
        case CAT_constanteInteira:
        case CAT_constanteReal:
        case CAT_constanteCaracter:
            tokenAtual = analex(fp);
            mostraToken(tokenAtual);   
            break;
        case CAT_sinais:
            if(tokenAtual.codigo == SN_abreParenteses){
                expr();
                if( tokenAtual.categoria != CAT_sinais ||
                    tokenAtual.codigo != SN_fechaParenteses){
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
    tokenAtual = analex(fp);
    mostraToken(tokenAtual);
    if(tokenAtual.categoria = CAT_sinais){
        switch(tokenAtual.codigo){
            case SN_igualdade:
            case SN_difente:
            case SN_menorIgualQue:
            case SN_menorQue:
            case SN_maiorIgualQue:
            case SN_maiorQue:
                tokenAtual = analex(fp);
                mostraToken(tokenAtual);
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