#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char const *argv[])
{
    
    if(!strcmp(argv[1],"1") && (argc==4)){
        //Funcionalidade 1 :
        int n = atoi(argv[3]);
        int* campo1 = (int*) malloc(n*sizeof(int));
        Gera_Campo1(n,campo1);
    }else{
        printf("Erro na pasagem de parâmetros\n");
    }
    return 0;
}

void Gera_Campo1(int n, int* vetor){
    int i;
    for(i=0;i<n;i++){
        vetor[i] = rand()%50000;
    }
}


