#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "my-lib.h"

token temptoken;
void main(){
    FILE *fp;
    char charEntrada;
    char buffer[1000]="";
    fp = fopen("sample1.cmm","r");
    int estado = 0;
    int linha=1;
    int coluna=1;
    bool finalDeArquivo = false;
//    while( (charEntrada = fgetc(fp)) != EOF ){

    while( !finalDeArquivo ){
        charEntrada = fgetc(fp);

        //printf("%c",charEntrada);
        //printf("estado atual %d\tlendo char '%c'\n",estado,charEntrada);
        
        //printf(":%d:%d ->'%c'\n",linha,coluna,charEntrada);
        switch(estado){
            case 0: //INICIAL
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
            case 1: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_abreChaves;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 2: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_fechaChaves;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 3: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_abreParenteses;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 4: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_fechaParenteses;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 5: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_pontoEVirgula;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 6:
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
            case 7: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_divisao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 8:
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
            case 9:
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
            case 10:
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
            case 11: //FINAL
                // temptoken.categoria = CAT_sinais;
                // temptoken.codigo = SN_divisao;
                // mostraToken(temptoken);
                printf("(COMENTARIO)\n");
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 12:
                if(ehLetra(charEntrada) || ehDigito(charEntrada) || charEntrada == '_'){
                    // strcat(charEntrada, ID_TABLE[ ID_TABLE_TOPO ] );
                    sprintf(buffer,"%s%c",buffer,charEntrada);
                    estado = 13;
                }else{
                    estado = 14;
                }
                break;
            case 13:
                if(ehLetra(charEntrada) || ehDigito(charEntrada) || charEntrada == '_'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);
                    estado = 13;
                }else{
                    ungetc(charEntrada, fp);
                    coluna--;
                    estado = 14;
                }
                break;
            case 14: //FINAL
                if(ehPalavraReservada(buffer)){
                    printf("<TOKEN: PR, %s>\n",buffer);
                    buffer[0] = '\0';
                }else{
                    strcpy(ID_TABLE[ ID_TABLE_TOPO ],buffer);
                    buffer[0] = '\0';                
                    temptoken.categoria = CAT_id;
                    temptoken.codigo = ID_TABLE_TOPO;
                    mostraToken(temptoken);
                    ID_TABLE_TOPO++;
                }
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 15:
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
            case 16: //FINAL
                printf("<TOKEN: CI, %s>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 17:
                if(ehDigito(charEntrada)){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 18;
                }
                break;
            case 18:
                if(ehDigito(charEntrada)){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 18;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 19;
                }
                break;
            case 19: //FINAL
                printf("<TOKEN: CR, %s>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 20:
                if(charEntrada != '\n'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 21;                    
                } else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 21:
                if(charEntrada=='"'){
                    estado = 22;
                }else if(charEntrada != '\n'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 21;                    
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 22: //FINAL
                printf("<TOKEN: LT, \"%s\">\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 23:
                if(charEntrada == '\\'){
                    estado = 47;
                }else if( charEntrada != '\''){
                    sprintf(buffer,"%s%c",buffer,charEntrada);
                    estado = 24;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 24:
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 25: //FINAL
                printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 26:
                if(charEntrada == '='){
                    estado = 27;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 28;
                }
                break;
            case 27: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_maiorIgualQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 28: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_maiorQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 29:
                if(charEntrada == '='){
                    estado = 30;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 31;
                }
                break;
            case 30: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_menorIgualQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 31: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_menorQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 32:
                if(charEntrada == '='){
                    estado = 33;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 34;
                }
                break;
            case 33: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_difente;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 34: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_negacao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 35:
                if(charEntrada == '='){
                    estado = 36;
                }else{
                    ungetc(charEntrada,fp);
                    coluna--;
                    estado = 37;
                }
                break;
            case 36: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_igualdade;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 37: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_atribuicao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 38: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_soma;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 39: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_subtracao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 40: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_mutiplicacao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 41: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_virgula;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 42:
                //EOF
                printf("((EOF))\n");
                finalDeArquivo = true;
                break;
            case 43:
                if(charEntrada == '|'){
                    estado = 44;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 44: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_ouCondicional;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 45:
                if(charEntrada == '&'){
                    estado = 46;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 46: //FINAL
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_eCondicional;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 47:
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
            case 48:
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 49:
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 50:
                if(charEntrada=='\''){
                    estado = 25;
                }else mensagemDeErro(fp,charEntrada,linha,coluna);
                break;
            case 51: //FINAL
                printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 52: //FINAL
                printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            case 53: //FINAL
                printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                coluna--;
                estado = 0;
                break;
            
            default:
                printf("ESTADO INVALIDO, VERIFICAR CODIGO!");
                exit(1);
        }
        coluna++;
    }
        
    fclose(fp);

}


