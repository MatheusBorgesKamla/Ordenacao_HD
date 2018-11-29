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
    for(int i=0; i<n; i++){
        fwrite(&reg[i].campo1, sizeof(int), 1, arq);
        fwrite(&reg[i].campo2, 30*sizeof(char), 1, arq);
        fwrite(&reg[i].campo3, 20*sizeof(char), 1, arq);
        fwrite(&reg[i].campo4, 10*sizeof(char), 1, arq);
    }
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
    *n = *n / 64; // 64 - número de bytes de um registro
    //REGISTRO *re = (REGISTRO*) malloc((*n)*sizeof(REGISTRO));
    *reg = (REGISTRO*)malloc(((*n+1) * sizeof(REGISTRO)));
    REGISTRO *a = (REGISTRO*)malloc((*n) * sizeof(REGISTRO));
    char status = '0';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fseek(arq, sizeof(char), SEEK_SET);
    for(int i=0;i<*n;i++){
        fread(&a[i].campo1,sizeof(int),1,arq);
        fread(&a[i].campo2,30*sizeof(char),1,arq);
        fread(&a[i].campo3,20*sizeof(char),1,arq);
        fread(&a[i].campo4,10*sizeof(char),1,arq);
        a[i].campo4[10] = '\0';
        reg[0][i] = a[i];
    }
    free(a);
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
        if((n-i) == 1)
        {
            indice = rand() % 50000;
            while (aux[indice] == (-1))
            {
                indice = rand() % 50000;
            }
            vetor[n-1] = aux[indice];
            vetor[n-2] = aux[indice];
            vetor[n-3] = aux[indice];
            break;
        }
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
    free(aux);
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
        if((n-i) == 1)
        {
            indice = rand() % 9901;
            while (!strcmp(strings[indice], "*"))
            {
                indice = rand() % 9901;
            }
            strcpy(vetor[n-1], strings[indice]);
            strcpy(vetor[n-2], strings[indice]);
            strcpy(vetor[n-3], strings[indice]);
            break;
        } 
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
        if((n-i) == 1)
        {
            indice = rand() % 9901;
            while (!strcmp(strings[indice], "*"))
            {
                indice = rand() % 9901;
            }
            strcpy(vetor[n-1], strings[indice]);
            strcpy(vetor[n-2], strings[indice]);
            strcpy(vetor[n-3], strings[indice]);
            break;
        } 
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
        if((n-i) == 1)
        {
            indice = rand() % 10440;
            while (!strcmp(strings[indice], "*"))
            {
                indice = rand() % 10440;
            }
            strcpy(vetor[n-1], strings[indice]);
            strcpy(vetor[n-2], strings[indice]);
            strcpy(vetor[n-3], strings[indice]);
            break;
        } 
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
    REGISTRO *vetAux = (REGISTRO *)malloc((tam+1) * sizeof(REGISTRO));
    int teste;
    while (com1 <= meio && com2 <= fim)
    {

        teste = compara_reg(reg[0][com1],reg[0][com2]);
        if(teste == 1){
            vetAux[comAux] = reg[0][com1];
            com1++;
        }else{
            vetAux[comAux] = reg[0][com2];
            com2++;
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

int mergeArq(char *arq_name1, char *arq_name2, char *arq_fname)
{
    //Abrindo os arquivos
    FILE *arq1 = fopen(arq_name1, "r+b");
    FILE *arq2 = fopen(arq_name2, "r+b");
    FILE *arq_fin = fopen(arq_fname, "w+b");

    if (arq1 == NULL || arq2 == NULL || arq_fin == NULL)
    {
        return -1;
    }
    //Pulando para o fim de cada arquivo
    fseek(arq1, 0, SEEK_END);
    fseek(arq2, 0, SEEK_END);
    /* Lê o indicador de posição (em bytes)*/
    int n1 = ftell(arq1);
    int n2 = ftell(arq2);

    if (n1 == 0 || n2 == 0)
    {
        return 0;
    }
    //Calculando a quantidade de elementos de cada arquivo
    n1 = n1 - sizeof(char);
    n1 = n1 / 64;
    n2 = n2 - sizeof(char);
    n2 = n2 / 64;
    REGISTRO *reg1 = (REGISTRO *)malloc((n1+1) * sizeof(REGISTRO));
    REGISTRO *reg2 = (REGISTRO *)malloc((n2+1) * sizeof(REGISTRO));
    REGISTRO reg_aux;
    //Escrevendo o status nos arquivos abertos
    char status = '0';
    rewind(arq1);
    rewind(arq2);
    fwrite(&status, sizeof(char), 1, arq1);
    fwrite(&status, sizeof(char), 1, arq2);
    fwrite(&status, sizeof(char), 1, arq_fin);
    fseek(arq1, sizeof(char), SEEK_SET);
    fseek(arq2, sizeof(char), SEEK_SET);

    //Començando a ler os arquivos e declarando variaveis auxiliáres
    int cont1 = 0, cont2 = 0, teste;
    fread(&reg_aux.campo1,sizeof(int),1,arq1);
    fread(&reg_aux.campo2,30*sizeof(char),1,arq1);
    fread(&reg_aux.campo3,20*sizeof(char),1,arq1);
    fread(&reg_aux.campo4,10*sizeof(char),1,arq1);
    reg1[cont1] = reg_aux;
    fread(&reg_aux.campo1,sizeof(int),1,arq2);
    fread(&reg_aux.campo2,30*sizeof(char),1,arq2);
    fread(&reg_aux.campo3,20*sizeof(char),1,arq2);
    fread(&reg_aux.campo4,10*sizeof(char),1,arq2);
    reg2[cont2] = reg_aux;
    while (1)
    {
        teste = compara_reg(reg1[cont1],reg2[cont2]);
        if(teste == 1)
        {
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10*sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1,sizeof(int),1,arq1);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq1);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq1);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq1);
            reg1[cont1] = reg_aux;
        }
        else if(teste == -1)
        {
            fwrite(&reg2[cont2].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg2[cont2].campo2, 30*sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo3, 20*sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo4, 10*sizeof(char), 1, arq_fin);
            cont2++;
            fread(&reg_aux.campo1,sizeof(int),1,arq2);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq2);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq2);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq2);
            reg2[cont2] = reg_aux;
        }else{
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10*sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1,sizeof(int),1,arq1);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq1);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq1);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq1);
            reg1[cont1] = reg_aux;
            cont2++;
            fread(&reg_aux.campo1,sizeof(int),1,arq2);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq2);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq2);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq2);
            reg2[cont2] = reg_aux;
        }
        //Continuo o loop até ter lido o número total de registros de um dos arquivos
        //indicando o seu final
        if (cont1 >= n1 || cont2 >= n2)
        {
            break;
        }
    }
    //Agora testo qual dos arquivos já cheguei no final, o que não cheguei continuo lendo e
    //escrevendo no arq final até chegar em seu fim
    while (cont1 < n1)
    {
        fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
        fwrite(&reg1[cont1].campo2, 30*sizeof(char), 1, arq_fin);
        fwrite(&reg1[cont1].campo3, 20*sizeof(char), 1, arq_fin);
        fwrite(&reg1[cont1].campo4, 10*sizeof(char), 1, arq_fin);
        cont1++;
        if (cont1 != n1)
        {
            fread(&reg_aux.campo1,sizeof(int),1,arq1);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq1);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq1);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq1);
            reg1[cont1] = reg_aux;
        }
    }
    while (cont2 < n2)
    {
        fwrite(&reg2[cont2].campo1, sizeof(int), 1, arq_fin);
        fwrite(&reg2[cont2].campo2, 30*sizeof(char), 1, arq_fin);
        fwrite(&reg2[cont2].campo3, 20*sizeof(char), 1, arq_fin);
        fwrite(&reg2[cont2].campo4, 10*sizeof(char), 1, arq_fin);
        cont2++;
        if (cont2 != n1)
        {
            fread(&reg_aux.campo1,sizeof(int),1,arq2);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq2);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq2);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq2);
            reg2[cont2] = reg_aux;
        }
    }
    //Retorno o status de cada arquivo para 1 para agora poder fecha-los
    status = '1';
    rewind(arq1);
    rewind(arq2);
    rewind(arq_fin);
    fwrite(&status, sizeof(char), 1, arq1);
    fwrite(&status, sizeof(char), 1, arq2);
    fwrite(&status, sizeof(char), 1, arq_fin);
    fclose(arq1);
    fclose(arq2);
    fclose(arq_fin);
    free(reg1);
    free(reg2);
    return 1;
}

int matching(char *arq_name1, char *arq_name2, char *arq_fname)
{
    //Abrindo os arquivos
    FILE *arq1 = fopen(arq_name1, "r+b");
    FILE *arq2 = fopen(arq_name2, "r+b");
    FILE *arq_fin = fopen(arq_fname, "w+b");

    if (arq1 == NULL || arq2 == NULL || arq_fin == NULL)
    {
        return -1;
    }
    //Pulando para o fim de cada arquivo
    fseek(arq1, 0, SEEK_END);
    fseek(arq2, 0, SEEK_END);
    /* Lê o indicador de posição (em bytes)*/
    int n1 = ftell(arq1);
    int n2 = ftell(arq2);

    if (n1 == 0 || n2 == 0)
    {
        return 0;
    }
    //Calculando a quantidade de elementos de cada arquivo
    n1 = n1 - sizeof(char);
    n1 = n1 / 64;
    n2 = n2 - sizeof(char);
    n2 = n2 / 64;
    REGISTRO *reg1 = (REGISTRO *)malloc((n1+1) * sizeof(REGISTRO));
    REGISTRO *reg2 = (REGISTRO *)malloc((n2+1) * sizeof(REGISTRO));
    REGISTRO reg_aux;
    //Escrevendo o status nos arquivos abertos
    char status = '0';
    rewind(arq1);
    rewind(arq2);
    fwrite(&status, sizeof(char), 1, arq1);
    fwrite(&status, sizeof(char), 1, arq2);
    fwrite(&status, sizeof(char), 1, arq_fin);
    fseek(arq1, sizeof(char), SEEK_SET);
    fseek(arq2, sizeof(char), SEEK_SET);

    //Començando a ler os arquivos e declarando variaveis auxiliáres
    int cont1 = 0, cont2 = 0, teste;
    fread(&reg_aux.campo1,sizeof(int),1,arq1);
    fread(&reg_aux.campo2,30*sizeof(char),1,arq1);
    fread(&reg_aux.campo3,20*sizeof(char),1,arq1);
    fread(&reg_aux.campo4,10*sizeof(char),1,arq1);
    reg1[cont1] = reg_aux;
    fread(&reg_aux.campo1,sizeof(int),1,arq2);
    fread(&reg_aux.campo2,30*sizeof(char),1,arq2);
    fread(&reg_aux.campo3,20*sizeof(char),1,arq2);
    fread(&reg_aux.campo4,10*sizeof(char),1,arq2);
    reg2[cont2] = reg_aux;
    while (1)
    {
        teste = compara_reg(reg1[cont1],reg2[cont2]);
        if(teste == 1)
        {
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10*sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1,sizeof(int),1,arq1);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq1);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq1);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq1);
            reg1[cont1] = reg_aux;
        }
        else if(teste == -1)
        {
            fwrite(&reg2[cont2].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg2[cont2].campo2, 30*sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo3, 20*sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo4, 10*sizeof(char), 1, arq_fin);
            cont2++;
            fread(&reg_aux.campo1,sizeof(int),1,arq2);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq2);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq2);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq2);
            reg2[cont2] = reg_aux;
        }else{
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20*sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10*sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1,sizeof(int),1,arq1);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq1);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq1);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq1);
            reg1[cont1] = reg_aux;
            cont2++;
            fread(&reg_aux.campo1,sizeof(int),1,arq2);
            fread(&reg_aux.campo2,30*sizeof(char),1,arq2);
            fread(&reg_aux.campo3,20*sizeof(char),1,arq2);
            fread(&reg_aux.campo4,10*sizeof(char),1,arq2);
            reg2[cont2] = reg_aux;
        }
        //Continuo o loop até ter lido o número total de registros de um dos arquivos
        //indicando o seu final, ou seja, quando uma das listas acabarem o processo se
        //encerra
        if (cont1 >= n1 || cont2 >= n2)
        {
            break;
        }
    }
    //Retorno o status de cada arquivo para 1 para agora poder fecha-los
    status = '1';
    rewind(arq1);
    rewind(arq2);
    rewind(arq_fin);
    fwrite(&status, sizeof(char), 1, arq1);
    fwrite(&status, sizeof(char), 1, arq2);
    fwrite(&status, sizeof(char), 1, arq_fin);
    fclose(arq1);
    fclose(arq2);
    fclose(arq_fin);
    return 1;
}

int compara_reg(REGISTRO reg1, REGISTRO reg2) //Função que retorna 1 se reg1 < reg2 e -1 c.c.
{
    if (reg1.campo1 < reg2.campo1)
    {
        return 1;
    }
    else if (reg2.campo1 < reg1.campo1)
    {
        return -1;
    }
    else
    {
        int a, n;
        if (strlen(reg1.campo2) < strlen(reg2.campo2))
        {
            n = strlen(reg1.campo2);
            a = 1;
        }
        else if (strlen(reg2.campo2) < strlen(reg1.campo2))
        {
            n = strlen(reg2.campo2);
            a = -1;
        }
        else
        {
            n = strlen(reg1.campo2);
            a = 0;
        }
        for (int j = 0; j < n; j++)
        {
            if (reg1.campo2[j] < reg2.campo2[j])
            {
                return 1;
            }
            else if (reg2.campo2[j] < reg1.campo2[j])
            {
                return -1;
            }
            else if (j == n - 1 && a == 1)
            {
                return 1;
            }
            else if (j == n - 1 && a == -1)
            {
                return -1;
            }
        }
        if (a == 0)
        {
            if (strlen(reg1.campo3) < strlen(reg2.campo3))
            {
                n = strlen(reg1.campo3);
                a = 1;
            }
            else if (strlen(reg2.campo3) < strlen(reg1.campo3))
            {
                n = strlen(reg2.campo3);
                a = -1;
            }
            else
            {
                n = strlen(reg1.campo3);
                a = 0;
            }
            for (int j = 0; j < n; j++)
            {
                if (reg1.campo3[j] < reg2.campo3[j])
                {
                    return 1;
                }
                else if (reg2.campo3[j] < reg1.campo3[j])
                {
                    return -1;
                }
                else if (j == n - 1 && a == 1)
                {
                    return 1;
                }
                else if (j == n - 1 && a == -1)
                {
                    return 1;
                }
            }
            if (a == 0)
            {
                int compare4;
                for (int j = 6; j < 10; j++)
                {
                    if (reg1.campo4[j] < reg2.campo4[j])
                    {
                        return 1;
                    }
                    else if (reg2.campo4[j] < reg1.campo4[j])
                    {
                        return -1;
                    }
                    else if (reg2.campo4[j] == reg1.campo4[j] && j == 9)
                    {
                        compare4 = 0;
                    }
                }
                if (compare4 == 0)
                {
                    for (int i = 3; i <= 4; i++)
                    {
                        if (reg1.campo4[i] < reg2.campo4[i])
                        {
                            return 1;
                        }
                        else if (reg1.campo4[i] > reg2.campo4[i])
                        {
                            return -1;
                        }
                    }
                    if (compare4 == 0)
                    {
                        //Se possuirem mês igual eu comparo os dias até achar o menor deles
                        for (int i = 0; i <= 1; i++)
                        {
                            if (reg1.campo4[i] < reg2.campo4[i])
                            {
                                return 1;
                            }
                            else if (reg1.campo4[i] > reg2.campo4[i])
                            {
                                return -1;
                            }
                        }
                        return 0;
                    }
                }
            }
        }
    }
}

int sortMerge(char *arq_name, char *arq_fname)
{
    FILE *arq = fopen(arq_name, "r+b");
    if (arq == NULL)
    {
        return -1;
    }
    /* Pula até o fim do arquivo */
    fseek(arq, 0, SEEK_END);
    /* Lê o indicador de posição (em bytes)*/
    int n = ftell(arq);
    if (n == 0)
    {
        //Arquivo vazio
        fclose(arq);
        return 0;
    }
    //Calculo o número total de registros no arquivo (n)
    n = n - sizeof(char);
    n = n / 64;
    //Aloco memória para os 1000 registros (4 páginas de disco) que poderei trabalhar no buffer (RAM) 
    REGISTRO *reg = (REGISTRO *)malloc((250) * sizeof(REGISTRO));
    //Defino status 0 para o arquivo após abri-lo indicando que irei manipula-lo
    char status = '0';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fseek(arq, sizeof(char), SEEK_SET);
    int n_arq, sobra = 0;
    //Calculo do número de subarquivos necessários já considerando o caso de haver sobras (subarquivos que não ocupam necessariamente 16000 bytes == 250 registros)
    if (n % 250 == 0)
    {
        n_arq = n / 250;
    }
    else
    {
        n_arq = n / 250;
        sobra = n - (n_arq * 250);
        n_arq++;
    }
    char num[10][4] = {"0","1","2","3","4","5","6","7","8","9"};
    char sub_arq_name[20];
    int n_aux;
    FILE *sub_arq;
    int i;
    for(i=0; i<n_arq; i++){
        for(int j=0;j<250;j++)
        {
            fread(&reg[j].campo1,sizeof(int),1,arq);
            fread(&reg[j].campo2,30*sizeof(char),1,arq);
            fread(&reg[j].campo3,20*sizeof(char),1,arq);
            fread(&reg[j].campo4,10*sizeof(char),1,arq);
            //printf("%d %s %s %s \n",reg[i].campo1,reg[i].campo2,reg[i].campo3,reg[i].campo4);
        }
        mergeSort(&reg,0,249);
        strcpy(sub_arq_name,"sub_arquivo");
        if(i < 10)
        {
            strcat(sub_arq_name,num[i]);
        }
        else if (i>=10 && i<20)
        {
            strcat(sub_arq_name,num[1]);
            n_aux = i-10;
            strcat(sub_arq_name,num[n_aux]);
        }else if(i>=20 && i<30){
            strcat(sub_arq_name,num[2]);
            n_aux = i-20;
            strcat(sub_arq_name,num[n_aux]);
        }
        sub_arq = fopen(sub_arq_name, "w+b");
        status = '0';
        fwrite(&status, sizeof(char), 1, sub_arq);
        for(int j=0; j<250; j++){
            fwrite(&reg[j].campo1, sizeof(int), 1, sub_arq);
            fwrite(&reg[j].campo2, 30*sizeof(char), 1, sub_arq);
            fwrite(&reg[j].campo3, 20*sizeof(char), 1, sub_arq);
            fwrite(&reg[j].campo4, 10*sizeof(char), 1, sub_arq);
        }
        status = '1';
        rewind(sub_arq);
        fwrite(&status, sizeof(char), 1, sub_arq);
        fclose(sub_arq);
    }
    int x = recursive_sortMerge(i,0,0,arq_fname);
    return 1;
}

int recursive_sortMerge(int n_arq, int cont, int sobra, char *arq_fname)
{
    char num[10][4] = {"0","1","2","3","4","5","6","7","8","9"};
    char sub_arq_name1[20];
    char sub_arq_name2[20];
    char sub_arq_name3[20];
    int n_aux, i, cont_aux, n;
    if (n_arq == 1)
    {
        char final[20];
        strcpy(final, "sub_arquivo");
        if (cont < 10)
        {
            strcat(final,num[cont]);
        }
        else if (cont >= 10 && cont < 20)
        {
            strcat(final, num[1]);
            n_aux = cont - 10;
            strcat(final, num[n_aux]);
        }
        else if (cont >= 20 && cont < 30)
        {
            strcat(final, num[2]);
            n_aux = cont - 20;
            strcat(final, num[n_aux]);
        }
        else if (cont >= 30 && cont < 40)
        {
            strcat(final, num[3]);
            n_aux = cont - 30;
            strcat(final, num[n_aux]);;
        }
        else if (cont >= 40 && cont < 50)
        {
            strcat(final, num[4]);
            n_aux = cont - 40;
            strcat(final, num[n_aux]);
        }
        printf("\n\n %s",final);
        rename(final, arq_fname);
        return 1;
    }
    else if(n_arq%2 == 0)
    {
        n = cont + n_arq;
        cont_aux = n;
        printf("\nValor do cont_aux = %d \n",cont_aux);
        for( i=cont;i<n;i+=2){
            strcpy(sub_arq_name1,"sub_arquivo");
            strcpy(sub_arq_name2,"sub_arquivo");
            strcpy(sub_arq_name3,"sub_arquivo");
            if(i < 10)
            {
                strcat(sub_arq_name1,num[i]);
                strcat(sub_arq_name2,num[i+1]);
            }
            else if (i>=10 && i<20)
            {
                strcat(sub_arq_name1,num[1]);
                strcat(sub_arq_name2,num[1]);
                n_aux = i-10;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }else if(i>=20 && i<30){
                strcat(sub_arq_name1,num[2]);
                strcat(sub_arq_name2,num[2]);
                n_aux = i-20;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }else if(i>=30 && i<40){
                strcat(sub_arq_name1,num[3]);
                strcat(sub_arq_name2,num[3]);
                n_aux = i-30;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }else if(i>=40 && i<50){
                strcat(sub_arq_name1,num[4]);
                strcat(sub_arq_name2,num[4]);
                n_aux = i-40;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }
            if(cont_aux < 10)
            {
                strcat(sub_arq_name3,num[cont_aux]);
            }
            else if (cont_aux>=10 && cont_aux<20)
            {
                strcat(sub_arq_name3,num[1]);
                n_aux = cont_aux-10;
                strcat(sub_arq_name3,num[n_aux]);
            }
            else if (cont_aux>=20 && cont_aux<30)
            {
                strcat(sub_arq_name3,num[2]);
                n_aux = cont_aux-20;
                strcat(sub_arq_name3,num[n_aux]);
            }
            else if (cont_aux>=30 && cont_aux<40)
            {
                strcat(sub_arq_name3,num[3]);
                n_aux = cont_aux-30;
                strcat(sub_arq_name3,num[n_aux]);
            }
            else if (cont_aux>=40 && cont_aux<50)
            {
                strcat(sub_arq_name3,num[4]);
                n_aux = cont_aux-40;
                strcat(sub_arq_name3,num[n_aux]);
            }
        
            printf("%s %s %s \n",sub_arq_name1,sub_arq_name2,sub_arq_name3);
            mergeArq(sub_arq_name1,sub_arq_name2,sub_arq_name3);
            cont_aux++;
        }
        cont = i;
        printf("cont = %d\n",cont);
        recursive_sortMerge(n_arq/2,cont,0,arq_fname);
    }
    else
    {
        n = cont + n_arq;
        sobra = n-1;
        printf("\nValor da sobra = %d\n",sobra);
        n--;
        cont_aux = sobra+1;
        printf("Valor do cont_aux = %d \n",cont_aux);
        for( i=cont;i<n;i+=2){
            strcpy(sub_arq_name1,"sub_arquivo");
            strcpy(sub_arq_name2,"sub_arquivo");
            strcpy(sub_arq_name3,"sub_arquivo");
            if(i < 10)
            {
                strcat(sub_arq_name1,num[i]);
                strcat(sub_arq_name2,num[i+1]);
            }
            else if (i>=10 && i<20)
            {
                strcat(sub_arq_name1,num[1]);
                strcat(sub_arq_name2,num[1]);
                n_aux = i-10;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }else if(i>=20 && i<30){
                strcat(sub_arq_name1,num[2]);
                strcat(sub_arq_name2,num[2]);
                n_aux = i-20;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }else if(i>=30 && i<40){
                strcat(sub_arq_name1,num[3]);
                strcat(sub_arq_name2,num[3]);
                n_aux = i-30;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }else if(i>=40 && i<50){
                strcat(sub_arq_name1,num[4]);
                strcat(sub_arq_name2,num[4]);
                n_aux = i-40;
                strcat(sub_arq_name1,num[n_aux]);
                strcat(sub_arq_name2,num[n_aux+1]);
            }
            if(cont_aux < 10)
            {
                strcat(sub_arq_name3,num[cont_aux]);
            }
            else if (cont_aux>=10 && cont_aux<20)
            {
                strcat(sub_arq_name3,num[1]);
                n_aux = cont_aux-10;
                strcat(sub_arq_name3,num[n_aux]);
            }
            else if (cont_aux>=20 && cont_aux<30)
            {
                strcat(sub_arq_name3,num[2]);
                n_aux = cont_aux-20;
                strcat(sub_arq_name3,num[n_aux]);
            }
            else if (cont_aux>=30 && cont_aux<40)
            {
                strcat(sub_arq_name3,num[3]);
                n_aux = cont_aux-30;
                strcat(sub_arq_name3,num[n_aux]);
            }
            else if (cont_aux>=40 && cont_aux<50)
            {
                strcat(sub_arq_name3,num[4]);
                n_aux = cont_aux-40;
                strcat(sub_arq_name3,num[n_aux]);
            }
        
            printf("%s %s %s \n",sub_arq_name1,sub_arq_name2,sub_arq_name3);
            mergeArq(sub_arq_name1,sub_arq_name2,sub_arq_name3);
            cont_aux++;
        }
        cont = i;
        printf("\ncont = %d",cont);
        n_arq = n_arq/2;
        n_arq++;
        recursive_sortMerge(n_arq,sobra,0,arq_fname);
    }
}