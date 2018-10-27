#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char const *argv[])
{

    if (!strcmp(argv[1], "1") && (argc == 4))
    {
        //Funcionalidade 1 :
        int n = atoi(argv[3]);
        int *campo1 = (int *)malloc(n * sizeof(int));
        Gera_Campo1(n, campo1);
        char **campo2 = (char **)malloc(n * sizeof(char *));
        for (int i = 0; i < n; i++)
        {
            campo2[i] = (char *)malloc(30 * sizeof(char));
        }
    }
    else
    {
        printf("Erro na pasagem de parâmetros\n");
    }
    return 0;
}

void Gera_Campo1(int n, int *vetor)
{
    int i, indice;
    int *aux = (int*) malloc(50000*sizeof(int));
    for(i=0;i<50000;i++){
        aux[i] = i;
    }
    for (i = 0; i < n*0.7; i++){
        indice = rand()%50000;
        while(aux[indice]==(-1)){
            indice = rand()%50000;
        }
        vetor[i] = aux[indice];
        aux[indice] = -1;
    }
    indice = rand()%50000;
    while(aux[indice]==(-1)){
        indice = rand()%50000;
    }
    for(i=n*0.7;i<n;i++){
        vetor[i] = aux[indice];
    }
    /*for(i=0;i<n;i++){
        printf("%d ",vetor[i]);
    }*/
}

void Gera_Campo2(int n, char *vetor[])
{
    /*aux[100][30] = {"GOD", "WAR", "SNIPER", "FIGTH", "BAD", "WEAPON", "FIRE", "ARMY", "ADVANCED", "GHOST", "CHICKEN", "GROW", "HIGH", "MAGIC", "WORLD", "ROCK", "BATTLE", "SNOW", "GAME", "YELLOW", "CALL", "BLACK", "OPS", "HACKER", "SOLDIER", "ZOMBIE", "DRAGONS", "SHIELD", "COLOSSUS", "SHADOW", "DIRTY", "TITANS", "BREAKING", "CRAZY", "NIGTH", "MUTANTS",
    "HERO", "SPEED", "" };*/
}
