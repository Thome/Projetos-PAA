#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define sigma 256

typedef struct no {
	unsigned int freq;
	char simb;
	no* dir;
	no* esq;
} no;

typedef struct node {
	char rcnv[6]; //Run Count aNd Value
	node *prox;
} node;

node* front;
node* rear;

char* decToHex(int n){
	char hexa[3];
	int i = 0, temp = 0;
	while(n!=0){
		temp = n % 16;
		if (temp < 10){
			hexa[i] = temp + 48;
			i++;
		} else {
			hexa[i] = temp + 55;
			i++;
		}
		
		n = n / 16;
	}

	return hexa;
}

void addrle(int runcount, int runvalue){
	node* novo = malloc(sizeof(node));
	novo.prox = NULL;
	sprintf(novo.rcnv, "%s %s", decToHex(runcount), decToHex(runvalue));
	
	if (rear == NULL){
		front = novo;
		rear = novo;
	} else {
		rear.prox = novo;
		rear = rear.prox;
	}
}

void criar_fila_p_min(){
	//???
}

void inserir_no(heap, unsigned int frequencia, unsigned int simbolo, no* right, no* left){
	//???
}

no* extrair_min(heap){
	
	//as características do primeiro elemento do heap são copiadas para minimo
	no* minimo;
	minimo = (no*) malloc(sizeof(no));
	minimo.freq = 
	minimo.simb = 
	minimo.dir = 
	minimo.esq = 
	
	//remove o primeiro elemento do heap
	//o ultimo elemento vira o primeiro
	//chama uma função no primeiro elemento para garantir a ordenação
	
	return minimo;
}

no* construir_arvore(unsigned int H[], int N){
	unsigned int i;
	fila_p_min* fp_min = criar_fila_p_min();
	
	for(i=0;i<N;i++){
		if(H[i]>0)
			inserir_no(fp_min, H[i], i, NULL, NULL);
	}
	
	while(tamanho(fp_min) > 1){
		no* x = extrair_min(fp_min);
		no* y = extrair_min(fp_min);
		inserir_no(fp_min, x.freq + y.freq, '\0', x, y);
	}
	
	return extrair_min(fp_min);
	
}

int main(int argc, char* argv[]){

	printf("#ARGS = %i\n", argc);
	printf("PROGRAMA = %s\n", argv[0]);
	printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	int seqquant;
	fscanf("%d", &seqquant);
	int T, i;
	unsigned int* histoHuff[sigma];
	long n;
	char byte[10000];
	char* sEnd;
	int runvalue;
	int runcount;
	
	while(seqquant){
		fscanf("%d", &T);
		
		for(i = 0; i < sigma; i++)
			histoHuff[i] = 0;
			
		front = NULL;
		rear = NULL;
		runvalue = -1;
		runcount = 0;
		
		fscanf("%[^\n]%*c", byte);
		while(1){
			if(runvalue == -1){ //se for o primeiro byte da sequência
				n = strtol(byte, &sEnd, 16);
				histoHuff[n]++;
				runvalue = n;
				runcount++;
			} else {			//não for o primeiro byte
				if (sEnd == '\0') { //se é o fim da sequencia
					addrle(runcount, runvalue);
					break;
				} else {			//não é o fim da sequencia
					n = strtol(sEnd, &sEnd, 16);
					histoHuff[n]++;
					
					if(runvalue == n && runcount < 255){ //se o byte for igual ao anterior E runcount menor que o máximo (255, FF)
						runcount++;
					} else { 		// runcount == 255 (FF) OU o byte for diferente
						addrle(runcount, runvalue);
						runvalue = n
						runcount = 0
					}
				}
			}
		}
		
		
		//construir_arvore(histoHuff, sigma);
		//comprimir_com_huffman
		//comparar huffman com rle
		//fprintf porcentagem e compressão menores (ambos em empate)
			
	}
	
	return 0;
}
