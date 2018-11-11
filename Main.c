#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Code.h"

int main(int argc, char const *argv[])
{

    if (!strcmp(argv[1], "1") && (argc == 4)){
        //Funcionalidade 1 :
        int n = atoi(argv[3]);
        REGISTRO *reg = (REGISTRO *)malloc(n*sizeof(REGISTRO));
        GeraDados(n,reg);
        if(GerarArquivo(n,reg,argv[2])){
            printf("Arquivo gerado.");
        }else{
            printf("Falha no processamento.");
        }
    }else{
        printf("Falha no processamento.\n");
    }
    return 0;
}