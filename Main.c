#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Code.h"

int main(int argc, char const *argv[])
{

    if (!strcmp(argv[1], "1") && (argc == 4))
    {
        //Funcionalidade 1 :
        int n = atoi(argv[3]);
        REGISTRO *reg = (REGISTRO *)malloc(n * sizeof(REGISTRO));
        GeraDados(n, reg);
        if (GerarArquivo(n, reg, argv[2]))
        {
            printf("Arquivo gerado.");
        }
        else
        {
            printf("Falha no processamento.");
        }
        free(reg);
    }
    else if (!strcmp(argv[1], "2") && (argc == 3))
    {
        //Funcionalidade 2 :
        REGISTRO *reg;
        int n;
        int teste = LeArquivo(&reg, argv[2], &n);
        if (teste == -1)
        {
            printf("Falha no processamento.");
        }
        else if (teste == 0)
        {
            printf("Arquivo Vazio.");
        }
        else
        {
            for (int i = 0; i < n; i++)
                printf("%d %s %s %s \n",reg[i].campo1, reg[i].campo2, reg[i].campo3, reg[i].campo4);
        }
        free(reg);
    }
    else if (!strcmp(argv[1], "3") && argc == 4)
    {
        //Funcionalidade 3 :
        REGISTRO *reg;                            //Cria um registro
        int n;                                    //Variável que irá guardar o numero de registros
        int teste = LeArquivo(&reg, argv[2], &n); //Chama a função que lê o arquivo e o armazena no registro
        if (teste == -1)
        {
            printf("Falha no processamento.");
        }
        else if (teste == 0)
        {
            printf("Arquivo Vazio.");
        }
        else
        {
            mergeSort(&reg, 0, n-1);
            if (GerarArquivo(n, reg, argv[3]))
                printf("Arquivo gerado.");
            else
                printf("Falha no processamento.");
        }
        free(reg);
    }
    else if (!strcmp(argv[1], "4") && argc == 5)
    {
        //Funcionalidade 4 :
        int teste = mergeArq(argv[2], argv[3], argv[4]);
        if (teste == -1)
        {
            printf("Falha no processamento.");
        }
        else if (teste == 0)
        {
            printf("Arquivo Vazio.");
        }
        else
        {
            printf("Arquivo gerado.");
        }
    }
    else if (!strcmp(argv[1], "5") && argc == 5)
    {
        //Funcionalidade 5 :
        REGISTRO *reg1, *reg2;
        int teste = matching(argv[2], argv[3], argv[4]);
        if (teste == -1)
        {
            printf("Falha no processamento.");
        }
        else if (teste == 0)
        {
            printf("Arquivo Vazio.");
        }
        else
        {
            printf("Arquivo gerado.");
        }
        
    }
    else if(!strcmp(argv[1], "6") && argc >= 5)
    {
        char **arquivos_name = (char **) malloc((argc-2)*sizeof(char*));
        int j = 0;
        for(int i = 2; i < argc-1; i++)
        {
            arquivos_name[j] = argv[i];
            j++;
        }
        int teste = multiway_merging(arquivos_name, argv[argc-1] ,j); 
        if(teste == -1)
            printf("Falha no processamento.");
        else if(teste == 0)
            printf("Um dos arquivos esta vazio.");
        else
            printf("Arquivo gerado.");

        free(arquivos_name);
    }
    else if (!strcmp(argv[1], "7") && argc == 4)
    {
        //Funcionalidade 7 :
        int teste = sortMerge(argv[2],argv[3]); 
        if (teste == -1)
        {
            printf("Falha no processamento.");
        }
        else if (teste == 0)
        {
            printf("Arquivo Vazio.");
        }
        else
        {

            printf("Arquivo gerado.");
        }        
    }
    else
    {
        printf("Erro passagem de parametros");
    }
    return 0;
}