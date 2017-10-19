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
    fp = fopen("sample.cmm","r");
    int estado = 0;
    while( (charEntrada = fgetc(fp)) != EOF ){
        //printf("%c",charEntrada);
        //printf("estado atual %d\tlendo char '%c'\n",estado,charEntrada);
        switch(estado){
            case 0:
                // abre chaves
                if(charEntrada== '{') estado = 1;
                // fecha chaves
                if(charEntrada== '}') estado = 2;
                // abre parenteses
                if(charEntrada== '(') estado = 3;
                // fecha parenteses
                if(charEntrada== ')') estado = 4;
                // ponto e virgula
                if(charEntrada== ';') estado = 5;
                // divisão ou comentario
                if(charEntrada== '/') estado = 6;
                // palavra reservada ou ID
                if(ehLetra(charEntrada)){
                    ungetc(charEntrada, fp);
                    estado = 12;
                }
                // numero inteiro ou real
                if(ehDigito(charEntrada)){
                    ungetc(charEntrada, fp);
                    estado = 15;
                }
                // Cadeia de caracteres
                if(charEntrada== '"') estado = 20;
                // caracter
                if(charEntrada== '\'') estado = 23;
                // maior ou maior e igual
                if(charEntrada== '>') estado = 26;
                // menor ou menor e igual
                if(charEntrada== '<') estado = 29;
                // negação ou diferente
                if(charEntrada== '!') estado = 32;
                // igualdade ou atribuição
                if(charEntrada== '=') estado = 35;
                // soma
                if(charEntrada== '+') estado = 38;
                // subtração
                if(charEntrada== '-') estado = 39;
                // multiplicaçõa
                if(charEntrada== '*') estado = 40;
                // virgula
                if(charEntrada== ',') estado = 41;
                // maior ou maior e igual
                // if(charEntrada== EOF) estado = 2;
                // não entra fim de arquivo

                // ou condicional
                if(charEntrada== '|') estado = 43;
                // e condicional
                if(charEntrada== '&') estado = 45;

                // RETRO ALIMENTAÇÂO

                // maior ou maior e igual
                if(charEntrada== '\n' || charEntrada== '\t' ||charEntrada== '\b') estado = 0;
                break;
            case 1:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_abreChaves;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 2:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_fechaChaves;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 3:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_abreParenteses;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 4:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_fechaParenteses;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 5:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_pontoEVirgula;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 6:
                // comentario
                if(charEntrada == '*'){ 
                    estado = 8;
                //divisão
                }else{
                    ungetc(charEntrada, fp);
                    estado = 7;
                }
                break;
            case 7:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_divisao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 8:
                if(charEntrada == '*'){
                    estado = 10;
                }else{
                    estado = 9;
                }
                break;
            case 9:
                if(charEntrada == '*'){
                    estado = 10;
                }else{
                    estado = 9;
                }
                break;
            case 10:
                if(charEntrada == '*'){
                    estado = 10;
                }else if(charEntrada == '/'){
                    estado = 11;
                }else{
                    estado = 9;
                }
                break;
            case 11:
                // temptoken.categoria = CAT_sinais;
                // temptoken.codigo = SN_divisao;
                // mostraToken(temptoken);
                printf("(COMENTARIO)\n");
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
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
                    estado = 14;
                }
                break;
            case 14:
                strcpy(ID_TABLE[ ID_TABLE_TOPO ],buffer);
                buffer[0] = '\0';                
                temptoken.categoria = CAT_id;
                temptoken.codigo = ID_TABLE_TOPO;
                mostraToken(temptoken);
                ID_TABLE_TOPO++;
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
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
                    estado = 16;
                }
                break;
            case 16:
                printf("<TOKEN: CI, %s>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
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
                    estado = 19;
                }
                break;
            case 19:
                printf("<TOKEN: CR, %s>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 20:
                if(charEntrada != '\n'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 21;                    
                }
                break;
            case 21:
                if(charEntrada=='"'){
                    estado = 22;
                }else if(charEntrada != '\n'){
                    sprintf(buffer,"%s%c",buffer,charEntrada);                    
                    estado = 21;                    
                }
                break;
            case 22:
                printf("<TOKEN: LT, \"%s\">\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 23:
                if(charEntrada != '\\' && charEntrada != '\''){
                    sprintf(buffer,"%s%c",buffer,charEntrada);
                    estado = 24;
                }
                break;
            case 24:
                if(charEntrada=='\''){
                    estado = 25;
                }
                break;
            case 25:
                printf("<TOKEN: CC, '%s'>\n",buffer);
                buffer[0] = '\0';                
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 26:
                if(charEntrada == '='){
                    estado = 27;
                }else{
                    ungetc(charEntrada,fp);
                    estado = 28;
                }
                break;
            case 27:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_maiorIgualQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 28:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_maiorQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 29:
                if(charEntrada == '='){
                    estado = 30;
                }else{
                    ungetc(charEntrada,fp);
                    estado = 31;
                }
                break;
            case 30:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_menorIgualQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 31:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_menorQue;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 32:
                if(charEntrada == '='){
                    estado = 33;
                }else{
                    ungetc(charEntrada,fp);
                    estado = 34;
                }
                break;
            case 33:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_difente;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 34:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_negacao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 35:
                if(charEntrada == '='){
                    estado = 36;
                }else{
                    ungetc(charEntrada,fp);
                    estado = 37;
                }
                break;
            case 36:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_igualdade;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 37:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_atribuicao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 38:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_soma;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 39:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_subtracao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 40:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_mutiplicacao;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 41:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_virgula;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 42:
                //EOF
                break;
            case 43:
                if(charEntrada == '|'){
                    estado = 44;
                }
                break;
            case 44:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_ouCondicional;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            case 45:
                if(charEntrada == '&'){
                    estado = 46;
                }
                break;
            case 46:
                temptoken.categoria = CAT_sinais;
                temptoken.codigo = SN_eCondicional;
                mostraToken(temptoken);
                // fseek(fp,-1, SEEK_CUR);
                ungetc(charEntrada, fp);
                estado = 0;
                break;
            default:
                printf("ESTADO INVALIDO, VERIFICAR CODIGO!");
                exit(1);
        }
    }
        
    fclose(fp);

}


