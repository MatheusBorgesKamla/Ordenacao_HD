#ifndef _H_CODE
#define _H_CODE

typedef struct registros{
    int campo1;
    char campo2[30];
    char campo3[20];
    char campo4[10];
}REGISTRO;
void GeraDados(int n, REGISTRO *reg);
void Gera_Campo1(int n, int *vetor);
void Gera_Campo2(int n, char *vetor[]);
void Gera_Campo3(int n, char *vetor[]);
void Gera_Campo4(int n, char *vetor[]);


#endif 