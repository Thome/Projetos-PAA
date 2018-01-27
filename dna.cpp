#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string>
using namespace std;

ifstream input;
ofstream output;

typedef struct virus{
	string nome;
	float porcentagem;
}virus;

virus* diseases;

void calcular_tabela(int tab[], string P){
	int m = P.size();
	int j = -1;
	int i = 1;
	for(int contador = 0; contador < m; contador++)
		tab[contador] = -1;
	
	for(i = 1; i < m; i++){
		while(j>=0 && P[j+1]!=P[i]){
			 j = tab[j];
		}
		if(P[j+1] == P[i]){
			j++;
		}
		tab[i] = j;
	}
}

int kmp(int tab[], string T, string P, int tam){
	int n = T.size();
	int m = P.size();
	int j = -1;
	int i = 0;
	int temp = 0;
	int su_m = 0;
	calcular_tabela(tab, P);
	
	for(i = 0; i < n; i++){
		while(j >= 0 && P[j+1] != T[i]){
            j = tab[j];
        }
        if(P[j+1] == T[i]){
			j++;
		} else {
			if (temp >= tam){
				su_m += temp;
				P.erase (0,temp);
				calcular_tabela(tab, P);
				j = -1;
			}
		}
		
		temp = j+1;
		if(j == (int)m-1){
			su_m = m;
			break;
		}
		
	}
	
	if ((float)su_m / (float)m * 100 >= 90){
		return 1;
	} else {
		return 0;
	}
}	

//mergesort intercalar copiar para ordenar diseases de maior para menor %
void copiar(virus S[],virus E[], int n){
	int i=0;	
	for(i=0;i<n;i++){
		S[i] = E[i];
	}
}

void intercalar(virus S[], virus E[], int ini, int meio, int fim){
	int i = ini;
	int j = meio + 1;
	int k = ini;
	while(i <= meio && j <= fim) {
		if(E[i].porcentagem >= E[j].porcentagem)
			S[k++] = E[i++];
		else 
			S[k++] = E[j++];
	}
	if(i > meio) 
		copiar(&S[k], &E[j], fim - j + 1);
	else
		copiar(&S[k], &E[i], meio - i + 1);
	
	copiar(&E[ini], &S[ini], fim - ini + 1);
}

void mergesort(virus S[], virus E[], int ini, int fim){
	int meio = ini + (fim - ini) / 2;
	if(ini < fim){
		mergesort(S, E, ini, meio);
		mergesort(S, E, meio + 1, fim);
	}
	intercalar(S, E, ini, meio, fim);
}
//mergesort intercalar copiar para ordenar diseases de maior para menor %

int main(int argc, char* argv[]){
	
	//Ilustrando uso de argumentos de programa
	printf("#ARGS = %i\n", argc);
	printf("PROGRAMA = %s\n", argv[0]);
	printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);
	// Abrindo arquivos
	input.open(argv[1]);
	output.open(argv[2]);
	
	int tam, n_diseases, n_genes, genes_ativos;
	string T, gene;
	
	input >> tam;
	input >> T;
	input >> n_diseases;
	diseases = new virus[n_diseases];
	
	for(int i = 0; i < n_diseases; i++){
		input >> diseases[i].nome >> n_genes;
		genes_ativos = 0;
		int *tab;
		
		for(int j = 0; j < n_genes; j++){
			input >> gene;
			tab = new int[gene.size()];
			if(kmp(tab, T, gene, tam)){
				genes_ativos++;
			}
		}
		
		diseases[i].porcentagem = round(((float)genes_ativos / (float)n_genes) * 100.0);
		delete[] tab;
	}
	
	virus *temp;
	temp = new virus[n_diseases];
	mergesort(temp,diseases,0,n_diseases-1);
	for(int i = 0; i < n_diseases; i++){
		output << diseases[i].nome << ": " << diseases[i].porcentagem << "%" << endl;
	}
	
	delete[] temp;
	delete[] diseases;
	return 0;
}
