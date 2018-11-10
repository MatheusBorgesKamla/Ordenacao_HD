#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
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
        campo4[i] = (char *)malloc(10 * sizeof(char));

    }
    Gera_Campo1(n, campo1);
    Gera_Campo2(n,campo2);
    Gera_Campo3(n,campo3);
    Gera_Campo4(n,campo4);
    for(int i=0;i<n;i++){
        reg[i].campo1 = campo1[i];
        strcpy(reg[i].campo2,campo2[i]);
        strcpy(reg[i].campo3,campo3[i]);
        strcpy(reg[i].campo4,campo4[i]);
        printf("REGISTRO[%d] : %d | %s | %s | %s --",(i+1),reg[i].campo1,reg[i].campo2,reg[i].campo3,reg[i].campo4);
    }
    /*free(campo1);
    free(campo2);
    free(campo3);
    free(campo4);*/
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
    /*indice = rand()%50000;
    while(aux[indice]==(-1)){
        indice = rand()%50000;
    }
    for(i=n*0.7;i<n;i++){
        vetor[i] = aux[indice];
    }*/
    i = 0.7*n;
    while(i<n){
        indice = rand()%50000;
        while(aux[indice]==(-1)){
            indice = rand()%50000;
        }
        vetor[i] = aux[indice];
        vetor[i+1] = aux[indice];
        aux[indice] = -1;
        i+=2;
    }

}

void Gera_Campo2(int n, char *vetor[])
{
    int i, j, k, indice;
    char aux[100][10] = {"GOD", "WAR", "SNIPER", "FIGHT", "BAD", "WEAPON", "FIRE", "ARMY", "ADVANCED", "GHOST", "CHICKEN", "GROW", "HIGH", "MAGIC", "WORLD", "ROCK", "BATTLE", "SNOW", "GAME", "YELLOW", "CALL", "BLACK", "OPS", "HACKER", "SOLDIER", "ZOMBIE", "DRAGONS", "SHIELD", "COLOSSUS", "SHADOW", "DIRTY", "TITANS", "BREAKING", "CRAZY", "NIGHT", "MUTANTS",
    "HERO", "SPEED", "RACE", "SUN", "AGE", "EMPIRE", "WAKE", "AMNESIA", "AQUA", "LEGEND", "COUNTER", "KINGS", "DARK", "WATCH", "DOGS", "ORIGINS", "DEFEAT", "DAY", "DIRT", "EURO", "FAR", "CRY", "HONOR", "SIMULATOR", "DESTINY", "GRAND",  "HITMAN", "BIOSHOCK", "INSURGENCY", "CAUSE", "LAYERS", "DEAD", "LIFE", "STRANGE", "MAFIA", "MEDAL", "EARTH", "GOAT", "ORCS", "PORTAL", "ROCKET", "SLEEPING", "STAR", "SUPREME", "SURGEON", "TEAM", "FOREST", "WITCHER", "TROPICO", "TIBIA", "RAINBOW", "TALES", "ZELDA", "AUTO", "SIEGE", "ELDER", "SCROLL", "FARM", "HOTEL", "QUAKE", "HALF", "FEAR", "SOULS", "GREAT"};
    char strings[9901][30];
    for(i=0;i<100;i++){
        strcpy(strings[i],aux[i]);
    }
    int cont = 100;
    for(j=0;j<100;j++){
        for(i=(j+1);i<100;i++){
            strcpy(strings[cont],strings[j]);
            strcat(strings[cont]," ");
            strcat(strings[cont],strings[i]);
            cont++;
        }
    }
    for(j=0;j<100;j++){
        for(i=(j+1);i<100;i++){
            for(k=(i+1);k<100;k++){
                strcpy(strings[cont],strings[j]);
                strcat(strings[cont]," ");
                strcat(strings[cont],strings[i]);
                strcat(strings[cont]," ");
                strcat(strings[cont],strings[k]);
                cont++;
            }
            break;
        }
    }
    /*printf("Contador: %d",cont);
    for(i=0;i<9901;i++){
        printf("%s -",strings[i]);
    }*/
    for (i = 0; i < n*0.75; i++){
        indice = rand()%9901;
        while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
        }
        strcpy(vetor[i],strings[indice]);
        strcpy(strings[indice],"*");
    }
    /*indice = rand()%9901;
    while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
    }
    for(i=n*0.75;i<n;i++){
        strcpy(vetor[i],strings[indice]);
    }*/
    i = 0.75*n;
    while(i<n){
        indice = rand()%9901;
        while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
        }
        strcpy(vetor[i],strings[indice]);
        strcpy(vetor[i+1],strings[indice]);
        strcpy(strings[indice],"*");
        i+=2;
    }
}

void Gera_Campo3(int n, char *vetor[]){
    int i, j, k, indice;
    char aux[100][20] = {"UBI", "NINTENDO", "MICRO", "EA", "LG", "ROCKSTAR", "NEW", "ATLAS", "SIRIUS", "GIGA", "RIO", "BIT", "ROCKLAND", "WIZARD", "SWIFT", "AMAZON", "MANAGER", "YORK", "APPLE", "SILICON", "JDK", "ORACLE", "SYSTEM", "WARNER", "MARVEL", "SONY", "ACER", "LENOVO", "HP", "ATARI", "SPACE", "FOX", "DIGITAL", "PLAY", "SIMS", "SAMSUNG",
    "RISE", "EUREKA", "RACE", "ALPHA", "LAMBDA", "OPEN", "CENTER", "WIN", "LINUX", "WIND", "HOME", "UPCOMING", "RECALL", "DATABASE", "RIDDLE", "AZTEC", "CELLAR", "FORSALE", "APEX", "INFLUENCE", "QUILL", "VS", "VISUAL", "UBUNTU", "TEXT", "MOZILA",  "GOOGLE", "SEARCH", "CONFIG", "SIGMA", "TETA", "ADAPTER", "CAPCOM", "PENTA", "ROBOTIC", "SUBLIME", "SCIENCE", "GORILLA", "ULTIMATE", "LONDON", "ASUS", "UMBRELLA", "CIRCUIT", "ENJOY", "COOL", "ABSTRACT", "TOOL", "GARBAGE", "LOAD", "PROGRESS", "INC", "CODE", "STUDIO", "ENG", "DEVELOPMENT", "STOKE", "TECH", "JUNIOR", "GAMES", "SOFT", "ORG", "FOUND", "S.A.", "CORP"};
    char strings[9901][20];
    for(i=0;i<100;i++){
        strcpy(strings[i],aux[i]);
    }
    int cont = 100;
    for(j=0;j<100;j++){
        for(i=(j+1);i<100;i++){
            strcpy(strings[cont],strings[j]);
            strcat(strings[cont]," ");
            strcat(strings[cont],strings[i]);
            cont++;
        }
    }
    int tam, res;
    char aux2[20];
    for(j=0;j<100;j++){
        for(i=(j+1);i<100;i++){
            for(k=(i+1);k<100;k++){
                strcpy(strings[cont],strings[j]);
                strcat(strings[cont]," ");
                strcat(strings[cont],strings[i]);
                strcat(strings[cont]," ");
                tam = strlen(strings[cont]) + strlen(strings[k]);
                //printf("tam = %d ",tam);
                if(tam>=20){
                    res = 19 - strlen(strings[cont]);
                    strcpy(aux2,strings[k]);
                    aux2[res] = '\0';
                    //printf("res = %d  %s",res,aux2);
                    strcat(strings[cont],aux2);
                    //printf("-- teste --");
                    //printf("%s ",strings[cont]);
                }else{
                    strcat(strings[cont],strings[k]);
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
    for (i = 0; i < n*0.8; i++){
        indice = rand()%9901;
        while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
        }
        strcpy(vetor[i],strings[indice]);
        strcpy(strings[indice],"*");
    }
    /*indice = rand()%9901;
    while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
    }
    for(i=n*0.8;i<n;i++){
        strcpy(vetor[i],strings[indice]);
    }*/
    i = 0.8*n;
    while(i<n){
        indice = rand()%9901;
        while(!strcmp(strings[indice],"*")){
            indice = rand()%9901;
        }
        strcpy(vetor[i],strings[indice]);
        strcpy(vetor[i+1],strings[indice]);
        strcpy(strings[indice],"*");
        i+=2;
    }

}

void Gera_Campo4(int n, char *vetor[]){
    int i, j, k, indice;
    char dia[30][3] = {"01","02","03","04","05","06","07","08","09",
    "10","11","12","13","14","15","16","17","18","19","20","21",
    "22","23","24","25","26","27","28","29","30"};
    char mes[12][3] = {"01","02","03","04","05","06","07","08","09",
    "10","11","12"};
    char ano[29][5] = {"1990","1991","1992","1993","1994","1995","1996","1997","1998","1999",
    "2000","2001","2002","2003","2004","2005","2006","2007","2008","2009","2010","2011","2012"
    ,"2013","2014","2015","2016","2017","2018"};
    char strings[10440][11];
    int cont = 0;
    for(i=0;i<29;i++){
        for(j=0;j<12;j++){
            for(k=0;k<30;k++){
                strcpy(strings[cont],dia[k]);
                strcat(strings[cont],"/");
                strcat(strings[cont],mes[j]);
                strcat(strings[cont],"/");
                strcat(strings[cont],ano[i]);
                cont++;
            }
        }  
    }
    /*printf("Contador: %d",cont);
    for(i=0;i<10440;i++){
        printf("%s -",strings[i]);
    }*/
    
    for (i = 0; i < n*0.85; i++){
        indice = rand()%10440;
        while(!strcmp(strings[indice],"*")){
            indice = rand()%10440;
        }
        strcpy(vetor[i],strings[indice]);
        strcpy(strings[indice],"*");
    }
    /*indice = rand()%10440;
    while(!strcmp(strings[indice],"*")){
            indice = rand()%10440;
    }
    for(i=n*0.85;i<n;i++){
        strcpy(vetor[i],strings[indice]);
    }*/
    i = 0.85*n;
    while(i<n){
        indice = rand()%10440;
        while(!strcmp(strings[indice],"*")){
            indice = rand()%10440;
        }
        strcpy(vetor[i],strings[indice]);
        strcpy(vetor[i+1],strings[indice]);
        strcpy(strings[indice],"*");
        i+=2;
    }
}

