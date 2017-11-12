#ifndef ANALEX
#define ANALEX

// TOKEN ------------------------------------------------------------------------------
typedef struct token{
    int categoria;
    int codigo;
}token;

// IDs ------------------------------------------------------------------------------
char ID_TABLE[1000][100];
int ID_TABLE_TOPO=0;

// Palavras reservadas ------------------------------------------------------------------------------
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

// Sinais ------------------------------------------------------------------------------
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

// Constantes ------------------------------------------------------------------------------
int CT_I_TABLE[100]; // inteiro
float CT_R_TABLE[100]; //real
char CT_C_TABLE[100]; //caracter

// Literais ------------------------------------------------------------------------------
char LT[1000][100];

// Outros
#define C_NovaLinha '\n';
#define C_Tab '\t';
#define C_Espaco '\b';

//  Categorias ------------------------------------------------------------------------------
enum categoria{
    CAT_id,
    CAT_palavraReservada,
    CAT_sinais,
    CAT_constanteInteira,
    CAT_constanteReal,
    CAT_constanteCaracter,
    CAT_literal,
    CAT_fimDeArquivo
};

char tabela_categoria[][100]={
    "Id",
    "Palavra Reservada",
    "Sinais",
    "Constante Inteira",
    "Constante Real",
    "Constante Caracter",
    "Literal",
    "EOF"
};


#endif // ANALEX