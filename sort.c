#include "sort.h"

void bubbleSort(TArray* pA, long long* att, long* comp){
	TItem aux;
	int i,j;
	for(i = 0; i < pA->n-1; i++){
		for(j = 1; j < pA->n-i; j++){
			(*comp)++;
			if(pA->item[j].key < pA->item[j-1].key){
				(*att)+=3;
				aux           = pA->item[j];
				pA->item[j]   = pA->item[j-1];
				pA->item[j-1] = aux;
			}
		}
	}
}

//bubbleSort Otimizado
void bubbleSortO(TArray* pA, long long* att, long* comp){
	TItem aux;
	int i =0,j,flag;
	do{//Ao invés de um for de tamanho n, uma flag verifica se o vetor ja esta ordenado e interrompe o loop.
    (*att)++;
    flag = 0;
    for(j = 1; j < pA->n-i; j++){
			(*comp)++;
			if(pA->item[j].key < pA->item[j-1].key){
				(*att)+=4;
				aux           = pA->item[j];
				pA->item[j]   = pA->item[j-1];
				pA->item[j-1] = aux;
                flag          = 1;
			}
    }
    (*comp)++;
    i++;
	}while(flag == 1);
}

//implementação do selectionsort
void selectSort(TArray* pA,long long* att,long*comp){
	TItem aux;
	int i,j,min;
	for(i = 0; i < pA->n-1; i++){
        (*att)++;
        min = i;
		for(j = i+1; j < pA->n; j++){
			(*comp)++;
			if(pA->item[j].key < pA->item[min].key){//verifica se é o menor elemento
				(*att)++;
                min = j;
			}
		}
        (*att)+=3;//atribui o menor elemento a "primeira" posição daquela execução
        aux           = pA->item[i];
        pA->item[i]   = pA->item[min];
        pA->item[min] = aux;
	}
}

//selection sort modificado
void selectSortO(TArray* pA,long long* att,long* comp){
	TItem aux;
	int i,j,min;
	for(i = 0; i < pA->n-1; i++){
        (*att)++;
        min = i;
		for(j = i+1; j < pA->n; j++){
			(*comp)++;
			if(pA->item[j].key < pA->item[min].key){
				(*att)++;
                min = j;
			}
		}
		(*comp)++;
		if(pA->item[i].key != pA->item[min].key){//verifica se o elemento ja está na posição antes de fazer as atribuições de valor.
            (*att)+=3;
            aux           = pA->item[i];
            pA->item[i]   = pA->item[min];
            pA->item[min] = aux;
		}
	}
}

//implementação do selection sort
void insertionSort(TArray* pA,long long* att,long* comp){
	TItem atual;
	int i,j;

	for(i = 1; i < pA->n; i++){
        (*att)++;
        atual = pA->item[i]; // elege o elemento i
        (*comp)++;
		for(j = i - 1; (j >= 0) &&  (atual.key < pA->item[j].key); j--){ //loop executa enquanto o elemento eleito for menor ou a posição atual >=0 e "empurra" os outros elementos para frente
			(*comp)++;
            (*att)++;
            pA->item[j+1] = pA->item[j];
        }
        pA->item[j+1] = atual;//Atribui o valor elito a posição de parada final
    }
}

void insertionSortO(TArray* pA,long long* att,long* comp){
	TItem atual;

	(*att)++;
	int i,j,min = 0;

	for(i = 1; i < pA->n; i++){// pega o menor elemento do vetor e posiciona na primeira posição (pivo), isso evita que seja necessário a comparação j>=0 no segundo loop do algoritmo.
        (*comp)++;
        if(pA->item[i].key < pA->item[min].key){
            (*att)++;
            min = i;
        }
	}
	(*att)+=3;
    atual           = pA->item[0];
    pA->item[0]   = pA->item[min];
    pA->item[min] = atual;

	for(i = 1; i < pA->n; i++){
        (*att)++;
        atual = pA->item[i];
		for(j = i - 1; (atual.key < pA->item[j].key); j--){
			(*comp)++;
            (*att)++;
            pA->item[j+1] = pA->item[j];
        }
        pA->item[j+1] = atual;
    }
}

void shellSort(TArray* pA,long long* att,long* comp){
	int i,j,h = 1;
	TItem aux;
    while(h < pA->n){ //encontra o primeiro valor de h, que é o valor de divisão do vetor
        (*att)++;
        (*comp)++;
        h = h*3+1;
    }
    while (h>1){
        (*comp)++;
        (*att)++;
        h /= 3; // redefine o valor de h
        for(i = h;i < pA->n;i++){ //Primeiro loop q vai de h a n.
            (*att)+=2;
            (*comp)++;
            aux = pA->item[i];
            j = i;

            while(j >= h && aux.key < pA->item[j-h].key){ // segundo loop que funciona como um insertion entre elementos que estão entre h de distância entre si.
                (*att)+=2;
                (*comp)++;
                pA->item[j] = pA->item[j-h];
                j -= h;
            }
            (*att)++;
            pA->item[j] = aux;
        }
    }
}

void quickSort(TArray* pA,long long* att,long* comp){
	quick(pA,att,comp,0,pA->n);
}

void quick(TArray* pA,long long* att,long* comp, int ini, int fim){
    int i = ini,j = fim-1;
    TItem aux,pivo;
    (*att)++;
    pivo = pA->item[(ini+fim)/2];
    while(i <= j){ //Executa até que as variáveis se encontrem, lembrando que o i começa do inicio e j do fim
        //tem por objetivo manter os elemento menores que o pivô em posições menores que ele,
        //e os maiores,respectivamente, em posições maiores.
        (*comp)++;
        while(pA->item[i].key < pivo.key && i<fim){
            (*comp)++;
            (*att)++;
            i++;
        }
        while(pA->item[j].key > pivo.key && j>ini){
            (*comp)++;
            (*att)++;
            j--;
        }
        if(i <= j){
            (*comp)++;
            (*att)+=5;
            aux = pA->item[i];
            pA->item[i] = pA->item[j];
            pA->item[j] = aux;
            i++;
            j--;
        }
    }
    (*comp)++;
    if( j > ini){ //Chama a função recursivamente para os primeiros elemento do vetora
        quick(pA,att,comp,ini,j+1);
    }
    (*comp)++;
    if(i < fim){ //Chama a função recursivamente para os últimos elemento do vetora
        quick(pA,att,comp,i,fim);
    }
}

void heapSort(TArray* pA,long long* att,long* comp){
	int n = pA->n,i = n/2, pai,filho;
	TItem aux;
	while(1) {
        (*comp)++;
        if (i > 0) { //i começa da posição do meio do vetor e vai até 0
            (*att)+=2;
            i--;
            aux = pA->item[i];
        } else {
            (*att)++;
            n--;
            (*comp)++;
            if (n == 0) return; //Ja n vai do número máximo a 0
            (*att)+=2;
            aux = pA->item[n];
            pA->item[n] = pA->item[0]; //Como o heap montado é de máximo, troca-se a 1 posição, maior elemento para a final.
            //Em seguida, monta-se um heap até a posição n-1.
        }
        (*att)+=2;
        pai = i;
        filho = i * 2 + 1;
        while (filho < n) { //Processo de montagem de um heap de máximo
            (*comp)++;
            if ((filho + 1 < n)  &&  (pA->item[filho + 1].key > pA->item[filho].key))
              filho++;
              (*comp)++;
            if (pA->item[filho].key > aux.key) {
                (*att)+=3;
                pA->item[pai] = pA->item[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        (*att)++;
        pA->item[pai] = aux;
   }
}

void mergeSort(TArray* pA,long long* att,long* comp){
	mergeP(pA, att, comp, 0, pA->n-1);
}

void mergeAux(TArray* pA,long long* att,long* comp,int comeco, int meio, int fim){
    int com1 = comeco, com2 = meio+1, comAux =0, tam= fim-comeco+1;
    TArray aux;
    allocateArray(&aux,tam);
    while(com1 <= meio && com2 <= fim){
        (*comp)++;
        if(pA->item[com1].key < pA->item[com2].key ){ //Verifica entre o primeiro elemento e o do meio qual o menor e o atribui a posição atual do auxiliar
            //Como na execução mais profunda do merge isso ocorre entre dois elementos isso garante que essa comparação garantirá a ordenação
            (*att)+=2;
            aux.item[comAux] =  pA->item[com1];
            com1++;
        }
        else{
            (*att)+=2;
            aux.item[comAux] =  pA->item[com2];
            com2++;
        }
        (*att)++;
        comAux++;
    }

    while(com1 <= meio){ //Caso haja elementos não atribuidos da primeira metade, atribui-os agora
        (*comp)++;
        (*att)+=3;
        aux.item[comAux] =  pA->item[com1];
        comAux++;
        com1++;
    }

     while(com2 <= fim){ //Caso haja elementos não atribuidos da segunda metade, atribui-os agora
        (*comp)++;
        (*att)+=3;
        aux.item[comAux] =  pA->item[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){ //Atribui os elementos ja ordenados no vetor auxilar ao array princiapal
        (*comp)++;
        (*att)++;
        pA->item[comAux] = aux.item[comAux-comeco];
    }
    freeArray(&aux);
}

void mergeP(TArray* pA,long long* att,long* comp,int comeco,int fim){
    if(comeco < fim){
        int meio = (fim+comeco)/2;

        mergeP(pA, att, comp, comeco, meio); //Faz a divisão do problema para a primeira metade do array
        mergeP(pA, att, comp, meio+1, fim); //Faz a divisão do problema para a segunda metade do array
        mergeAux(pA, att, comp, comeco, meio, fim); //Executa o algoritmo de ordenação de fato para o subconjunto do array.
    }
}
