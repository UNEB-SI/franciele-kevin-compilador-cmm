#include "./analex.h"
#include <stdbool.h>

int estado = 0;
int linha=1;
int coluna=1;

bool debug = false;


bool ehLetra(char caracter){
    if(
        (caracter >= 65 && caracter <= 90) ||
        (caracter >= 97 && caracter <= 122)
    ) return true;
    return false;
}

bool ehDigito(char caracter){
    if(caracter >= 48 && caracter <= 57)
        return true;
    return false;
}

bool ehPalavraReservada(char string[]){
    int i;
    for (i=0;i<NUM_PR_TABLE;i++){
        if( !strcmp( string , PR_TABLE[i] ) ) return true;
    } 
    return false;
}

int numeroEnumPalavraReservada(char string[]){
    int i;
    for (i=0;i<NUM_PR_TABLE;i++){
        if( !strcmp( string , PR_TABLE[i] ) ) return i;
    } 
    return -1;
}

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

void mostraTokens(token token1, token token2){
    char tempVar[100];
    switch(token1.categoria){
        case CAT_id:
            strcpy(tempVar,ID_TABLE[token1.codigo]);
            break;
        case CAT_palavraReservada:
            strcpy(tempVar,PR_TABLE[token1.codigo]);
            break;
        case CAT_sinais:
            strcpy(tempVar,SN_TABLE[token1.codigo]);
            break;
        case CAT_constanteInteira:
            // strcpy(tempVar,CT_I_TABLE[token.codigo]);
            sprintf(tempVar,"%d",CT_I_TABLE[token1.codigo]);
            break;
        case CAT_constanteReal:
            // strcpy(tempVar,CT_R_TABLE[token.codigo]);
            sprintf(tempVar,"%f",CT_R_TABLE[token1.codigo]);
            break;
        case CAT_constanteCaracter:
            // strcpy(tempVar,CT_C_TABLE[token.codigo]);
            sprintf(tempVar,"%c",CT_C_TABLE[token1.codigo]);
            break;
        case CAT_literal:
            strcpy(tempVar,LT[token1.codigo]);
            break;
        case CAT_fimDeArquivo:
            strcpy(tempVar,tabela_categoria[token1.categoria]);
            break;
        default:
            strcpy(tempVar,"Categoria indefinida");
            break;
    }
    printf("[ %s , %s ]",tabela_categoria[token1.categoria], tempVar);
    tempVar[0]='\0';
    printf(" -> ");
    switch(token2.categoria){
        case CAT_id:
            strcpy(tempVar,ID_TABLE[token2.codigo]);
            break;
        case CAT_palavraReservada:
            strcpy(tempVar,PR_TABLE[token2.codigo]);
            break;
        case CAT_sinais:
            strcpy(tempVar,SN_TABLE[token2.codigo]);
            break;
        case CAT_constanteInteira:
            // strcpy(tempVar,CT_I_TABLE[token.codigo]);
            sprintf(tempVar,"%d",CT_I_TABLE[token2.codigo]);
            break;
        case CAT_constanteReal:
            // strcpy(tempVar,CT_R_TABLE[token.codigo]);
            sprintf(tempVar,"%f",CT_R_TABLE[token2.codigo]);
            break;
        case CAT_constanteCaracter:
            // strcpy(tempVar,CT_C_TABLE[token.codigo]);
            sprintf(tempVar,"%c",CT_C_TABLE[token2.codigo]);
            break;
        case CAT_literal:
            strcpy(tempVar,LT[token2.codigo]);
            break;
        case CAT_fimDeArquivo:
            strcpy(tempVar,tabela_categoria[token2.categoria]);
            break;
        default:
            strcpy(tempVar,"Categoria indefinida");
            break;
    }
    printf("[ %s , %s ]\n",tabela_categoria[token2.categoria], tempVar);

}


float converteStringParaReal(char string[]){
    // char parteInteira[100];
    // char parteDecimal[100];
    // parteInteira[0] = '\0';
    // parteDecimal[0] = '\0';
    // float pi = 0;
    // float pd = 0;
    // float retorno=0;

    // bool depoisDoPonto = false;
    // int i;
    // for(i=0; string[i]!='\0' ;i++){
    //     if(string[i]=='.') depoisDoPonto= true;
    //     else{
    //         if(depoisDoPonto){
    //             sprintf(parteDecimal,"%s%c",parteDecimal,string[i]);
    //         }else{ // antes do ponto
    //             sprintf(parteInteira,"%s%c",parteInteira,string[i]);
    //         }
    //     }
    // }

    // pi = atof(parteInteira);
    // pd = atof(parteDecimal);
    // retorno = pi + ( pd * pow(0.1,strlen(parteDecimal)) );

    printf("-> %f",atof(string));
    return atof(string);
    //printf("%s %s %f %f %f %d\n", parteInteira, parteDecimal, pi, pd, retorno, strlen(parteDecimal));
    
    // return retorno;
}

void mensagemDeErro(FILE* fp,char c,int linha,int coluna){
    
    char auxChar;
    int i;
    printf("\nErro lexico em %d:%d\n",linha,coluna);
    fseek(fp, coluna * -1, SEEK_CUR);
    while( true ){
        auxChar = fgetc(fp);
        if(auxChar == '\n' || auxChar == EOF){
            printf("\n");
            break;
        }
        else printf("%c",auxChar);
    }
    for(i=1;i<coluna;i++) printf(" ");
    printf("^\n");
    exit(1);
}


token analex(FILE *fp){
    char charEntrada;
    char buffer[1000]="";
    bool finalDeArquivo = false;
    token returnToken;

    while( !finalDeArquivo ){
        charEntrada = fgetc(fp);

        //printf("%c",charEntrada);
        //printf("estado atual %d\tlendo char '%c'\n",estado,charEntrada);
        
        //printf(":%d:%d ->'%c'\n",linha,coluna,charEntrada);
        switch(estado){
            case 0: if(debug){printf("E:%d  B:%s\n",estado,buffer);} //INICIAL
                // abre chaves
                if(charEntrada== '{') estado = 1;
                // fecha chaves
                else if(charEntrada== '}') estado = 2;
                // abre parenteses
                else if(charEntrada== '(') estado = 3;
                // fecha parenteses
                else if(charEntrada== ')') estado = 4;
                // ponto e virgula
                else if(charEntrada== ';') estado = 5;
                // divisão ou comentario
                else if(charEntrada== '/') estado = 6;
                // palavra reservada ou ID
                else if(ehLetra(charEntrada)){
                    ungetc(charEntrada, fp);
                    coluna--;
                    estado = 12;
                }
                // numero inteiro ou real
                else if(ehDigito(charEntrada)){
                    ungetc(charEntrada, fp);
                    coluna--;
                    estado = 15;
                }
                // Cadeia de caracteres
                else if(charEntrada== '"') estado = 20;
                // caracter
                else if(charEntrada== '\'') estado = 23;
                // maior ou maior e igual
                else if(charEntrada== '>') estado = 26;
                // menor ou menor e igual
                else if(charEntrada== '<') estado = 29;
                // negação ou diferente
                else if(charEntrada== '!') estado = 32;
                // igualdade ou atribuição
                else if(charEntrada== '=') estado = 35;
                // soma
                else if(charEntrada== '+') estado = 38;
                // subtração
                else if(charEntrada== '-') estado = 39;
                // multiplicaçõa
                else if(charEntrada== '*') estado = 40;
                // virgula
                else if(charEntrada== ',') estado = 41;
                // maior ou maior e igual
                else if(charEntrada == EOF){
                    estado = 42;
                    ungetc(charEntrada, fp);
                    coluna--;
                }
                // não entra fim de arquivo

                // ou condicional
                else if(charEntrada== '|') estado = 43;
                // e condicional
                else if(charEntrada== '&') estado = 45;

                // RETRO ALIMENTAÇÂO

                // maior ou maior e igual
                else if(charEntrada=='\n'){
                    estado = 0;
                    linha++;
                    coluna=0;
                }
                else if(charEntrada== '\t' ||charEntrada== ' ') estado = 0;
                else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 1: if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_abreChaves;

                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 2: if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_fechaChaves;
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 3: if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_abreParenteses;
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 4: if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_fechaParenteses;
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 5: if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_pontoEVirgula;
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 6: if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                // comentario
                if(charEntrada == '*'){ 
                    estado = 8;
                //divisão
                }else{
                    ungetc(charEntrada, fp);
                    coluna--;
                    estado = 7;
                }
                break;
            case 7: if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_divisao;
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 8: if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '*'){
                    estado = 10;
                }else{
                    estado = 9;
                    if(charEntrada=='\n'){
                        linha++;
                        coluna=0;
                    }else if(charEntrada == EOF){
                        estado = 42;
                        ungetc(charEntrada, fp);
                        coluna--;
                    }
                }
                break;
            case 9: if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '*'){
                    estado = 10;
                }else{
                    estado = 9;
                    if(charEntrada=='\n'){
                        linha++;
                        coluna=0;
                    }else if(charEntrada == EOF){
                        estado = 42;
                        ungetc(charEntrada, fp);
                        coluna--;
                    }
                }
                break;
            case 10:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '*'){
                    estado = 10;
                }else if(charEntrada == '/'){
                    estado = 11;
                }else if(charEntrada == EOF){
                    estado = 42;
                    ungetc(charEntrada, fp);
                    coluna--;
                }else{
                    estado = 9;
                }
                break;
            case 11:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                
                // printf("(COMENTARIO)\n");
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                // return returnToken;
                break;
            case 12:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(ehLetra(charEntrada) || ehDigito(charEntrada) || charEntrada == '_'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);
                    estado = 13;
                }else{
                    estado = 14;
                }
                break;
            case 13:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(ehLetra(charEntrada) || ehDigito(charEntrada) || charEntrada == '_'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);
                    estado = 13;
                }else{
                    ungetc(charEntrada, fp);
                    coluna--;
                    estado = 14;
                }
                break;
            case 14:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                if(ehPalavraReservada(buffer)){
                    // printf("<TOKEN: PR, %s>\n",buffer);

                    returnToken.categoria = CAT_palavraReservada;
                    returnToken.codigo = numeroEnumPalavraReservada(buffer);
                    buffer[0] = '\0';
                }else{
                    strcpy(ID_TABLE[ ID_TABLE_TOPO ],buffer);
                    buffer[0] = '\0';                
                    returnToken.categoria = CAT_id;
                    returnToken.codigo = ID_TABLE_TOPO;
                    
                    ID_TABLE_TOPO++;
                }
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 15:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(ehDigito(charEntrada)){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 15;
                }else if(charEntrada=='.'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 17;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 16;
                }
                break;
            case 16:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                // printf("<TOKEN: CI, %s>\n",buffer);
                CT_I_TABLE[CT_I_TABLE_TOPO]= atoi(buffer);
                returnToken.categoria = CAT_constanteInteira;
                returnToken.codigo = CT_I_TABLE_TOPO;
                CT_I_TABLE_TOPO++;
                
                buffer[0] = '\0';                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 17:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(ehDigito(charEntrada)){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 18;
                }
                break;
            case 18:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(ehDigito(charEntrada)){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 18;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 19;
                }
                break;
            case 19:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                // printf("<TOKEN: CR, %s>\n",buffer);
                CT_R_TABLE[CT_R_TABLE_TOPO]=  atof(buffer); // converteStringParaReal(buffer);
                returnToken.categoria = CAT_constanteReal;
                returnToken.codigo = CT_R_TABLE_TOPO;
                CT_R_TABLE_TOPO++;


                buffer[0] = '\0';                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 20:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada != '\n'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 21;                    
                } else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 21:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada=='"'){
                    estado = 22;
                }else if(charEntrada != '\n'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 21;                    
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 22:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                // printf("<TOKEN: LT, \"%s\">\n",buffer);
                // printf("22->>%s %c\n", buffer, buffer[0]);
                strcpy(LT[LT_TOPO],buffer);
                returnToken.categoria = CAT_literal;
                returnToken.codigo = LT_TOPO;
                LT_TOPO++;

                buffer[0] = '\0';                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 23:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '\\'){
                    estado = 47;
                }else if( charEntrada != '\''){
                    sprintf(buffer,"%s%c",buffer,charEntrada);
                    estado = 24;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 24:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 25:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                // printf("<TOKEN: CC, '%s'>\n",buffer);
                // printf("25->>%s %c\n", buffer, buffer[0]);
                CT_C_TABLE[CT_C_TABLE_TOPO]= buffer[0];
                returnToken.categoria = CAT_constanteCaracter;
                returnToken.codigo = CT_C_TABLE_TOPO;
                CT_C_TABLE_TOPO++;

                buffer[0] = '\0';                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 26:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '='){
                    estado = 27;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 28;
                }
                break;
            case 27:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_maiorIgualQue;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 28:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_maiorQue;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 29:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '='){
                    estado = 30;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 31;
                }
                break;
            case 30:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_menorIgualQue;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 31:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_menorQue;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 32:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '='){
                    estado = 33;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 34;
                }
                break;
            case 33:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_difente;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 34:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_negacao;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 35:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '='){
                    estado = 36;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 37;
                }
                break;
            case 36:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_igualdade;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 37:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_atribuicao;
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 38:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_soma;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 39:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_subtracao;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 40:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_mutiplicacao;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 41:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_virgula;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 42:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                //EOF
                returnToken.categoria = CAT_fimDeArquivo;
                // printf("((EOF))\n");

                finalDeArquivo = true;
                return returnToken;
                break;
            case 43:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '|'){
                    estado = 44;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 44:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_ouCondicional;
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 45:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == '&'){
                    estado = 46;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 46:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                returnToken.categoria = CAT_sinais;
                returnToken.codigo = SN_eCondicional;
                
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 47:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada == 'n'){
                    sprintf(buffer,"%s%c",buffer,'\n');
                    estado = 48;
                }else if(charEntrada == 't'){
                    sprintf(buffer,"%s%c",buffer,'\t');
                    estado = 49;
                }else if(charEntrada == '0'){
                    sprintf(buffer,"%s%c",buffer,'\0');
                    estado = 50;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 48:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 49:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 50:if(debug){printf("E:%d  B:%s\n",estado,buffer);}
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 51:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                // printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 52:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                // printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            case 53:if(debug){printf("E:%d  B:%s\n",estado,buffer);} //FINAL
                // printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                return returnToken;
                break;
            
            default:
                printf("ESTADO INVALIDO, VERIFICAR CODIGO!");
                exit(1);
        }
        coluna++;
    }
}

