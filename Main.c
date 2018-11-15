#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    }else if(!strcmp(argv[1], "2") && (argc == 3)){
        //Funcionalidade 2 :
        REGISTRO *reg;
        int n;
        int teste = LeArquivo(&reg,argv[2],&n);
        if(teste == -1){
            printf("Falha no processamento.");
            return 0;
        }else if(teste == 0){
            printf("Arquivo Vazio.");
            return 0;
        }else{
            for(int i=0;i<n;i++)
                printf("%d %s %s %s \n",reg[i].campo1,reg[i].campo2,reg[i].campo3,reg[i].campo4);
    
        }

    }else if(!strcmp(argv[1], "3") && argc == 3){
        //Funcionalidade 3 :
        REGISTRO *reg;   //Cria um registro
        int n;           //Variável que irá guardar o numero de registros
        int teste = LeArquivo(&reg, argv[2], &n);   //Chama a função que lê o arquivo e o armazena no registro
        if(teste == -1){
            printf("Falha no processamento.");
            return 0;
        }else if(teste == 0){
            printf("Arquivo Vazio.");
            return 0;
        }else{
            mergeSort(&reg, 0, n);
            int cont = 0;
            if(GerarArquivo(n,reg,argv[2]))
                printf("Arquivo gerado.");
            else
                printf("Falha no processamento.");
            }
    }else{
        printf("Falha no processamento.\n");
    }
    return 0;
}