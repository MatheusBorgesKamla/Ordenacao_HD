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

int mergeArq(char *arq_name1, char *arq_name2, char *arq_fname);

int matching(char *arq_name1, char *arq_name2, char *arq_fname);

int compara_reg(REGISTRO reg1, REGISTRO reg2);

int sortMerge(char *arq_name, char *arq_fname);

int recursive_sortMerge(int n_arq, int cont, int sobra, char *arq_fnam);
#endif 
