#ifndef ANASIN
#define ANASIN

#include "analex.h"
#include "anasem.h"
#include "GerenciadorTS.h"
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
void erroSin(char * string);

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
        tokenAtual = tokenProx;
        tokenProx = tokenProxProx;
        tokenProxProx = analex(fp);
    }
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
    int temp_tipo = 0;
    int temp_id = -1;
    do{
        
        getToken();
        if(pr(viewToken(),prototipo)){
            
            getToken();
            if(tipo(viewToken())){
                
                armazenar_simbolo(escopoTS_global,categoriaTS_prototipo,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
                temp_tipo = checar_tipoTS(viewToken());
                getToken();
                if(id(viewToken())){
                    getToken();
                    if(sinal(viewToken(),SN_abreParenteses)){
                        tipos_p_opc();
                        if(sinal(viewNext(),SN_fechaParenteses)){
                            getToken();
                            while(sinal(viewNext(),SN_virgula)){
                                getToken();
                                armazenar_simbolo(escopoTS_global,categoriaTS_prototipo,temp_tipo, ID_TABLE[viewNext().codigo]);

                                

                                if(id(viewNext())){
                                    getToken();
                                }else erroSin("Esperado identificador");

                                if(sinal(viewNext(),SN_abreParenteses)){
                                    getToken();
                                    tipos_p_opc();
                                }else erroSin("Esperando abre parenteses");

                                if(sinal(viewNext(),SN_fechaParenteses)){
                                    getToken();
                                }else erroSin("Esperado fecha parenteses");
                            }

                            if(sinal(viewNext(),SN_pontoEVirgula)){
                                getToken();
                            }else erroSin("Esperado ponto e virgula");

                        }else erroSin("Esperad  o fecha parenteses");
                    }else erroSin("Esperado abre parenteses");
                }else erroSin("Esperado identificador");
            }else if(pr(viewToken(),semretorno)){
                
                
                armazenar_simbolo(escopoTS_global,categoriaTS_prototipo,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
                temp_tipo = checar_tipoTS(viewToken());
                getToken();
                if(id(viewToken())){
                    getToken();
                    if(sinal(viewToken(),SN_abreParenteses)){
                        tipos_p_opc();
                        if(sinal(viewNext(),SN_fechaParenteses)){
                            getToken();
                            while(sinal(viewNext(),SN_virgula)){
                                getToken();
                                
                                armazenar_simbolo(escopoTS_global,categoriaTS_prototipo,temp_tipo, ID_TABLE[viewNext().codigo]);
                                if(id(viewNext())){
                                    getToken();
                                }else erroSin("Esperado identificador");

                                if(sinal(viewNext(),SN_abreParenteses)){
                                    getToken();
                                    tipos_p_opc();
                                }else erroSin("Esperando abre parenteses");

                                if(sinal(viewNext(),SN_fechaParenteses)){
                                    getToken();
                                }else erroSin("Esperado fecha parenteses");
                            }

                            if(sinal(viewNext(),SN_pontoEVirgula)){
                                getToken();
                            }else erroSin("Esperado ponto e virgula");

                        }else erroSin("Esperad  o fecha parenteses");
                    }else erroSin("Esperado abre parenteses");
                }else erroSin("Esperado identificador");
            }else{
                erroSin("tipo invalido");
            }

        }else if(tipo(viewToken())){
            
            
            
            temp_tipo = checar_tipoTS(viewToken());

            getToken();
            
            if(id(viewToken())){
                
                
                
                if(sinal(viewNext(),SN_abreParenteses)){

                    armazenar_simbolo(escopoTS_global,categoriaTS_funcao,temp_tipo , ID_TABLE[viewToken().codigo]);

                    getToken();
                    
                    
                    tipos_param();
                    
                    
                    getToken();
                    if(sinal(viewToken(),SN_fechaParenteses)){
                    }else erroSin("Esperado Fecha Parenteses");
                    
                    getToken();
                    if(sinal(viewToken(),SN_abreChaves)){
                    }else erroSin("Esperado Abre Chaves");

                    
                    // mostraTokens();
                    temp_id = topo_tabela_de_simbolos;
                    while(tipo(viewNext())){
                        getToken(); // no need to check, because the while will do for you
                        if( tipo(viewToken()) && id(viewNext()) ){
                            armazenar_simbolo(escopoTS_local,categoriaTS_variavel,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
                            temp_tipo = checar_tipoTS(viewToken());
                        }
                        
                        if(id(viewNext())){
                            getToken();
                        }else erroSin("Esperado identificador");
                        

                        while(sinal(viewNext(),SN_virgula)){
                            getToken();
                            if( id(viewNext() ) ){
                                armazenar_simbolo(escopoTS_local,categoriaTS_variavel,temp_tipo , ID_TABLE[viewNext().codigo]);
                            }
                            
                            if(id(viewNext())){
                                getToken();
                            }else erroSin("Esperaro identificador");
                            
                        }
                        
                        if(sinal(viewNext(),SN_pontoEVirgula)){
                            getToken();
                        }else erroSin("Esperado ponto e virgula");
                    }
                    

                    while(!sinal(viewNext(),SN_fechaChaves)){
                        
                        cmd();
                        tipoAtualUtilizado = -1;
                        
                        // getToken();
                        
                    }
                    limparSimbolosLocais(temp_id);
                    verificaRetornoObrigatorio();
                    possui_retorno = false;
                    
                    
                    // mostraTabela();
                    getToken();
                    


                    // if(sinal(viewNext(),SN_fechaChaves)){
                    // }else{
                    //     cmd();
                    //     if(sinal(viewNext(),SN_fechaChaves)){
                    //         getToken();
                    //     }else erroSin("Esperado fecha chaves");
                    // }



                }else{
                    armazenar_simbolo(escopoTS_global,categoriaTS_variavel,temp_tipo , ID_TABLE[viewToken().codigo]);
                    while(sinal(viewNext(),SN_virgula)){
                        getToken();
                        
                        if(id(viewNext())){
                            getToken();
                            armazenar_simbolo(escopoTS_global,categoriaTS_variavel,temp_tipo , ID_TABLE[viewToken().codigo]);
                        }else erroSin("Esperado identificador");
                        
                    }
                    if(sinal(viewNext(),SN_pontoEVirgula)){
                        getToken();
                    }else erroSin("Esperado Ponto e virgula");
                }
                

            }else erroSin("Esperado identificador");

        }else if(pr(viewToken(),semretorno)){
            
            
            if(pr(viewToken(),semretorno) && id(viewNext())){
                armazenar_simbolo(escopoTS_global,categoriaTS_funcao,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
            }

            getToken();
            if(id(viewToken())){
                getToken();
                if(sinal(viewToken(),SN_abreParenteses)){
                    tipos_param();
                    getToken();
                    if(sinal(viewToken(),SN_fechaParenteses)){
                        getToken();
                        if(sinal(viewToken(),SN_abreChaves)){
                            // mostraTokens();
                            temp_id = topo_tabela_de_simbolos;
                            while(tipo(viewNext())){
                                getToken(); // no need to check, because the while will do for you
                                
                                armazenar_simbolo(escopoTS_local,categoriaTS_variavel,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
                                temp_tipo = checar_tipoTS(viewToken());
                                if(id(viewNext())){
                                    getToken();
                                }else erroSin("Esperado identificador");
                                while(sinal(viewNext(),SN_virgula)){
                                    getToken();
                                    
                                    armazenar_simbolo(escopoTS_local,categoriaTS_variavel,temp_tipo , ID_TABLE[viewNext().codigo]);

                                    if(id(viewNext())){
                                        getToken();
                                    }else erroSin("Esperaro identificador");
                                }
                                
                                if(sinal(viewNext(),SN_pontoEVirgula)){
                                    getToken();
                                }else erroSin("Esperado ponto e virgula");
                            }

                            while(!sinal(viewNext(),SN_fechaChaves)){
                                cmd();
                                tipoAtualUtilizado = -1;
                            }
                            

                            verificaRetornoObrigatorio();
                            possui_retorno = false;
                            limparSimbolosLocais(temp_id);
                            // mostraTabela();
                            getToken();

                        }else erroSin("Esperado abre chaves");
                    }else erroSin("Esperado fecha parenteses");
                }else erroSin("Esperado abre parenteses");
            }else erroSin("Esperado identificador");



        }else{
            erroSin("Entrada Invalida");
        }
    }while(!eof(viewNext()));
}

// ok
void tipos_param(){
    if(debugSin){
        printf("DBGsin: tipos_param()=>");
        mostraTokens();
    }


    getToken();

    if(pr(viewToken(),semparam)){
        // ALL FINE DUDE
    }else if(tipo(viewToken())){
        
        // verificaPrototipoCompativelComFuncao();
        inicio_escopo_funcao=topo_tabela_de_simbolos;
        armazenar_simbolo(escopoTS_local,categoriaTS_parametro,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
        getToken();
        if(id(viewToken())){
            if(sinal(viewNext(),SN_virgula)){
                getToken();
                do{
                    if(sinal(viewNext(),SN_virgula)) getToken();
                    getToken();
                    if(tipo(viewToken())){
                        
                        armazenar_simbolo(escopoTS_local,categoriaTS_parametro,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
                        getToken();
                        if(id(viewToken())){
                            // All fine
                        }else{
                            erroSin("Esperado um id");
                            // esperado um id
                        }
                    }else{
                        erroSin("Esperando um tipo");
                        // esperado um tipo
                    }
                }while(sinal(viewNext(),SN_virgula));
            }else;
        }else{
            erroSin("Esperado um id");
        }
    }else{
        erroSin("Parametros invalidos");
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
        
        // getToken();
        
        // verificaPrototipoCompativelComFuncao();
        inicio_escopo_funcao=topo_tabela_de_simbolos;
        if(id(viewNext())){
            armazenar_simbolo(escopoTS_local,categoriaTS_parametro_prototipo,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
            getToken();
        }else{
            armazenar_simbolo(escopoTS_local,categoriaTS_parametro_prototipo,checar_tipoTS(viewToken()) , "");
            
        }
        
        
        if(sinal(viewNext(),SN_virgula)){
            do{
                getToken();
                
                if(sinal(viewNext(),SN_virgula)) getToken();

                if(tipo(viewNext())){
                    
                    getToken();
                    
                    if(id(viewNext())){
                        armazenar_simbolo(escopoTS_local,categoriaTS_parametro_prototipo,checar_tipoTS(viewToken()) , ID_TABLE[viewNext().codigo]);
                        getToken();
                    }else{
                        armazenar_simbolo(escopoTS_local,categoriaTS_parametro_prototipo,checar_tipoTS(viewToken()) , "");
                        
                    }


                }else{
                    erroSin("Tipo invalido");
                }
            }while(sinal(viewNext(),SN_virgula));
        }else;

    }else{
        erroSin("Argumentos invalidos"); // argumentos invalidos
    }

}

// ok
void cmd(){
    if(debugSin){
        printf("DBGsin: cmd()=>");
        mostraTokens();
    }
    if(id(viewNext())){
        if(sinal(viewNextNext(),SN_abreParenteses)){
            printf("X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-\n");
            printf("%d\n",numParamFuncao);
            verificaExistenciaDaFuncao(ID_TABLE[viewNext().codigo]);
            id_funcao_atual = verificaPosicaoTabelaDeSimbolos(ID_TABLE[viewNext().codigo]);
            numParamFuncao = 0;
            getToken();
            getToken();
            if(!sinal(viewNext(),SN_fechaParenteses)){
                numParamFuncao =1;
                expr();
                while(sinal(viewNext(),SN_virgula)){
                    getToken();
                    numParamFuncao++;
                    expr();
                }
            }

            if(sinal(viewNext(),SN_fechaParenteses)){
                getToken();
                verificaQuantidadeDeParametros(numParamFuncao);
                numParamFuncao=0;
                if(sinal(viewNext(),SN_pontoEVirgula)){
                    getToken();
                }else erroSin("Esperado ponto e virgula");
            }
        }else{
            atrib();
            getToken();
            if(sinal(viewToken(),SN_pontoEVirgula));
            else erroSin("Esperado Ponto e virgula");
        }
    }
    else if(pr(viewNext(),se)){
        getToken();
        getToken();
        if(sinal(viewToken(),SN_abreParenteses)){
            
            expr();
            
            getToken();
            if(sinal(viewToken(),SN_fechaParenteses)){
                // all fine
                cmd();
                if(pr(viewNext(),senao)){
                    getToken();
                    cmd();
                }
            }else erroSin("Esperado fecha parenteses");
        }else erroSin("Esperado Abre Parenteses");


    }
    else if(pr(viewNext(),enquanto)){
        getToken();
        getToken();
        if(sinal(viewToken(),SN_abreParenteses)){
            
            expr();
            
            getToken();
            if(sinal(viewToken(),SN_fechaParenteses)){
                // all fine
                cmd();
            }else erroSin("Esperado Fecha Parenteses");
        }else erroSin("Esperado Abre Parenteses");

    }
    else if(pr(viewNext(),para)){
        getToken();
        getToken();
        if(sinal(viewToken(),SN_abreParenteses)){
            if(sinal(viewNext(),SN_pontoEVirgula)){
            }else atrib();
            getToken();
            if(sinal(viewToken(),SN_pontoEVirgula)){
            }else erroSin("Esperado Ponto e virgula");

            if(sinal(viewNext(),SN_pontoEVirgula)){
            }else expr();
            getToken();
            if(sinal(viewToken(),SN_pontoEVirgula)){
            }else erroSin("Esperado Ponto e virgula");

            if(sinal(viewNext(),SN_fechaParenteses)){
            }else atrib();

            getToken();
            if(sinal(viewToken(),SN_fechaParenteses)){
            }else erroSin("Esperado Fecha Parenteses");

            cmd();

        }
    }
    else if(pr(viewNext(),retorne)){
        getToken();
        if(sinal(viewNext(),SN_pontoEVirgula)){
            
            getToken();
            tipoAtualUtilizado = -1;
            possui_retorno = true;
            verificaTipoDeRetorno();
        }else{
            
            expr();
            
            getToken();
            if(sinal(viewToken(),SN_pontoEVirgula)){
                possui_retorno = true;
                verificaTipoDeRetorno();
            }else erroSin("Esperado Ponto e virgula");
        }
    }
    else if(sinal(viewNext(),SN_abreChaves)){
        getToken();
        if(sinal(viewNext(),SN_fechaChaves)){
            getToken();
        }else{
            cmd();
            if(sinal(viewNext(),SN_fechaChaves)){
                getToken();
            }else erroSin("Esperado Fecha Chaves");
        }
    }
    else if(sinal(viewNext(),SN_pontoEVirgula)){
        getToken();
    }else{
        erroSin("Esperado Ponto e virgula");
    }
}

// ok
void atrib(){
    if(debugSin){
        printf("DBGsin: atrib()=>");
        mostraTokens();
    }
    getToken();
    if(id(viewToken())){
        trocaTipo(verificaTipoTabelaDeSimbolos(ID_TABLE[viewToken().codigo])); 
        getToken();
        if(sinal(viewToken(),SN_atribuicao)){
            expr();
        }else{
            erroSin("Esperado Sinal de igualdade"); // Esperado sinal de igualdade
        }
    }else{
        erroSin("Esperado Identificador"); // esperado identificador
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
        if(sinal(viewToken(),SN_ouCondicional)){
            tipoAtualUtilizado = -1;
            
        }
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
        if(sinal(viewToken(),SN_eCondicional)){            
            tipoAtualUtilizado = -1;
            
        }
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

        // verificadorDeTipos(viewToken(),numParamFuncao); 
        if(sinal(viewNext(),SN_abreParenteses)){

            verificadorDeTipos(viewToken(),numParamFuncao); 

            
            verificaExistenciaDaFuncao(ID_TABLE[viewToken().codigo]);
            id_funcao_atual = verificaPosicaoTabelaDeSimbolos(ID_TABLE[viewToken().codigo]);
            numParamFuncao = 0;
            // verificadorDeTipos(viewToken(),numParamFuncao); 
            
            

            // id_funcao_atual = verificaPosicaoTabelaDeSimbolos(ID_TABLE[viewNext().codigo]);
            // verificadorDeTipos(viewToken(),numParamFuncao);
            getToken();
            if(sinal(viewNext(),SN_fechaParenteses)){
                // all fine

                getToken();
            }else{
                // expr
                // NOT TESTED     
                
                // verificadorDeTipos(viewToken(),numParamFuncao); 
                numParamFuncao=1;               
                expr();
                while(sinal(viewNext(),SN_virgula)){
                    getToken();
                    numParamFuncao++;
                    expr();
                    
                }
            }
            getToken();
            
            verificaQuantidadeDeParametros(numParamFuncao);
            numParamFuncao=0;
            
            
        }else{
            // all fine
            
            if(numParamFuncao!=0)
                verificadorDeTipos(viewToken(),numParamFuncao);
            else
                trocaTipo(verificaTipoTabelaDeSimbolos(ID_TABLE[viewToken().codigo])); 
            
        }
    }else if(categoria(viewToken(),CAT_constanteInteira)){
        // all fine
        
        if(numParamFuncao!=0)
            verificadorDeTipos(viewToken(),numParamFuncao);
        else
            trocaTipo(tipoTS_inteiro); 
    }else if(categoria(viewToken(),CAT_constanteReal)){
        // all fine
        
        if(numParamFuncao!=0)            
            verificadorDeTipos(viewToken(),numParamFuncao);
        else
            trocaTipo(tipoTS_real); 

    }else if(categoria(viewToken(),CAT_constanteCaracter)){
        // all fine
        
        if(numParamFuncao!=0)
            verificadorDeTipos(viewToken(),numParamFuncao);
        else
            trocaTipo(tipoTS_caracter); 
    }else if(categoria(viewToken(),CAT_literal)){
        // all fine
    }else if (sinal(viewToken(),SN_abreParenteses)){
        // expr
        expr();
        getToken();
        if(sinal(viewToken(),SN_fechaParenteses));
        else erroSin("Esperado Fecha Parenteses");
    }else if(sinal(viewToken(),SN_negacao)){
        // fator
        fator();
    }else{
        erroSin("Entrada invalida");
    }
    if(debugSin){
        printf("DBGsin: fator() <==");
        mostraTokens();
    }
}

// ok
void erroSin(char * string){
    printf("Erro Sintatico: %s\n", string);
    exit(1);
}

int checar_tipoTS(token token){
    if(pr(token,caracter)) return tipoTS_caracter;
    else if(pr(token,inteiro)) return tipoTS_inteiro;
    else if(pr(token,real)) return tipoTS_real;
    else if(pr(token,booleano)) return tipoTS_booleano;
    else if(pr(token,semretorno)) return tipoTS_semretorno;
}

#endif
