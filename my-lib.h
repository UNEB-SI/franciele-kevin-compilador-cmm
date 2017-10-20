// IDs
char ID_TABLE[1000][100];
int ID_TABLE_TOPO=0;
// Palavras reservadas
enum PR{
    inteiro=0,
    real,
    booleano,
    caracter,
    retorne,
    semretorno,
    semparam,
    se,
    para,
    enquanto,
    principal
};
#define NUM_PR_TABLE 12
char PR_TABLE[][50]={
    "inteiro",
    "real",
    "booleano",
    "caracter",
    "retorne",
    "semretorno",
    "semparam",
    "se",
    "senao",
    "para",
    "enquanto",
    "principal"
};

// Sinais
enum SN {
    SN_abreChaves = 0,
    SN_fechaChaves,
    SN_abreParenteses,
    SN_fechaParenteses,
    SN_pontoEVirgula,
    SN_divisao,
    SN_mutiplicacao,
    SN_soma,
    SN_subtracao,
    SN_virgula,
    SN_maiorQue,
    SN_maiorIgualQue,
    SN_menorQue,
    SN_menorIgualQue,
    SN_negacao,
    SN_difente,
    SN_atribuicao,
    SN_igualdade,
    SN_ouCondicional,
    SN_eCondicional
};
char SN_TABLE[][50]={
    "{",
    "}",
    "(",
    ")",
    ";",
    "/",
    "*",
    "+",
    "-",
    ",",
    ">",
    ">=",
    "<",
    "<=",
    "!",
    "!=",
    "=",
    "==",
    "||",
    "&&"
};

// Constantes
int CT_I_TABLE[100]; // inteiro
float CT_R_TABLE[100]; //real
char CT_C_TABLE[100]; //caracter

// Literais
char LT[1000][100];

// Outros
#define C_NovaLinha '\n';
#define C_Tab '\t';
#define C_Espaco '\b';


enum categoria{
    CAT_id,
    CAT_palavraReservada,
    CAT_sinais,
    CAT_constanteInteira,
    CAT_constanteReal,
    CAT_constanteCaracter,
    CAT_literal
};

char tabela_categoria[][100]={
    "Id",
    "Palavra Reservada",
    "Sinais",
    "Constante Inteira",
    "Constante Real",
    "Constante Caracter",
    "Literal" 
};

typedef struct token{
    int categoria; // qual categoria é 
    int codigo; // codigo 
}token;


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

void mensagemDeErro(char c,int linha,int coluna){
    

    printf("Erro em %d:%d\n",linha,coluna);
    
    printf("HEY YOU LITTLE PRICK!\n");
    printf("YOU BROKE THE RULES!\n");
    printf("COME HERE RIGHT NOW!\n");

    printf("THIS (%c) IS ILEGAL\n", c);
    exit(1);
}


// terminar isso aqui
// imprimir de acordo com a categoria
void mostraToken(token token){
    switch(token.categoria){
        case CAT_id:
            printf("<TOKEN: ID, %s>\n",ID_TABLE[token.codigo]);
            break;
        case CAT_palavraReservada:
            printf("<TOKEN: PALAVRA RESERVADA, %s>\n",PR_TABLE[token.codigo]);
            break;
        case CAT_sinais:
            printf("<TOKEN: SINAIS, %s>\n",SN_TABLE[token.codigo]);
            break;
        case CAT_constanteInteira:
            printf("<TOKEN: CONSTANTE INTEIRA, %d>\n",CT_I_TABLE[token.codigo]);
            break;
        case CAT_constanteReal:
            printf("<TOKEN: CONSTANTE REAL, %f>\n",CT_R_TABLE[token.codigo]);
            break;
        case CAT_constanteCaracter:
            printf("<TOKEN: CONSTANTE CARACTER, %c>\n",CT_C_TABLE[token.codigo]);
            break;
        case CAT_literal:
            printf("<TOKEN: LITERAL, %s>\n",LT[token.codigo]);
            break;
        default:
            printf("<TOKEN INVALIDO>\n");
            break;
    }
    
}