#ifndef _H_CODE
#define _H_CODE

typedef struct registros{
    int campo1;
    char campo2[30];
    char campo3[20];
    char campo4[11];
}REGISTRO;
void GeraDados(int n, REGISTRO *reg);
int GerarArquivo(int n, REGISTRO *reg, char* arq_name);
int LeArquivo(REGISTRO **reg, char* arq_name, int *n);
void Gera_Campo1(int n, int *vetor);
void Gera_Campo2(int n, char *vetor[]);
void Gera_Campo3(int n, char *vetor[]);
void Gera_Campo4(int n, char *vetor[]);

void merge(REGISTRO **reg, int comeco, int meio, int fim); //Ordena internamente os registros através de um merge sort
void mergeSort(REGISTRO **reg, int comeco, int fim);


#endif 
