#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcmp
#include <time.h>   //clock
#include <limits.h> //constantes max
#include <stdio.h>

#include "sort.h"


int main(int argc, char* argv[]){
	//comandos para testar capacidade das variaveis na sua maquina.
	/*printf("%*s: %d\n",  14, "INT_MAX", INT_MAX);                //2147483647
	printf("%*s: %d\n",  14, "RAND_MAX", RAND_MAX);              //2147483647
	printf("%*s: %ld\n", 14, "LONG_MAX", LONG_MAX);
	printf("%*s: %ld\n", 14, "CLOCKS_PER_SEC", CLOCKS_PER_SEC); //1000000
	printf("\n* * *\n\n");*/

	//ATENCAO: nao funciona se os parametros nao forem passados por linha de comando!
	//lendo parametros de linha de comando.
	char* ALG = argv[1];
	int   NUM = atoi(argv[2]);
	char* SIT = argv[3];
	int PRINT = (argc == 5);
	if(NUM == 0){
		printf("ERRO: NUM DE ELEMENTOS DESCONHECIDO\n");
		exit(1);
	}

	TArray A;
	allocateArray(&A, NUM);

	//gerando o vetor
	printf("gerando o vetor...\n");
	if(strcmp(SIT, "ordc") == 0)
		generateSorted(&A, A.n);
	else if(strcmp(SIT, "ordi") == 0)
		generateInvert(&A, A.n);
	else if(strcmp(SIT, "ale") == 0)
		generateRandomNoRep(&A, A.n);
	else if(strcmp(SIT, "qord") == 0)
		generateAlmostSortedNoRep(&A, A.n);
	else{
		printf("ERRO: SITUACAO DO VETOR DESCONHECIDA\n");
		freeArray(&A);
		exit(1);
	}

	if(PRINT) printArray(&A);

	long long att = 0;
	long comp = 0;
	long time = 0;

	//ordenando o vetor
	printf("ordenando o vetor...\n");
	if(strcmp(ALG, "bub") == 0){
		time = clock();
		bubbleSort(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "bubo") == 0){
		time = clock();
		bubbleSortO(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "sel") == 0){
		time = clock();
		selectSort(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "selo") == 0){
		time = clock();
		selectSortO(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "ins") == 0){
		time = clock();
		insertionSort(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "inso") == 0){
		time = clock();
		insertionSortO(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "shell") == 0){
		time = clock();
		shellSort(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "qui") == 0){
		time = clock();
		quickSort(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "heap") == 0){
		time = clock();
		heapSort(&A, &att, &comp);
		time = clock() - time;
	}else if(strcmp(ALG, "merge") == 0){
		time = clock();
		mergeSort(&A, &att, &comp);
		time = clock() - time;
	}else{
		printf("ERRO: ALGORITMO DE ORDENACAO DESCONHECIDO\n");
		freeArray(&A);
		exit(1);
	}

	// imprimindo resultados de execucao
	if(!isSorted(&A))
		printf("ERRO: VETOR NAO FOI COMPLETAMENTE ORDENADO!\n");
	if(PRINT) printArray(&A);
	printf("%*s: %s\n",   5, "ALG", ALG);
	printf("%*s: %d\n",   5, "NUM", NUM);
	printf("%*s: %ld\n",  5, "comp", comp);
	printf("%*s: %I64d\n",  5, "att", att);
	printf("%*s: %lfs\n", 5, "tempo", (double)time/1000);

    FILE *saida;
    saida = fopen("resultado.csv","a");
    fprintf(saida,"%s;%s;%d;%ld;%I64d;%lfs\n",ALG,SIT,NUM,comp,att,(double)time/1000);
	freeArray(&A);
	return 0;
}
