#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Code.h"

/*Função responsável por gerar um vetor com um número n de registros*/
void GeraDados(int n, REGISTRO *reg)
{
    int *campo1 = (int *)malloc(n * sizeof(int)); //Cria um inteiro para o campo 1 e aloca memória para ele
    char **campo2 = (char **)malloc(n * sizeof(char *)); // Cria um vetor de strings para o campo 2 e aloca memória
    char **campo3 = (char **)malloc(n * sizeof(char *)); // Cria um vetor de strings para o campo 3 e aloca memória
    char **campo4 = (char **)malloc(n * sizeof(char *)); // Cria um vetor de strings para o campo 4 e aloca memória
    for (int i = 0; i < n; i++)
    {
        campo2[i] = (char *)malloc(30 * sizeof(char)); //Alocação de memória
        campo3[i] = (char *)malloc(20 * sizeof(char)); //Alocação de memória
        campo4[i] = (char *)malloc(11 * sizeof(char)); //Alocação de memória
    }
    Gera_Campo1(n, campo1); //Chama a função que gera os dados do campo1
    Gera_Campo2(n, campo2); //Chama a função que gera os dados do campo2
    Gera_Campo3(n, campo3); //Chama a função que gera os dados do campo3
    Gera_Campo4(n, campo4); //Chama a função que gera os dados do campo4
    for (int i = 0; i < n; i++)
    {
        reg[i].campo1 = campo1[i];       //Passa os valores para o registro que foi passado por referência
        strcpy(reg[i].campo2, campo2[i]);
        strcpy(reg[i].campo3, campo3[i]);
        strcpy(reg[i].campo4, campo4[i]);
    }
    free(campo1);   //Libera memória dos campos
    free(campo2);
    free(campo3);
    free(campo4);
}
/*Função responsável por receber um vetor de registros de tamanho e gerar
um arquivo binário com eles salvos*/
int GerarArquivo(int n, REGISTRO *reg, char *arq_name)
{
    FILE *arq = fopen(arq_name, "w+b"); //Cria e abre um arquivo para escrita
    if (arq == NULL)  //Se o arquivo for nulo, retorna zero
    {
        return 0;
    }
    char status = '0';   //Seta o status como zero para começar a mexer no arquivo
    fwrite(&status, sizeof(char), 1, arq); //Escreve o status zero no arquivo
    for (int i = 0; i < n; i++)   //Percorre os n registros
    {   //Escreve no arquivo os registros armazenados anteriormente em reg
        fwrite(&reg[i].campo1, sizeof(int), 1, arq);
        fwrite(&reg[i].campo2, 30 * sizeof(char), 1, arq);
        fwrite(&reg[i].campo3, 20 * sizeof(char), 1, arq);
        fwrite(&reg[i].campo4, 10 * sizeof(char), 1, arq);
    }
    status = '1'; //Seta o status como 1, pois acabou de se mexer no arquivo
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq); //Escreve esse status no arquivo
    fclose(arq); //Fecha o arquivo
    return 1;
}
/*Função responsável por ler um arquivo binário com arq_name e passar os registros
para um vetor de ponteiros reg e o total de registros salvos para o ponteiro n*/
int LeArquivo(REGISTRO **reg, char *arq_name, int *n)
{
    //Abre o arquivo com o nome recebido de parâmetro e testa se abriu certo
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
    //Realiza o cálculo do número de registros no arquivo
    *n = *n - sizeof(char);
    *n = *n / 64; // 64 - número de bytes de um registro
    //Aloco o vetor reg que receberá os resgistros
    *reg = (REGISTRO *)malloc(((*n + 1) * sizeof(REGISTRO)));
    //Vetor auxiliar utilizado para realizar fread
    REGISTRO *a = (REGISTRO *)malloc((*n) * sizeof(REGISTRO));
    //Escrevo o status no cabeçalho
    char status = '0';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fseek(arq, sizeof(char), SEEK_SET);
    //Leio campo a campo de cada registro passando do a para o reg
    for (int i = 0; i < *n; i++)
    {
        fread(&a[i].campo1, sizeof(int), 1, arq);
        fread(&a[i].campo2, 30 * sizeof(char), 1, arq);
        fread(&a[i].campo3, 20 * sizeof(char), 1, arq);
        fread(&a[i].campo4, 10 * sizeof(char), 1, arq);
        //Passo como ultima posição do campo 4 o \0 para não printar lixo
        a[i].campo4[10] = '\0';
        reg[0][i] = a[i];
    }
    //Libero o vetor a
    free(a);
    //Volto o status para 1 e fecho o arquivo
    status = '1';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fclose(arq);
    return 1;
}
/*Função responsável por gerar os dados do campo1 passando-os para o *vetor de tamanho n*/
void Gera_Campo1(int n, int *vetor)
{
    //Variável i auxiliar para os loop e a indice guardará os valores sorteados aleatoriamente pela rand
    int i, indice;
    //Crio um vetor de 50000 posições em que cada posção i possui o valor i
    int *aux = (int *)malloc(50000 * sizeof(int));
    for (i = 0; i < 50000; i++)
    {
        aux[i] = i;
    }
    //Para 70% de n registros
    for (i = 0; i < n * 0.7; i++)
    {
        indice = rand() % 50000; // gero um valor aleatório para o indice no intervalo de 0 - 50000
        while (aux[indice] == (-1))//testo se a posição aux[indice] já não foi pega para assim não repetir
        {
            indice = rand() % 50000; // se já foi pega (possui -1) resorteio até achar uma não pega
        }
        vetor[i] = aux[indice]; //passo o valor achado não repetido para o vetor[i]
        aux[indice] = -1;//torno -1 essa posição pois peguei ela
    }
    /*indice = rand()%50000;
    while(aux[indice]==(-1)){
        indice = rand()%50000;
    }
    for(i=n*0.7;i<n;i++){
        vetor[i] = aux[indice];
    }*/
    //Para os outros 30% eu vou realizando a mesma coisa porém ao pegar um valor não repetido
    //eu o repito, sendo assim repetições aos pares, e caso os 30% de n for ímpar a última interação é repetida 3 vezes
    i = 0.7 * n;
    while (i < n)
    {
        if ((n - i) == 1)
        {
            indice = rand() % 50000;
            while (aux[indice] == (-1))
            {
                indice = rand() % 50000;
            }
            vetor[n - 1] = aux[indice];
            vetor[n - 2] = aux[indice];
            vetor[n - 3] = aux[indice];
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
/*Função responsável por gerar os dados do campo2 passando-os para o *vetor de tamanho n*/
void Gera_Campo2(int n, char *vetor[])
{
    int i, j, k, indice; //Variáveis auxiliares
    //Aqui, são escritos 100 palavras diferentes em um vetor de strings
    char aux[100][10] = {"GOD", "WAR", "SNIPER", "FIGHT", "BAD", "WEAPON", "FIRE", "ARMY", "ADVANCED", "GHOST", "CHICKEN", "GROW", "HIGH", "MAGIC", "WORLD", "ROCK", "BATTLE", "SNOW", "GAME", "YELLOW", "CALL", "BLACK", "OPS", "HACKER", "SOLDIER", "ZOMBIE", "DRAGONS", "SHIELD", "COLOSSUS", "SHADOW", "DIRTY", "TITANS", "BREAKING", "CRAZY", "NIGHT", "MUTANTS",
                         "HERO", "SPEED", "RACE", "SUN", "AGE", "EMPIRE", "WAKE", "AMNESIA", "AQUA", "LEGEND", "COUNTER", "KINGS", "DARK", "WATCH", "DOGS", "ORIGINS", "DEFEAT", "DAY", "DIRT", "EURO", "FAR", "CRY", "HONOR", "SIMULATOR", "DESTINY", "GRAND", "HITMAN", "BIOSHOCK", "BOARD", "CAUSE", "LAYERS", "DEAD", "LIFE", "STRANGE", "MAFIA", "MEDAL", "EARTH", "GOAT", "ORCS", "PORTAL", "ROCKET", "SLEEPING", "STAR", "SUPREME", "SURGEON", "TEAM", "FOREST", "WITCHER", "TROPICO", "TIBIA", "RAINBOW", "TALES", "ZELDA", "AUTO", "SIEGE", "ELDER", "SCROLL", "FARM", "HOTEL", "QUAKE", "HALF", "FEAR", "SOULS", "GREAT"};
    char strings[9901][30]; //Cria um novo vetor de strings que irá guardar concatenações dessas palavras escritas acima
    for (i = 0; i < 100; i++) //Percorre as 100 palavras
    {
        strcpy(strings[i], aux[i]); //Copia cada palavra para o novo vetor de strings
    }
    int cont = 100;
    for (j = 0; j < 100; j++)  //Percorre novamente as 100 palavras
    {
        for (i = (j + 1); i < 100; i++)
        {
            strcpy(strings[cont], strings[j]); //Aqui, vai concatenando as palavras duas a duas, de modo a gerar nomes de jogos diferentes entre si
            strcat(strings[cont], " ");
            strcat(strings[cont], strings[i]);
            cont++;
        }
    }
    for (j = 0; j < 100; j++)  //Percorre mais uma vez as palavras
    {
        for (i = (j + 1); i < 100; i++)
        {
            for (k = (i + 1); k < 100; k++)
            {
                strcpy(strings[cont], strings[j]);  //Aqui, as concatena novamente, mas agora 3 a 3, gerando mais nomes novos
                strcat(strings[cont], " ");
                strcat(strings[cont], strings[i]);
                strcat(strings[cont], " ");
                strcat(strings[cont], strings[k]);
                cont++;
            }
            break;    //dá um break pois nesse ponto já foi gerado um número suficiente de nomes para serem escritos nos arquivos
        }
    }

    for (i = 0; i < n * 0.75; i++)   //Percorre 75% do total de registros digitados pelo usuário
    {
        indice = rand() % 9901; //Sorteia um valor para o indice
        while (!strcmp(strings[indice], "*")) //Enquanto não tiver *, o nome do indice em questão ainda não foi utilizado
        {
            indice = rand() % 9901;  //Se tiver "*", sorteia um novo índice
        }
        strcpy(vetor[i], strings[indice]);
        strcpy(strings[indice], "*");
    }
    //Para os outros 30% eu vou realizando a mesma coisa porém ao pegar um valor não repetido
    //eu o repito, sendo assim repetições aos pares, e caso os 30% de n for ímpar a última interação é repetida 3 vezes
    i = 0.75 * n;
    while (i < n)
    {
        if ((n - i) == 1)
        {
            indice = rand() % 9901;
            while (!strcmp(strings[indice], "*"))
            {
                indice = rand() % 9901;
            }
            strcpy(vetor[n - 1], strings[indice]);
            strcpy(vetor[n - 2], strings[indice]);
            strcpy(vetor[n - 3], strings[indice]);
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
/*Função responsável por gerar os dados do campo3 passando-os para o *vetor de tamanho n*/
void Gera_Campo3(int n, char *vetor[])
{
    int i, j, k, indice;
    /*São escritas 100 palavras a mão e passadas para o vetor de strings aux */
    char aux[100][20] = {"UBI", "NINTENDO", "MICRO", "EA", "LG", "ROCKSTAR", "NEW", "ATLAS", "SIRIUS", "GIGA", "RIO", "BIT", "ROCKLAND", "WIZARD", "SWIFT", "AMAZON", "MANAGER", "YORK", "APPLE", "SILICON", "JDK", "ORACLE", "SYSTEM", "WARNER", "MARVEL", "SONY", "ACER", "LENOVO", "HP", "ATARI", "SPACE", "FOX", "DIGITAL", "PLAY", "SIMS", "SAMSUNG",
                         "RISE", "EUREKA", "RACE", "ALPHA", "LAMBDA", "OPEN", "CENTER", "WIN", "LINUX", "WIND", "HOME", "UPCOMING", "RECALL", "DATABASE", "RIDDLE", "AZTEC", "CELLAR", "FORSALE", "APEX", "INFLUENCE", "QUILL", "VS", "VISUAL", "UBUNTU", "TEXT", "MOZILA", "GOOGLE", "SEARCH", "CONFIG", "SIGMA", "TETA", "ADAPTER", "CAPCOM", "PENTA", "ROBOTIC", "SUBLIME", "SCIENCE", "GORILLA", "ULTIMATE", "LONDON", "ASUS", "UMBRELLA", "CIRCUIT", "ENJOY", "COOL", "ABSTRACT", "TOOL", "GARBAGE", "LOAD", "PROGRESS", "INC", "CODE", "STUDIO", "ENG", "DEVELOPMENT", "STOKE", "TECH", "JUNIOR", "GAMES", "SOFT", "ORG", "FOUND", "S.A.", "CORP"};
    //É declarado o vetor que conterá todas as strings posspiveis geradas
    //Esse numero 9901 foi obtido através de testes para um vetor bem maior e ai depois foi modificado para ficar certinho
    char strings[9901][20];
    for (i = 0; i < 100; i++)
    {
        //As primeiras 100 posições de string possuiram somente uma palavra (o que tinha no aux)
        strcpy(strings[i], aux[i]);
    }
    int cont = 100;
    for (j = 0; j < 100; j++)
    {
        for (i = (j + 1); i < 100; i++)
        {
            //A partir daqui começam a se concatenar as 100 primeiras com as outras sem se repetir
            //a inicial ex: UBI NITENDO , UBI MICRO ....
            // NITENDO MICRO, NINTENDO EA ...
            strcpy(strings[cont], strings[j]);
            strcat(strings[cont], " ");
            strcat(strings[cont], strings[i]);
            cont++;
        }
    }
    int tam, res;
    char aux2[20];
    //Aqui começa a concatenar de três a três, também sem se repetir nenhuma das palavras
    //da mesma forma de para duas porém agora para três
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
                if (tam >= 20)
                {
                    res = 19 - strlen(strings[cont]);
                    strcpy(aux2, strings[k]);
                    aux2[res] = '\0';
                    strcat(strings[cont], aux2);
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
    //Aqui de 0 até 80% é realizado um rand para indice e com ele se acessa o vetor string que tem todas as strings geradas, se checa se ela não possui * que quer dizer que já foi pega, então assim garante que não há repetições
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
    //Para os outros 20% eu vou realizando a mesma coisa porém ao pegar um valor não repetido
    //eu o repito, sendo assim repetições aos pares, e caso os 30% de n for ímpar a última interação é repetida 3 vezes
    i = 0.8 * n;
    while (i < n)
    {
        if ((n - i) == 1)
        {
            indice = rand() % 9901;
            while (!strcmp(strings[indice], "*"))
            {
                indice = rand() % 9901;
            }
            strcpy(vetor[n - 1], strings[indice]);
            strcpy(vetor[n - 2], strings[indice]);
            strcpy(vetor[n - 3], strings[indice]);
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
/*Função responsável por gerar os dados do campo4 passando-os para o *vetor de tamanho n*//*Função responsável por gerar os dados do campo4 passando-os para o *vetor de tamanho n*/
void Gera_Campo4(int n, char *vetor[])
{
    int i, j, k, indice; //Declara variáveis auxiliares
    //Aqui, são escritas diversas datas diferentes
    char dia[30][4] = {"01/", "02/", "03/", "04/", "05/", "06/", "07/", "08/", "09/", 
                       "10/", "11/", "12/", "13/", "14/", "15/", "16/", "17/", "18/", "19/", "20/", "21/",
                       "22/", "23/", "24/", "25/", "26/", "27/", "28/", "29/", "30/"};
    char mes[12][4] = {"01/", "02/", "03/", "04/", "05/", "06/", "07/", "08/", "09/",
                       "10/", "11/", "12/"};
    char ano[29][5] = {"1990", "1991", "1992", "1993", "1994", "1995", "1996", "1997", "1998", "1999",
                       "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018"};
    char strings[10440][11];
    int cont = 0;
    for (i = 0; i < 29; i++)  //Percorre os dados escritos
    {
        for (j = 0; j < 12; j++)
        {
            for (k = 0; k < 30; k++)
            {
                strcpy(strings[cont], dia[k]); //Vai concatenando dia mes e ano de modo a formar datas completas
                strcat(strings[cont], mes[j]);
                strcat(strings[cont], ano[i]);
                cont++;
            }
        }
    }

    for (i = 0; i < n * 0.85; i++)
    {
        indice = rand() % 10440;         //Sorteia um indice
        while (!strcmp(strings[indice], "*")) //Se ele tiver *, então a data desse indice já foi utilizada
        {
            indice = rand() % 10440;  //Nesse caso, sorteia uma nova data
        }
        strcpy(vetor[i], strings[indice]);  //Passa essa data para o vetor[i]
        strcpy(strings[indice], "*");      //Seta ela em strings como *, para indicar que já foi utilizada
    }
 //Para os outros 30% eu vou realizando a mesma coisa porém ao pegar um valor não repetido
 //eu o repito, sendo assim repetições aos pares, e caso os 30% de n for ímpar a última interação é repetida 3 vezes
    i = 0.85 * n;
    while (i < n)
    {
        if ((n - i) == 1)
        {
            indice = rand() % 10440;
            while (!strcmp(strings[indice], "*"))
            {
                indice = rand() % 10440;
            }
            strcpy(vetor[n - 1], strings[indice]);
            strcpy(vetor[n - 2], strings[indice]);
            strcpy(vetor[n - 3], strings[indice]);
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
/*Função utilizada no processo de ordenação de um vetor de registros reg juntamente com a mergeSort*/
void merge(REGISTRO **reg, int comeco, int meio, int fim)
{

    // int auxC2 = 0, auxC3 = 0, auxC4 = 0; //Variáveis auxiliares para a comparação de strings

    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    REGISTRO *vetAux = (REGISTRO *)malloc((tam + 1) * sizeof(REGISTRO));
    int teste;
    while (com1 <= meio && com2 <= fim)
    {

        teste = compara_reg(reg[0][com1], reg[0][com2]);
        if (teste == 1)
        {
            vetAux[comAux] = reg[0][com1];
            com1++;
        }
        else
        {
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
/*Função sort utilizada no processo de ordenação de um vetor de registros reg (algoritmo sort MergeSort de complexidade O(nlogn))*/
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
//Função responsável por realizar operação de merge entre dois arquivos arq_name1 e arq_name2
//gerando um arquivo final que possui todos os registros dos outros dois ordenados
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
    REGISTRO *reg1 = (REGISTRO *)malloc((n1 + 1) * sizeof(REGISTRO));
    REGISTRO *reg2 = (REGISTRO *)malloc((n2 + 1) * sizeof(REGISTRO));
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
    fread(&reg_aux.campo1, sizeof(int), 1, arq1);
    fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq1);
    fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq1);
    fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq1);
    reg1[cont1] = reg_aux;
    fread(&reg_aux.campo1, sizeof(int), 1, arq2);
    fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq2);
    fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq2);
    fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq2);
    reg2[cont2] = reg_aux;
    while (1)
    {
        teste = compara_reg(reg1[cont1], reg2[cont2]); //Compara reg1 com reg2 e passa o valor do menor para teste. Se 1 for menor, teste recebe 1, caso contrário, recebe 1
        //Nos próximos condicionais, o valor de teste é checado e, de acordo com ele, é escrito ou o registro 1 ou o 2 no arquivo final
        if (teste == 1) 
        {
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10 * sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq1);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq1);
            reg1[cont1] = reg_aux;
        }
        else if (teste == -1)
        {
            fwrite(&reg2[cont2].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg2[cont2].campo2, 30 * sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo3, 20 * sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo4, 10 * sizeof(char), 1, arq_fin);
            cont2++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq2);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq2);
            reg2[cont2] = reg_aux;
        }
        else
        {
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10 * sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq1);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq1);
            reg1[cont1] = reg_aux;
            cont2++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq2);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq2);
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
        fwrite(&reg1[cont1].campo2, 30 * sizeof(char), 1, arq_fin);
        fwrite(&reg1[cont1].campo3, 20 * sizeof(char), 1, arq_fin);
        fwrite(&reg1[cont1].campo4, 10 * sizeof(char), 1, arq_fin);
        cont1++;
        if (cont1 != n1)
        {
            fread(&reg_aux.campo1, sizeof(int), 1, arq1);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq1);
            reg1[cont1] = reg_aux;
        }
    }
    while (cont2 < n2)
    {
        fwrite(&reg2[cont2].campo1, sizeof(int), 1, arq_fin);
        fwrite(&reg2[cont2].campo2, 30 * sizeof(char), 1, arq_fin);
        fwrite(&reg2[cont2].campo3, 20 * sizeof(char), 1, arq_fin);
        fwrite(&reg2[cont2].campo4, 10 * sizeof(char), 1, arq_fin);
        cont2++;
        if (cont2 != n1)
        {
            fread(&reg_aux.campo1, sizeof(int), 1, arq2);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq2);
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
/*Função responsável por realizar operação de match entre dois arquivos arq_name1 e arq_name2
gerando um arquivo final que possui todos a intersecção dos registros dos outros dois ordenados*/
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
    REGISTRO *reg1 = (REGISTRO *)malloc((n1 + 1) * sizeof(REGISTRO));
    REGISTRO *reg2 = (REGISTRO *)malloc((n2 + 1) * sizeof(REGISTRO));
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
    fread(&reg_aux.campo1, sizeof(int), 1, arq1);
    fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq1);
    fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq1);
    fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq1);
    reg1[cont1] = reg_aux;
    fread(&reg_aux.campo1, sizeof(int), 1, arq2);
    fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq2);
    fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq2);
    fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq2);
    reg2[cont2] = reg_aux;
    while (1)
    {
        teste = compara_reg(reg1[cont1], reg2[cont2]); //Compara reg1 com reg2 e passa o valor do menor para teste. Se 1 for menor, teste recebe 1, caso contrário, recebe 1
        //Nos próximos condicionais, o valor de teste é checado e, de acordo com ele, é escrito ou o registro 1 ou o 2 no arquivo final
        if (teste == 1)
        {
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10 * sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq1);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq1);
            reg1[cont1] = reg_aux;
        }
        else if (teste == -1)
        {
            fwrite(&reg2[cont2].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg2[cont2].campo2, 30 * sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo3, 20 * sizeof(char), 1, arq_fin);
            fwrite(&reg2[cont2].campo4, 10 * sizeof(char), 1, arq_fin);
            cont2++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq2);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq2);
            reg2[cont2] = reg_aux;
        }
        else
        {
            fwrite(&reg1[cont1].campo1, sizeof(int), 1, arq_fin);
            fwrite(&reg1[cont1].campo2, 30 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo3, 20 * sizeof(char), 1, arq_fin);
            fwrite(&reg1[cont1].campo4, 10 * sizeof(char), 1, arq_fin);
            cont1++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq1);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq1);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq1);
            reg1[cont1] = reg_aux;
            cont2++;
            fread(&reg_aux.campo1, sizeof(int), 1, arq2);
            fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq2);
            fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq2);
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
/*Função auxiliar utilizada em vários outros processos que possui a funcionalidade de comparar
dois registros retornando 1 caso reg1<reg2 , -1 caso reg2<reg1 e 0 caso reg1 = reg2*/
int compara_reg(REGISTRO reg1, REGISTRO reg2)
{
    if (reg1.campo1 < reg2.campo1) //Compara o campo 1. Se o campo 1 do registro 1 for menor, retorna 1
    {
        return 1;
    }
    else if (reg2.campo1 < reg1.campo1) //Se o campo 1 do registro 2 for menor, retorna -1
    {
        return -1;
    }
    else //Se eles forem iguais, passa para a análise do campo2
    {
        int a, n; //Variáveis auxiliares
        if (strlen(reg1.campo2) < strlen(reg2.campo2)) //Compara o tamanho do campo2 de cada registro e pega o menor
        {
            n = strlen(reg1.campo2);
            a = 1;
        }
        else if (strlen(reg2.campo2) < strlen(reg1.campo2))  //Compara o tamanho do campo2 de cada registro e pega o menor
        {
            n = strlen(reg2.campo2);
            a = -1;
        }
        else
        {
            n = strlen(reg1.campo2);
            a = 0;
        }
        for (int j = 0; j < n; j++)  //Percorre o campo2 byte a byte(char por char), baseado no menor tamanho 
        {
            if (reg1.campo2[j] < reg2.campo2[j])  //No momento em que uma posição de algum dos registros for menor, retorna 1 ou -1 de acordo com o registro
            {
                return 1;
            }
            else if (reg2.campo2[j] < reg1.campo2[j]) //No momento em que uma posição de algum dos registros for menor, retorna 1 ou -1 de acordo com o registro
            {
                return -1;
            }
            else if (j == n - 1 && a == 1) //No momento em que uma posição de algum dos registros for menor, retorna 1 ou -1 de acordo com o registro
            {
                return 1;
            }
            else if (j == n - 1 && a == -1) //No momento em que uma posição de algum dos registros for menor, retorna 1 ou -1 de acordo com o registro
            {
                return -1;
            }
        }
        if (a == 0) //Se o campo 2 de ambos os registros for igual, vai para a análise do campo 3
        {
            if (strlen(reg1.campo3) < strlen(reg2.campo3)) //Novamente, pega o menor comprimento dentre os dois camps 3 analisados
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
            for (int j = 0; j < n; j++) //Percorre char por char baseado no menor comprimento
            {
                if (reg1.campo3[j] < reg2.campo3[j]) //Retorna 1 ou -1 baseado no menor valor de um ou outro registro, seguindo as regras defiinidas anteriormente
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
            if (a == 0) //Se forem iguais, parte para a análise do campo 4
            {
                int compare4;
                for (int j = 6; j < 10; j++) //Compara primeiramente a parte dos anos 
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
                if (compare4 == 0) //Se os anos forem iguais, compara os meses
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
                    if (compare4 == 0) //Se possuirem mês igual eu comparo os dias até achar o menor deles
                    {
                        
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
/*Funçao responsável pelo processo inicial de manipulação dos K arquivos, como sua abertura, escrita do status, leitura dos primeiros registros de cada arquivo, criação do arquivo final e depois de chamar a recursive_multMerge fechar os arquivos após manipulação*/
int multiway_merging(char **arquivos_entrada,char ** arq_fname ,int num_arq)
{
    //Abrindo os arquivos
    FILE *arq[num_arq];

    int n[num_arq]; //n será o vetor que guarda quantidade de registros em cada arquivo
    int cont_arq[num_arq]; //será o contador de quantos registros já foram lidos de cada arquivo
    
    REGISTRO **reg = (REGISTRO **) malloc((num_arq) * sizeof(REGISTRO*)); //Criando  os registros para fazer análises 

    REGISTRO reg_aux;
   
    for(int i = 0; i < num_arq; i++)
    {
        arq[i] = fopen(arquivos_entrada[i], "r+b");
        if(arq[i] == NULL)
            return -1;
        fseek(arq[i], 0, SEEK_END); //Pulando para o fim de cada arquivo
        n[i] = ftell(arq[i]); //Lê o indicador de posição em bytes
        if(n[i] == 0) // Se um dos arquivos estiverem vazios
            return 0;
        //Calculando a quantidade de elementos de cada arquivo
        n[i] = n[i] - sizeof(char);
        n[i] = n[i] / 64; 
        //Alocando memória para os registros
        reg[i] = (REGISTRO *) malloc(n[i] * sizeof(REGISTRO));
        //Escrevendo o status nos arquivos abertos
        rewind(arq[i]);
        char status = '0';
        fwrite(&status, sizeof(char), 1, arq[i]);
        fseek(arq[i], sizeof(char), SEEK_SET);
        //Lendo o primeiro registro de cada arquivo
        fread(&reg_aux.campo1, sizeof(int), 1, arq[i]);
        fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq[i]);
        fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq[i]);
        fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq[i]);
        reg[i][0] = reg_aux;
        cont_arq[i] = 0; //inicializo contadores como zero
    }
    //Arquivo final é criado e escrito o status
    FILE *arq_fin = fopen(arq_fname, "w+b");
    if(arq_fin == NULL)
        return -1;
    char status = '0';
    fwrite(&status, sizeof(char), 1, arq_fin);
    //É chamado a função recursive_multMerge que irá ir lendo os registros, achando os menores pela árvore de seleção na função Acha_menor e escrevendo os menores no arquivo final
    recursive_multMerge(reg,arq,arq_fin,n,num_arq,cont_arq);
    for(int i = 0; i < num_arq; i++){
        status = '1';
        rewind(arq[i]);
        fwrite(&status, sizeof(char), 1, arq[i]);
        fclose(arq[i]);
    }
    rewind(arq_fin);
    fwrite(&status, sizeof(char), 1, arq_fin);
    fclose(arq_fin);
    return 1;
}
/*Função que irá ir realizando a leitura dos arquivos e chamando a Acha_menor para encontrar o menor entre os lidos e escrevendo esse no arquivo final, quando um dos arquivos acaba a função é chamada recursivamente, desconsiderando especificamente aquele arquivo*/ 
int recursive_multMerge(REGISTRO **reg, FILE *arq[], FILE *arq_fin, int n[], int num_arq, int cont_arq[])
{   
    REGISTRO reg_aux; //Registro auxiliar utilizado para leitura dos registros dos arquivos
    REGISTRO Vet_aux[num_arq];// Vetor de registro auxiliar que utilizado para passar p/ Acha_menor
    REGISTRO menor; //Registro menor retornado pela Acha_menor
    int i, teste;
    if(num_arq == 1){
        while (cont_arq[0] < n[0])
        {
            fwrite(reg[0][cont_arq[0]].campo1, sizeof(int), 1, arq_fin);
            fwrite(reg[0][cont_arq[0]].campo2, 30 * sizeof(char), 1, arq_fin);
            fwrite(reg[0][cont_arq[0]].campo3, 20 * sizeof(char), 1, arq_fin);
            fwrite(reg[0][cont_arq[0]].campo4, 10 * sizeof(char), 1, arq_fin);
            cont_arq[0]++;
            if (cont_arq[0] != n[0])
            {
                fread(&reg_aux.campo1, sizeof(int), 1, arq[0]);
                fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq[0]);
                fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq[0]);
                fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq[0]);
                reg[0][cont_arq[0]] = reg_aux;
            }
        }
        return 1;
    }
    while(1)
    {
        int i;
        //Passo todas os registros atuais em análise de cada arquivo para o Vet_aux que será usado na Acha_menor
        for(i=0; i<num_arq; i++){
            Vet_aux[i] = reg[i][cont_arq[i]];
            //printf("%d %s %s %s \n",Vet_aux[i].campo1,Vet_aux[i].campo2,Vet_aux[i].campo3,Vet_aux[i].campo4);
        }
        //Passo o menor registro achado para menor
        Acha_menor(Vet_aux,i,&menor);
        for(i=0; i<num_arq; i++){
            //Testo de qual arquivo pertence o menor registro e ao achar eu escrevo o menor registro achado no arquivo final, leio mais um registro do arquivo ao qual pertence o menor e incremento seu contador
            if(menor.campo1 == reg[i][cont_arq[i]].campo1 && !strcmp(menor.campo2,reg[i][cont_arq[i]].campo2) && !strcmp(menor.campo3,reg[i][cont_arq[i]].campo3) && !strcmp(menor.campo4,reg[i][cont_arq[i]].campo4) ){
                fwrite(&reg[i][cont_arq[i]].campo1, sizeof(int), 1, arq_fin);
                fwrite(&reg[i][cont_arq[i]].campo2, 30 * sizeof(char), 1, arq_fin);
                fwrite(&reg[i][cont_arq[i]].campo3, 20 * sizeof(char), 1, arq_fin);
                fwrite(&reg[i][cont_arq[i]].campo4, 10 * sizeof(char), 1, arq_fin);
                cont_arq[i]++;
                fread(&reg_aux.campo1, sizeof(int), 1, arq[i]);
                fread(&reg_aux.campo2, 30 * sizeof(char), 1, arq[i]);
                fread(&reg_aux.campo3, 20 * sizeof(char), 1, arq[i]);
                fread(&reg_aux.campo4, 10 * sizeof(char), 1, arq[i]);
                reg[i][cont_arq[i]] = reg_aux;
                
                if (cont_arq[i]>=n[i])
                {
                    teste = 1; //testa se o contador de um dos arquivos já leu todo os seus registros, ou seja, se o arquivo já foi todo lido
                    break;
                }
            }
        }

        if(teste == 1)
            break ;//um dos arquivos já foi totalmente lido, então tenho que desconsiderar ele agora 
    }
    //Agora vou gerar os novos vetores de arquivos, contadores e n sem o arquivo que foi encerrado
    FILE *novos_arquivos[num_arq-1];
    int novo_n[num_arq-1];
    int novo_cont_arq[num_arq-1];
    REGISTRO **novo_reg = (REGISTRO**) malloc((num_arq-1)*sizeof(REGISTRO*));

    for(int j=0;j<num_arq-1;j++){
        if(j>=i){
            novos_arquivos[j] = arq[j+1];
            novo_n[j] = n[j+1];
            novo_cont_arq[j] = cont_arq[j+1];
            novo_reg[j] = reg[j+1];
        }
        novos_arquivos[j] = arq[j];
        novo_n[j] = n[j];
        novo_cont_arq[j] = cont_arq[j];
        novo_reg[j] = reg[j];
    }
    //recursive_multMerge(novo_reg,novos_arquivos,arq_fin,novo_n,num_arq--,novo_cont_arq);*/
    return 1;
}
/*Função responsável que recebe um vetor de registros de cada K arquivo e realiza uma arvore de seleção através de recursão, pois compara de dois a dois e gera um novo vetor com os menores registros para o próxima interação recursiva. No caso de n_reg (números de registros) for ímpar ele comparada dois a dois desconsiderando o última, o qual é incluído na próxima geração*/
void Acha_menor(REGISTRO reg[], int n_reg, REGISTRO* fin)
{   
    //Condição de parada quando o número de registro n_reg for igual a 1
    if(n_reg == 1)
    {
        //Retorna o registro menor entre todos achados para fin
        *fin = reg[0];
    }
    //Testo se o número de registro é par
    else if(n_reg%2 == 0)
    {
        REGISTRO novo_reg[n_reg/2];
        int teste, pos_menor, cont_arq = 0;
        //Vou comparando os registros dois a dois
        for(int i=0; i < n_reg; i+=2)
        {
            //Uso a compara reg para achar o menor
            teste = compara_reg(reg[i],reg[i+1]);
            if(teste >= 0)
                pos_menor = i;
            else 
                pos_menor = i+1;
            //O registro menor é salvo no vetor novo_reg
            novo_reg[cont_arq] = reg[pos_menor];
            cont_arq++;
        }
        //Chamo a próxima intereção passando o novo_vetor de menores obtidos e reduzindo o nro de
        //arquivo em sua metade
        Acha_menor(novo_reg,n_reg/2,fin);
    }
    else
    {
        //Como o número de registros é impar é calculado um novo n_reg da segunte forma
        int aux = (n_reg/2) + 1;
        REGISTRO novo_reg[aux];
        int teste, pos_menor, cont_arq = 0;
        //Vou comparando os registros dois a dois
        for(int i=0; i < n_reg-1; i+=2)
        {
            //Uso a compara reg para achar o menor
            teste = compara_reg(reg[i],reg[i+1]);
            if(teste >= 0)
                pos_menor = i;
            else 
                pos_menor = i+1;
            //O registro menor é salvo no vetor novo_reg
            novo_reg[cont_arq] = reg[pos_menor];
            cont_arq++;
        }
        //O ultimo registro que não é comparada é reservado para a próxima interação
        novo_reg[aux-1] = reg[n_reg-1];
        //Chamo a próxima intereção passando o novo_vetor de menores obtidos e reduzindo o nro de
        //arquivo em sua metade
        Acha_menor(novo_reg,aux,fin);
    }

} 

/*Função que recebe um arquivo inicial (arq_name) e inicia o processo de sortMerge do arquivo
gerando os primeiros sub_arquivos ordenados contendo 1000 registros cada um (equivalente a 4 pág. de disco) e depois chama a recursive_sortMerge para finalizar o processo*/
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
    //Aloco memória para os 1000 registros (4 páginas de disco) que poderei trabalhar no buffer
    REGISTRO *reg = (REGISTRO *)malloc((1000) * sizeof(REGISTRO));
    //Defino status 0 para o arquivo após abri-lo indicando que irei manipula-lo
    char status = '0';
    rewind(arq);
    fwrite(&status, sizeof(char), 1, arq);
    fseek(arq, sizeof(char), SEEK_SET);
    int n_arq, sobra = 0;
    //Calculo do número de subarquivos necessários já considerando o caso de haver sobras (subarquivos que não ocupam necessariamente 16000*4 bytes == 1000 registros)
    if (n % 1000 == 0)
    {
        n_arq = n / 1000;
    }
    else
    {
        n_arq = n / 1000;
        sobra = n - (n_arq * 1000);
        n_arq++;
    }
    //Vetor de strings utilizado para compor o nome dos subarquivos
    char num[10][4] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    char sub_arq_name[20];
    int n_aux;
    FILE *sub_arq;
    int i;
    for (i = 0; i < n_arq; i++)
    {
        //Leio de 1000 em 1000 do meu arquivo de entrada
        for (int j = 0; j < 1000; j++)
        {
            fread(&reg[j].campo1, sizeof(int), 1, arq);
            fread(&reg[j].campo2, 30 * sizeof(char), 1, arq);
            fread(&reg[j].campo3, 20 * sizeof(char), 1, arq);
            fread(&reg[j].campo4, 10 * sizeof(char), 1, arq);
        }
        //Chamo o mergeSort para ordenar os 1000 registros
        mergeSort(&reg, 0, 999);
        //Aqui é realizado uma forma de compor os nomes dos subarquivos
        strcpy(sub_arq_name, "sub_arquivo");
        if (i < 10)
        {
            strcat(sub_arq_name, num[i]);
        }
        else if (i >= 10 && i < 20)
        {
            strcat(sub_arq_name, num[1]);
            n_aux = i - 10;
            strcat(sub_arq_name, num[n_aux]);
        }
        else if (i >= 20 && i < 30)
        {
            strcat(sub_arq_name, num[2]);
            n_aux = i - 20;
            strcat(sub_arq_name, num[n_aux]);
        }
        //Assim que o nome é composto é gerado o sub_arquivo já com o statu
        sub_arq = fopen(sub_arq_name, "w+b");
        status = '0';
        fwrite(&status, sizeof(char), 1, sub_arq);
        //Escrevo os 1000 registros ordenado no subarquivo 
        for (int j = 0; j < 1000; j++)
        {
            fwrite(&reg[j].campo1, sizeof(int), 1, sub_arq);
            fwrite(&reg[j].campo2, 30 * sizeof(char), 1, sub_arq);
            fwrite(&reg[j].campo3, 20 * sizeof(char), 1, sub_arq);
            fwrite(&reg[j].campo4, 10 * sizeof(char), 1, sub_arq);
        }
        //Fecho o subarquivo com o status correto
        status = '1';
        rewind(sub_arq);
        fwrite(&status, sizeof(char), 1, sub_arq);
        fclose(sub_arq);
    }
    //Após gerado todos os primeiros subarquivos com os 1000 registros é chamado a recursive_sortMerge para gerar os restantes de subarquivos 
    int x = recursive_sortMerge(i, 0, arq_fname);
    return 1;
}
/*Função recursiva que a partir dos primeiros subarquivos gerados realiza operação de merge com cada dois arquivos até gerar o arquivo final (arq_fname) com todos os registros de arq_name ordenados*/
int recursive_sortMerge(int n_arq, int cont, char *arq_fname)
{
    //vetor de strings utilizado para compor os nomes dos subarquivos
    char num[10][4] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    char sub_arq_name1[20];
    char sub_arq_name2[20];
    char sub_arq_name3[20];
    int n_aux, i, cont_aux, n;
    //Condição de parada da recursão para quando chegar em um subarquivo só  
    if (n_arq == 1)
    {
        char final[20];
        //Aqui é realizado uma forma de compor os nomes dos subarquivos
        strcpy(final, "sub_arquivo");
        if (cont < 10)
        {
            strcat(final, num[cont]);
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
        //Posteriormente é renomeada para o nome que o usário passou 
        rename(final, arq_fname);
        return 1;
    }
    //Quando haver um número par de subarquivos
    else if (n_arq % 2 == 0)
    {
        n = cont + n_arq;
        cont_aux = n;
        //Aqui é realizado uma forma de compor os nomes dos subarquivos
        for (i = cont; i < n; i += 2)
        {
            strcpy(sub_arq_name1, "sub_arquivo");
            strcpy(sub_arq_name2, "sub_arquivo");
            strcpy(sub_arq_name3, "sub_arquivo");
            if (i < 10)
            {
                strcat(sub_arq_name1, num[i]);
                strcat(sub_arq_name2, num[i + 1]);
            }
            else if (i >= 10 && i < 20)
            {
                strcat(sub_arq_name1, num[1]);
                strcat(sub_arq_name2, num[1]);
                n_aux = i - 10;
                strcat(sub_arq_name1, num[n_aux]);
                strcat(sub_arq_name2, num[n_aux + 1]);
            }
            else if (i >= 20 && i < 30)
            {
                strcat(sub_arq_name1, num[2]);
                strcat(sub_arq_name2, num[2]);
                n_aux = i - 20;
                strcat(sub_arq_name1, num[n_aux]);
                strcat(sub_arq_name2, num[n_aux + 1]);
            }
            if (cont_aux < 10)
            {
                strcat(sub_arq_name3, num[cont_aux]);
            }
            else if (cont_aux >= 10 && cont_aux < 20)
            {
                strcat(sub_arq_name3, num[1]);
                n_aux = cont_aux - 10;
                strcat(sub_arq_name3, num[n_aux]);
            }
            else if (cont_aux >= 20 && cont_aux < 30)
            {
                strcat(sub_arq_name3, num[2]);
                n_aux = cont_aux - 20;
                strcat(sub_arq_name3, num[n_aux]);
            }
            else if (cont_aux >= 30 && cont_aux < 40)
            //Os subarquivos são chmados de dois a dois para realizar o merge
            //gerando um novo sunarquivo com o nome composto
            printf("");
            mergeArq(sub_arq_name1, sub_arq_name2, sub_arq_name3);
            cont_aux++;
        }
        cont = i;
        //chama a recursive divindo pela metade o numero de arquivos e passando
        //o contador para saber aonde parou na contagem dos subarquivos
        recursive_sortMerge(n_arq / 2, cont, arq_fname);
    }
    else
    {
        //Nesse caso o número de arquivos é ímpar sendo assim o é calculado uma sobra
        //, o último subarquivo recebido não vai ser considerado, sendo carregado para próxima operação 
        n = cont + n_arq;
        int sobra = n - 1;
        n--;
        cont_aux = sobra + 1;
        for (i = cont; i < n; i += 2)
        {
            strcpy(sub_arq_name1, "sub_arquivo");
            strcpy(sub_arq_name2, "sub_arquivo");
            strcpy(sub_arq_name3, "sub_arquivo");
            if (i < 10)
            {
                strcat(sub_arq_name1, num[i]);
                strcat(sub_arq_name2, num[i + 1]);
            }
            else if (i >= 10 && i < 20)
            {
                strcat(sub_arq_name1, num[1]);
                strcat(sub_arq_name2, num[1]);
                n_aux = i - 10;
                strcat(sub_arq_name1, num[n_aux]);
                strcat(sub_arq_name2, num[n_aux + 1]);
            }
            else if (i >= 20 && i < 30)
            {
                strcat(sub_arq_name1, num[2]);
                strcat(sub_arq_name2, num[2]);
                n_aux = i - 20;
                strcat(sub_arq_name1, num[n_aux]);
                strcat(sub_arq_name2, num[n_aux + 1]);
            }
            if (cont_aux < 10)
            {
                strcat(sub_arq_name3, num[cont_aux]);
            }
            else if (cont_aux >= 10 && cont_aux < 20)
            {
                strcat(sub_arq_name3, num[1]);
                n_aux = cont_aux - 10;
                strcat(sub_arq_name3, num[n_aux]);
            }
            else if (cont_aux >= 20 && cont_aux < 30)
            {
                strcat(sub_arq_name3, num[2]);
                n_aux = cont_aux - 20;
                strcat(sub_arq_name3, num[n_aux]);
            }
            //Os subarquivos são chmados de dois a dois para realizar o merge
            //gerando um novo sunarquivo com o nome composto
            printf("");
            mergeArq(sub_arq_name1, sub_arq_name2, sub_arq_name3);
            cont_aux++;
        }
        cont = i;
        n_arq = n_arq / 2;
        n_arq++;
        //chama a recursive passando a contar da sobra calculada
        recursive_sortMerge(n_arq, sobra, arq_fname);
    }
}