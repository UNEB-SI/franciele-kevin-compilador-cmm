// IDs
char ID_TABLE[1000][100];

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
    principal,
};
char PR_TABLE[][50]={
    "inteiro",
    "real",
    "booleano",
    "caracter",
    "retorne",
    "semretorno",
    "semparam",
    "se",
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
int CT_I_TABLE[100];
float CT_R_TABLE[100];
char CT_C_TABLE[100];

// Literais
char LT[1000][100];

// Outros
#define C_NovaLinha '\n';
#define C_Tab '\t';
#define C_Espaco '\b';



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
