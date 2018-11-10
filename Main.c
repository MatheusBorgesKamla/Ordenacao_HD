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
        printf("Rodou !!");
    }else{
        printf("Erro na passagem de parâmetros\n");
    }
    return 0;
}