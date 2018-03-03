#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	printf("#ARGS = %i\n", argc);
	printf("PROGRAMA = %s\n", argv[0]);
	printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	
	int NL;
	int **matriz;
	int largura, altura;
	int i, j;
	fscanf(input, "%d", &NL);
	while(NL){
		NL--;
		fscanf(input, "%d %d", &largura, &altura);
		matriz = malloc(altura * sizeof(char*));
		for (i = 0; i < altura; i++){
			matriz[i] = malloc(largura * sizeof(char));
		}
		
		for (i = 0; i < altura; i++){
			for (j = 0; j < largura; j++){
				fscanf(input, "%c", &matriz[i][j]);
				printf("%c ", matriz[i][j]);
			}
			printf("\n");
		}
		
		
		
		
		for(i = 0; i < largura; i++){
			free(matriz[i]);
		}
		free(matriz);
	}	

return 0;
}
