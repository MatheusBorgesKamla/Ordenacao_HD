#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Code.h"

void GeraDados(int n, REGISTRO *reg)
{
    int *campo1 = (int *)malloc(n * sizeof(int));
    char **campo2 = (char **)malloc(n * sizeof(char *));
    char **campo3 = (char **)malloc(n * sizeof(char *));
    char **campo4 = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        campo2[i] = (char *)malloc(30 * sizeof(char));
        campo3[i] = (char *)malloc(20 * sizeof(char));
        campo4[i] = (char *)malloc(11 * sizeof(char));
    }
    Gera_Campo1(n, campo1);
    Gera_Campo2(n, campo2);
    Gera_Campo3(n, campo3);
    Gera_Campo4(n, campo4);
    for (int i = 0; i < n; i++)
    {
        reg[i].campo1 = campo1[i];
        strcpy(reg[i].campo2, campo2[i]);
        strcpy(reg[i].campo3, campo3[i]);
        strcpy(reg[i].campo4, campo4[i]);
        //printf("REGISTRO[%d] : %d | %s | %s | %s --",(i+1),reg[i].campo1,reg[i].campo2,reg[i].campo3,reg[i].campo4);
    }
    free(campo1);
    free(campo2);
    free(campo3);
    free(campo4);
}

int GerarArquivo(int n, REGISTRO *reg, char *arq_name)
{
    FILE *arq = fopen(arq_name, "w+b");
    if (arq == NULL)
    {
        return 0;
    }
    char status = '0';
    fwrite(&status, sizeof(char), 1, arq);
    fwrite(reg, sizeof(REGISTRO), n, arq);
    status = '1';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fclose(arq);
    return 1;
}

int LeArquivo(REGISTRO **reg, char *arq_name, int *n)
{
    FILE *arq = fopen(arq_name, "r+b");
    if (arq == NULL)
    {
        return -1;
    }
    /* Pula até o fim do arquivo */
    fseek(arq, 0, SEEK_END);
    /* Lê o indicador de posição (em bytes)*/
    *n = ftell(arq);
    if (*n == 0)
    {
        //Arquivo vazio
        fclose(arq);
        return 0;
    }
    *n = *n - sizeof(char);
    *n = *n / (sizeof(REGISTRO));
    *reg = (REGISTRO **)malloc((*n) * sizeof(REGISTRO));
    char status = '0';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fseek(arq, sizeof(char), SEEK_SET);
    fread(*reg, sizeof(REGISTRO), *n, arq);
    status = '1';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fclose(arq);
    return 1;
}

void Gera_Campo1(int n, int *vetor)
{
    int i, indice;
    int *aux = (int *)malloc(50000 * sizeof(int));
    for (i = 0; i < 50000; i++)
    {
        aux[i] = i;
    }
    for (i = 0; i < n * 0.7; i++)
    {
        indice = rand() % 50000;
        while (aux[indice] == (-1))
        {
            indice = rand() % 50000;
        }
        vetor[i] = aux[indice];
        aux[indice] = -1;
    }
    /*indice = rand()%50000;
    while(aux[indice]==(-1)){
        indice = rand()%50000;
    }
    for(i=n*0.7;i<n;i++){
        vetor[i] = aux[indice];
    }*/
    i = 0.7 * n;
    while (i < n)
    {
        indice = rand() % 50000;
        while (aux[indice] == (-1))
        {
            indice = rand() % 50000;
        }
        vetor[i] = aux[indice];
        vetor[i + 1] = aux[indice];
        aux[indice] = -1;
        i += 2;
    }
}

void Gera_Campo2(int n, char *vetor[])
{
    int i, j, k, indice;
    char aux[100][10] = {"GOD", "WAR", "SNIPER", "FIGHT", "BAD", "WEAPON", "FIRE", "ARMY", "ADVANCED", "GHOST", "CHICKEN", "GROW", "HIGH", "MAGIC", "WORLD", "ROCK", "BATTLE", "SNOW", "GAME", "YELLOW", "CALL", "BLACK", "OPS", "HACKER", "SOLDIER", "ZOMBIE", "DRAGONS", "SHIELD", "COLOSSUS", "SHADOW", "DIRTY", "TITANS", "BREAKING", "CRAZY", "NIGHT", "MUTANTS",
                         "HERO", "SPEED", "RACE", "SUN", "AGE", "EMPIRE", "WAKE", "AMNESIA", "AQUA", "LEGEND", "COUNTER", "KINGS", "DARK", "WATCH", "DOGS", "ORIGINS", "DEFEAT", "DAY", "DIRT", "EURO", "FAR", "CRY", "HONOR", "SIMULATOR", "DESTINY", "GRAND", "HITMAN", "BIOSHOCK", "BOARD", "CAUSE", "LAYERS", "DEAD", "LIFE", "STRANGE", "MAFIA", "MEDAL", "EARTH", "GOAT", "ORCS", "PORTAL", "ROCKET", "SLEEPING", "STAR", "SUPREME", "SURGEON", "TEAM", "FOREST", "WITCHER", "TROPICO", "TIBIA", "RAINBOW", "TALES", "ZELDA", "AUTO", "SIEGE", "ELDER", "SCROLL", "FARM", "HOTEL", "QUAKE", "HALF", "FEAR", "SOULS", "GREAT"};
    char strings[9901][30];
    for (i = 0; i < 100; i++)
    {
        strcpy(strings[i], aux[i]);
    }
    int cont = 100;
    for (j = 0; j < 100; j++)
    {
        for (i = (j + 1); i < 100; i++)
        {
            strcpy(strings[cont], strings[j]);
            strcat(strings[cont], " ");
            strcat(strings[cont], strings[i]);
            cont++;
        }
    }
    for (j = 0; j < 100; j++)
    {
        for (i = (j + 1); i < 100; i++)
        {
            for (k = (i + 1); k < 100; k++)
            {
                strcpy(strings[cont], strings[j]);
                strcat(strings[cont], " ");
                strcat(strings[cont], strings[i]);
                strcat(strings[cont], " ");
                strcat(strings[cont], strings[k]);
                cont++;
            }
            break;
        }
    }
    /*printf("Contador: %d",cont);
    for(i=0;i<9901;i++){
        printf("%s -",strings[i]);
    }*/
    for (i = 0; i < n * 0.75; i++)
    {
        indice = rand() % 9901;
        while (!strcmp(strings[indice], "*"))
        {
            indice = rand() % 9901;
        }
        strcpy(vetor[i], strings[indice]);
        strcpy(strings[indice], "*");
    }
    /*indice = rand()%9901;
    while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
    }
    for(i=n*0.75;i<n;i++){
        strcpy(vetor[i],strings[indice]);
    }*/
    i = 0.75 * n;
    while (i < n)
    {
        indice = rand() % 9901;
        while (!strcmp(strings[indice], "*"))
        {
            indice = rand() % 9901;
        }
        strcpy(vetor[i], strings[indice]);
        strcpy(vetor[i + 1], strings[indice]);
        strcpy(strings[indice], "*");
        i += 2;
    }
}

void Gera_Campo3(int n, char *vetor[])
{
    int i, j, k, indice;
    char aux[100][20] = {"UBI", "NINTENDO", "MICRO", "EA", "LG", "ROCKSTAR", "NEW", "ATLAS", "SIRIUS", "GIGA", "RIO", "BIT", "ROCKLAND", "WIZARD", "SWIFT", "AMAZON", "MANAGER", "YORK", "APPLE", "SILICON", "JDK", "ORACLE", "SYSTEM", "WARNER", "MARVEL", "SONY", "ACER", "LENOVO", "HP", "ATARI", "SPACE", "FOX", "DIGITAL", "PLAY", "SIMS", "SAMSUNG",
                         "RISE", "EUREKA", "RACE", "ALPHA", "LAMBDA", "OPEN", "CENTER", "WIN", "LINUX", "WIND", "HOME", "UPCOMING", "RECALL", "DATABASE", "RIDDLE", "AZTEC", "CELLAR", "FORSALE", "APEX", "INFLUENCE", "QUILL", "VS", "VISUAL", "UBUNTU", "TEXT", "MOZILA", "GOOGLE", "SEARCH", "CONFIG", "SIGMA", "TETA", "ADAPTER", "CAPCOM", "PENTA", "ROBOTIC", "SUBLIME", "SCIENCE", "GORILLA", "ULTIMATE", "LONDON", "ASUS", "UMBRELLA", "CIRCUIT", "ENJOY", "COOL", "ABSTRACT", "TOOL", "GARBAGE", "LOAD", "PROGRESS", "INC", "CODE", "STUDIO", "ENG", "DEVELOPMENT", "STOKE", "TECH", "JUNIOR", "GAMES", "SOFT", "ORG", "FOUND", "S.A.", "CORP"};
    char strings[9901][20];
    for (i = 0; i < 100; i++)
    {
        strcpy(strings[i], aux[i]);
    }
    int cont = 100;
    for (j = 0; j < 100; j++)
    {
        for (i = (j + 1); i < 100; i++)
        {
            strcpy(strings[cont], strings[j]);
            strcat(strings[cont], " ");
            strcat(strings[cont], strings[i]);
            cont++;
        }
    }
    int tam, res;
    char aux2[20];
    for (j = 0; j < 100; j++)
    {
        for (i = (j + 1); i < 100; i++)
        {
            for (k = (i + 1); k < 100; k++)
            {
                strcpy(strings[cont], strings[j]);
                strcat(strings[cont], " ");
                strcat(strings[cont], strings[i]);
                strcat(strings[cont], " ");
                tam = strlen(strings[cont]) + strlen(strings[k]);
                //printf("tam = %d ",tam);
                if (tam >= 20)
                {
                    res = 19 - strlen(strings[cont]);
                    strcpy(aux2, strings[k]);
                    aux2[res] = '\0';
                    //printf("res = %d  %s",res,aux2);
                    strcat(strings[cont], aux2);
                    //printf("-- teste --");
                    //printf("%s ",strings[cont]);
                }
                else
                {
                    strcat(strings[cont], strings[k]);
                }
                cont++;
            }
            break;
        }
    }
    /*printf("Contador: %d",cont);
    for(i=0;i<9901;i++){
        printf("- %s  -",strings[i]);
    }*/
    for (i = 0; i < n * 0.8; i++)
    {
        indice = rand() % 9901;
        while (!strcmp(strings[indice], "*"))
        {
            indice = rand() % 9901;
        }
        strcpy(vetor[i], strings[indice]);
        strcpy(strings[indice], "*");
    }
    /*indice = rand()%9901;
    while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
    }
    for(i=n*0.8;i<n;i++){
        strcpy(vetor[i],strings[indice]);
    }*/
    i = 0.8 * n;
    while (i < n)
    {
        indice = rand() % 9901;
        while (!strcmp(strings[indice], "*"))
        {
            indice = rand() % 9901;
        }
        strcpy(vetor[i], strings[indice]);
        strcpy(vetor[i + 1], strings[indice]);
        strcpy(strings[indice], "*");
        i += 2;
    }
}

void Gera_Campo4(int n, char *vetor[])
{
    int i, j, k, indice;
    char dia[30][4] = {"01/", "02/", "03/", "04/", "05/", "06/", "07/", "08/", "09/",
                       "10/", "11/", "12/", "13/", "14/", "15/", "16/", "17/", "18/", "19/", "20/", "21/",
                       "22/", "23/", "24/", "25/", "26/", "27/", "28/", "29/", "30/"};
    char mes[12][4] = {"01/", "02/", "03/", "04/", "05/", "06/", "07/", "08/", "09/",
                       "10/", "11/", "12/"};
    char ano[29][5] = {"1990", "1991", "1992", "1993", "1994", "1995", "1996", "1997", "1998", "1999",
                       "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018"};
    char strings[10440][11];
    int cont = 0;
    for (i = 0; i < 29; i++)
    {
        for (j = 0; j < 12; j++)
        {
            for (k = 0; k < 30; k++)
            {
                strcpy(strings[cont], dia[k]);
                strcat(strings[cont], mes[j]);
                strcat(strings[cont], ano[i]);
                cont++;
            }
        }
    }
    /*printf("Contador: %d",cont);
    for(i=0;i<10440;i++){
        printf("%s -",strings[i]);
    }*/

    for (i = 0; i < n * 0.85; i++)
    {
        indice = rand() % 10440;
        while (!strcmp(strings[indice], "*"))
        {
            indice = rand() % 10440;
        }
        strcpy(vetor[i], strings[indice]);
        strcpy(strings[indice], "*");
    }
    /*indice = rand()%10440;
    while(!strcmp(strings[indice],"*")){
            indice = rand()%10440;
    }
    for(i=n*0.85;i<n;i++){
        strcpy(vetor[i],strings[indice]);
    }*/
    i = 0.85 * n;
    while (i < n)
    {
        indice = rand() % 10440;
        while (!strcmp(strings[indice], "*"))
        {
            indice = rand() % 10440;
        }
        strcpy(vetor[i], strings[indice]);
        strcpy(vetor[i + 1], strings[indice]);
        strcpy(strings[indice], "*");
        i += 2;
    }
}

void merge(REGISTRO **reg, int comeco, int meio, int fim)
{

    // int auxC2 = 0, auxC3 = 0, auxC4 = 0; //Variáveis auxiliares para a comparação de strings

    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    REGISTRO *vetAux = (REGISTRO *)malloc(tam * sizeof(REGISTRO));

    while (com1 <= meio && com2 <= fim)
    {

        if (reg[0][com1].campo1 < reg[0][com2].campo1)
        {
            vetAux[comAux] = reg[0][com1];
            com1++;
        }
        else if (reg[0][com1].campo1 > reg[0][com2].campo1)
        {
            vetAux[comAux] = reg[0][com2];
            com2++;
        }
        else if (reg[0][com1].campo1 == reg[0][com2].campo1) //Se o campo1 dos dois registros forem iguais, analisa o campo2
        {
            int length1C2 = strlen(reg[0][com1].campo2), length2C2 = strlen(reg[0][com2].campo2), lenAuxC2; //Pega o tamanho de cada string
            if (length1C2 < length2C2)                                                                      //Aloca no lenAuxC2 o menor tamanho de string
                lenAuxC2 = length1C2;
            else
                lenAuxC2 = length2C2;

            int compareC2 = 0;                 //Variável que serve para dar um status na comparação das strings
            for (int i = 0; i < lenAuxC2; i++) //Faz um for que vai percorrer as strings comparando char por char
            {
                if (reg[0][com1].campo2[i] < reg[0][com2].campo2[i]) //Se o caractere 1 for menor que o 2, compareC2 recebe um valor negativo
                {
                    compareC2 = -1;
                    break;
                }
                else if (reg[0][com1].campo2[i] > reg[0][com2].campo2[i]) //Se o caractere 1 for maior que o 2, compareC2 recebe um valor positivo
                {
                    compareC2 = 1;
                    break;
                }
            }

            if (compareC2 < 0) //Se compareC2 for menor do que zero, o conteúdo da string 1 é menor que o da string 2
            {
                vetAux[comAux] = reg[0][com1];
                com1++;
            }
            else if (compareC2 > 0) //compareC2 maior do que zero --> conteúdo da string1 é maior do que string2
            {
                vetAux[comAux] = reg[0][com2];
                com2++;
            }
            else if (compareC2 == 0) //Se compareC2 for igual a zero, o conteúdo das duas string é igual
            {                        //Nesse caso, passa para o próximo campo para fazer a análise

                int length1C3 = strlen(reg[0][com1].campo3), length2C3 = strlen(reg[0][com2].campo3), lenAuxC3; //Pega o tamanho de cada string
                if (length1C3 < length2C3)                                                                      //Aloca no lenAuxC3 o menor tamanho de string
                    lenAuxC3 = length1C3;
                else
                    lenAuxC3 = length2C3;

                int compareC3;                     //Variável que serve para dar um status na comparação das strings
                for (int i = 0; i < lenAuxC3; i++) //Faz um for que vai percorrer as strings comparando char por char
                {
                    if (reg[0][com1].campo3[i] < reg[0][com2].campo3[i]) //Se o caractere 1 for menor que o 2, compareC3 recebe um valor negativo
                    {
                        compareC3 = -1;
                        break;
                    }
                    else if (reg[0][com1].campo3[i] > reg[0][com2].campo3[i]) //Se o caractere 1 for maior que o 2, compareC2 recebe um valor positivo
                    {
                        compareC3 = 1;
                        break;
                    }
                    else if (reg[0][com1].campo3[i] == reg[0][com2].campo3[i])
                    {
                        if (i == (lenAuxC3 - 1))
                            compareC3 = 0;
                    }
                }
                if (compareC3 < 0) //Se compareC3 for menor do que zero, o conteúdo da string 1 é menor que o da string 2
                {
                    vetAux[comAux] = reg[0][com1];
                    com1++;
                }
                else if (compareC3 > 0) //compareC3 maior do que zero --> conteúdo da string1 é maior do que string2
                {
                    vetAux[comAux] = reg[0][com2];
                    com2++;
                }
                else if (compareC3 == 0) //Se compareC3 for igual a zero, o conteúdo das duas string é igual
                {
                    int compareC4 = 0;           //Variável que serve para dar um status na comparação das strings
                    for (int i = 6; i < 10; i++) //Faz um for que vai percorrer as strings comparando char por char
                    {
                        if (reg[0][com1].campo4[i] < reg[0][com2].campo4[i]) //Se o caractere 1 for menor que o 2, compareC4 recebe um valor negativo
                        {
                            compareC4 = -1;
                            break;
                        }
                        if (reg[0][com1].campo4[i] > reg[0][com2].campo4[i]) //Se o caractere 1 for maior que o 2, compareC4 recebe um valor positivo
                        {
                            compareC4 = 1;
                            break;
                        }
                    }
                    if (compareC4 == 0)
                    {
                        if (reg[0][com1].campo4[4] < reg[0][com2].campo4[3] || reg[0][com1].campo4[3] < reg[0][com2].campo4[3])
                        {
                            compareC4 = -1;
                        }
                        else if (reg[0][com1].campo4[4] > reg[0][com2].campo4[4] || reg[0][com1].campo4[3] > reg[0][com2].campo4[3])
                        {
                            compareC4 = 1;
                        }
                        else
                        {
                            if (reg[0][com1].campo4[0] < reg[0][com2].campo4[0] || reg[0][com1].campo4[1] < reg[0][com2].campo4[1])
                            {
                                compareC4 = -1;
                            }
                            if (reg[0][com1].campo4[0] > reg[0][com2].campo4[0] || reg[0][com1].campo4[1] > reg[0][com2].campo4[1])
                            {
                                compareC4 = 1;
                            }
                        }
                    }

                    if (compareC4 <= 0) //Se compareC4 for menor do que zero, o conteúdo da string 1 é menor que o da string 2
                    {
                        vetAux[comAux] = reg[0][com1];
                        com1++;
                    }
                    else //compareC4 maior do que zero --> conteúdo da string1 é maior do que string2
                    {
                        vetAux[comAux] = reg[0][com2];
                        com2++;
                    }
                }
            }
        }
        comAux++;
    }

    while (com1 <= meio)
    { //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = reg[0][com1];
        comAux++;
        com1++;
    }

    while (com2 <= fim)
    { //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = reg[0][com2];
        comAux++;
        com2++;
    }

    for (comAux = comeco; comAux <= fim; comAux++)
    { //Move os elementos de volta para o vetor original
        if (vetAux[comAux - comeco].campo1 != 0)
            reg[0][comAux] = vetAux[comAux - comeco];
    }

    free(vetAux);
}

void mergeSort(REGISTRO **reg, int comeco, int fim)
{

    if (comeco < fim)
    {

        int meio = (fim + comeco) / 2;

        mergeSort(reg, comeco, meio);
        mergeSort(reg, meio + 1, fim);
        merge(reg, comeco, meio, fim);
    }
}

int mergeArq(REGISTRO **reg1, REGISTRO **reg2, char *arq_name1, char *arq_name2, char *arq_fname)
{
    FILE *arq1 = fopen(arq_name1, "r+b");
    FILE *arq2 = fopen(arq_name2, "r+b");
    FILE *arq_fin = fopen(arq_fname, "w+b");

    if (arq1 == NULL || arq2 == NULL || arq_fin == NULL)
    {
        return -1;
    }

    fseek(arq1, 0, SEEK_END);
    fseek(arq2, 0, SEEK_END);
    /* Lê o indicador de posição (em bytes)*/
    int n1 = ftell(arq1);
    int n2 = ftell(arq2);

    if (n1 == 0 || n2 == 0)
    {
        return 0;
    }

    n1 = n1 - sizeof(char);
    n1 = n1 / (sizeof(REGISTRO));
    n2 = n2 - sizeof(char);
    n2 = n2 / (sizeof(REGISTRO));

    *reg1 = (REGISTRO **)malloc(n1 * sizeof(REGISTRO));
    *reg2 = (REGISTRO **)malloc(n2 * sizeof(REGISTRO));

    REGISTRO reg_aux;
    char status = '0';
    rewind(arq1);
    rewind(arq2);
    fwrite(&status, sizeof(char), 1, arq1);
    fwrite(&status, sizeof(char), 1, arq2);
    fwrite(&status, sizeof(char), 1, arq_fin);
    fseek(arq1, sizeof(char), SEEK_SET);
    fseek(arq2, sizeof(char), SEEK_SET);

    int cont1 = 0, cont2 = 0, n, teste;
    fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
    reg1[0][cont1] = reg_aux;
    fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
    reg2[0][cont2] = reg_aux;
    while (1)
    {
        if (reg1[0][cont1].campo1 < reg2[0][cont2].campo1)
        {
            fwrite(&reg1[0][cont1], sizeof(REGISTRO), 1, arq_fin);
            cont1++;
            fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
            reg1[0][cont1] = reg_aux;
        }
        else if (reg2[0][cont2].campo1 < reg1[0][cont1].campo1)
        {
            fwrite(&reg2[0][cont2], sizeof(REGISTRO), 1, arq_fin);
            cont2++;
            fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
            reg2[0][cont2] = reg_aux;
        }
        else
        {
            int a;
            if (strlen(reg1[0][cont1].campo2) < strlen(reg2[0][cont2].campo2))
            {
                n = strlen(reg1[0][cont1].campo2);
                a = 1;
            }
            else if (strlen(reg2[0][cont2].campo2) < strlen(reg1[0][cont1].campo2))
            {
                n = strlen(reg2[0][cont2].campo2);
                a = -1;
            }
            else
            {
                n = strlen(reg1[0][cont1].campo2);
                a = 0;
            }
            int compare2 = 0;
            for (int j = 0; j < n; j++)
            {
                if (reg1[0][cont1].campo2[j] < reg2[0][cont2].campo2[j])
                {
                    compare2 = 1;
                    break;
                }
                else if (reg2[0][cont2].campo2[j] < reg1[0][cont1].campo2[j])
                {
                    compare2 = -1;
                    break;
                }
                else if (j == n - 1 && a == 1)
                {
                    //printf("%d %s -> %d %s \n",reg1[0][cont1].campo1,reg1[0][cont1].campo2,reg2[0][cont2].campo1,reg2[0][cont2].campo2);
                    fwrite(&reg1[0][cont1], sizeof(REGISTRO), 1, arq_fin);
                    cont1++;
                    fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
                    reg1[0][cont1] = reg_aux;
                    compare2 = 10;
                }
                else if (j == n - 1 && a == -1)
                {
                    //printf("%d %s -> %d %s \n",reg2[0][cont2].campo1,reg2[0][cont2].campo2,reg1[0][cont1].campo1,reg1[0][cont1].campo2);
                    fwrite(&reg2[0][cont2], sizeof(REGISTRO), 1, arq_fin);
                    cont2++;
                    fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
                    reg2[0][cont2] = reg_aux;
                    compare2 = 10;
                }
            }
            if (compare2 == 1)
            {
                //printf("%d %s -> %d %s \n",reg1[0][cont1].campo1,reg1[0][cont1].campo2,reg2[0][cont2].campo1,reg2[0][cont2].campo2);
                fwrite(&reg1[0][cont1], sizeof(REGISTRO), 1, arq_fin);
                cont1++;
                fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
                reg1[0][cont1] = reg_aux;
            }
            else if (compare2 == -1)
            {
                //printf("%d %s -> %d %s \n",reg2[0][cont2].campo1,reg2[0][cont2].campo2,reg1[0][cont1].campo1,reg1[0][cont1].campo2);
                fwrite(&reg2[0][cont2], sizeof(REGISTRO), 1, arq_fin);
                cont2++;
                fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
                reg2[0][cont2] = reg_aux;
            }
            else if (compare2 == 0 && a == 0)
            {
                if (strlen(reg1[0][cont1].campo3) < strlen(reg2[0][cont2].campo3))
                {
                    n = strlen(reg1[0][cont1].campo3);
                    a = 1;
                }
                else if (strlen(reg2[0][cont2].campo3) < strlen(reg1[0][cont1].campo3))
                {
                    n = strlen(reg2[0][cont2].campo3);
                    a = -1;
                }
                else
                {
                    n = strlen(reg1[0][cont1].campo3);
                    a = 0;
                }
                int compare3;
                for (int j = 0; j < n; j++)
                {
                    if (reg1[0][cont1].campo3[j] < reg2[0][cont2].campo3[j])
                    {
                        compare3 = 1;
                        break;
                    }
                    else if (reg2[0][cont2].campo3[j] < reg1[0][cont1].campo3[j])
                    {
                        compare3 = -1;
                        break;
                    }
                    else if (j == n - 1 && a == 1)
                    {
                        //printf("%d %s -> %d %s \n",reg1[0][cont1].campo1,reg1[0][cont1].campo2,reg2[0][cont2].campo1,reg2[0][cont2].campo2);
                        fwrite(&reg1[0][cont1], sizeof(REGISTRO), 1, arq_fin);
                        cont1++;
                        fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
                        reg1[0][cont1] = reg_aux;
                        compare3 = 10;
                    }
                    else if (j == n - 1 && a == -1)
                    {
                        //printf("%d %s -> %d %s \n",reg2[0][cont2].campo1,reg2[0][cont2].campo2,reg1[0][cont1].campo1,reg1[0][cont1].campo2);
                        fwrite(&reg2[0][cont2], sizeof(REGISTRO), 1, arq_fin);
                        cont2++;
                        fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
                        reg2[0][cont2] = reg_aux;
                        compare3 = 10;
                    }
                }
                if (compare3 == 1)
                {
                    //printf("%d %s -> %d %s \n",reg1[0][cont1].campo1,reg1[0][cont1].campo2,reg2[0][cont2].campo1,reg2[0][cont2].campo2);
                    fwrite(&reg1[0][cont1], sizeof(REGISTRO), 1, arq_fin);
                    cont1++;
                    fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
                    reg1[0][cont1] = reg_aux;
                }
                else if (compare3 == -1)
                {
                    //printf("%d %s -> %d %s \n",reg2[0][cont2].campo1,reg2[0][cont2].campo2,reg1[0][cont1].campo1,reg1[0][cont1].campo2);
                    fwrite(&reg2[0][cont2], sizeof(REGISTRO), 1, arq_fin);
                    cont2++;
                    fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
                    reg2[0][cont2] = reg_aux;
                }
                else if (compare3 == 0)
                {
                    int compare4;
                    for (int j = 6; j < 10; j++)
                    {
                        if (reg1[0][cont1].campo4[j] < reg2[0][cont2].campo4[j])
                        {
                            compare4 = 1;
                            break;
                        }
                        else if (reg2[0][cont2].campo4[j] < reg1[0][cont1].campo4[j])
                        {
                            compare4 = -1;
                            break;
                        }
                        else if (reg2[0][cont2].campo4[j] == reg1[0][cont1].campo4[j] && j == 9)
                        {
                            compare4 = 0;
                        }
                    }
                    if (compare4 == 0)
                    {
                        if (reg1[0][cont1].campo4[4] < reg2[0][cont2].campo4[4] || reg1[0][cont1].campo4[3] < reg2[0][cont2].campo4[3])
                        {
                            compare4 = 1;
                        }
                        else if (reg2[0][cont2].campo4[4] < reg1[0][cont1].campo4[4] || reg2[0][cont2].campo4[3] < reg1[0][cont1].campo4[3])
                        {
                            compare4 = -1;
                        }
                        else
                        {
                            if (reg1[0][cont1].campo4[0] < reg2[0][cont2].campo4[0] || reg1[0][cont1].campo4[1] < reg2[0][cont2].campo4[1])
                            {
                                compare4 = 1;
                            }
                            else if (reg2[0][cont2].campo4[0] < reg1[0][cont1].campo4[0] || reg2[0][cont2].campo4[1] < reg1[0][cont1].campo4[1])
                            {
                                compare4 = -1;
                            }
                        }
                    }
                    if (compare4 == 1)
                    {
                        //printf("%d %s -> %d %s \n",reg1[0][cont1].campo1,reg1[0][cont1].campo2,reg2[0][cont2].campo1,reg2[0][cont2].campo2);
                        fwrite(&reg1[0][cont1], sizeof(REGISTRO), 1, arq_fin);
                        cont1++;
                        fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
                        reg1[0][cont1] = reg_aux;
                    }
                    else if (compare4 == -1)
                    {
                        //printf("%d %s -> %d %s \n",reg2[0][cont2].campo1,reg2[0][cont2].campo2,reg1[0][cont1].campo1,reg1[0][cont1].campo2);
                        fwrite(&reg2[0][cont2], sizeof(REGISTRO), 1, arq_fin);
                        cont2++;
                        fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
                        reg2[0][cont2] = reg_aux;
                    }
                    else if (compare4 == 0)
                    {
                        fwrite(&reg1[0][cont1], sizeof(REGISTRO), 1, arq_fin);
                        cont1++;
                        fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
                        reg1[0][cont1] = reg_aux;
                        cont2++;
                        fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
                        reg2[0][cont2] = reg_aux;
                    }
                }
            }
        }
        if (cont1 >= n1 || cont2 >= n2)
        {
            break;
        }
    }
    int i;
    if (cont1 < n1)
    {
        for (i = cont1 + 1; i < n1; i++)
        {
            fread(&reg_aux, sizeof(REGISTRO), 1, arq1);
            reg1[0][i] = reg_aux;
            fwrite(&reg1[0][i], sizeof(REGISTRO), 1, arq_fin);
        }
    }
    else if (cont2 < n2)
    {
        for (int i = cont2 + 1; i < n2; i++)
        {
            fread(&reg_aux, sizeof(REGISTRO), 1, arq2);
            reg2[0][i] = reg_aux;
            fwrite(&reg2[0][i], sizeof(REGISTRO), 1, arq_fin);
        }
    }
    status = '1';
    rewind(arq1);
    rewind(arq2);
    fwrite(&status, sizeof(char), 1, arq1);
    fwrite(&status, sizeof(char), 1, arq2);
    fwrite(&status, sizeof(char), 1, arq_fin);
    fclose(arq1);
    fclose(arq2);
    fclose(arq_fin);
    return 1;
}
