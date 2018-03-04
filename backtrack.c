#include <stdio.h>
#include <stdlib.h>

void processar(int x, int y, char** matriz, int altura, int largura, int cordx, int cordy, int* flag){

    if (x == altura-1 || x == 0 || y == largura-1 || y == 0){
        printf("SAIDA [%d,%d]\n", x, y);
        *flag = 1;
    } else {
        if (matriz[x][y+1] == '0'){
            printf("D [%d,%d]->[%d,%d]\n", x, y, x, y+1);
            matriz[x][y+1] = 'X';
            processar(x, y+1, matriz, altura, largura, x, y, flag);
        }

        if (matriz[x-1][y] == '0'){
            printf("F [%d,%d]->[%d,%d]\n", x, y, x-1, y);
            matriz[x-1][y] = 'X';
            processar(x-1, y, matriz, altura, largura, x, y, flag);
        }

        if (matriz[x][y-1] == '0'){
            printf("E [%d,%d]->[%d,%d]\n", x, y, x, y-1);
            matriz[x][y-1] = 'X';
            processar(x, y-1, matriz, altura, largura, x, y, flag);
        }

        if (matriz[x+1][y] == '0'){
            printf("T [%d,%d]->[%d,%d]\n", x, y, x+1, y);
            matriz[x+1][y] = 'X';
            processar(x+1, y, matriz, altura, largura, x, y, flag);
        }

        if (cordx != 0 && cordy != 0) { //não é a primeira instancia de processar
            printf("BT [%d,%d]<-[%d,%d]\n", cordx, cordy, x, y);
        } else if (*flag == 0) {         //é a primeira instancia de processar, E não achou saída
            printf("SEM SAIDA\n");
        }
    }


}


int main(){

	FILE* input = fopen("input.txt", "r");

	int NL;
	char **matriz;
	int largura, altura;
	int i, j;
	int a, b;
	int contador = 0;
	int flag;
	fscanf(input, "%d", &NL);
	while(contador < NL){
		fscanf(input, "%d %d ", &largura, &altura);
		matriz = malloc(altura * sizeof(char*));
		for (i = 0; i < altura; i++){
			matriz[i] = malloc(largura * sizeof(char));
		}

		for (i = 0; i < altura; i++){
			for (j = 0; j < largura; j++){
				fscanf(input, "%c ", &matriz[i][j]);
				//printf("%c ", matriz[i][j]);
				if (matriz[i][j] == 'X'){
					a = i;
					b = j;
				}

			}
		}

        printf("L%d:\n", contador);
        printf("INICIO [%d,%d]\n", a, b);
        flag = 0;
        processar(a, b, matriz, altura, largura, 0, 0, &flag);


		for(i = 0; i < altura; i++){
			free(matriz[i]);
		}
		free(matriz);
		contador++;
	}

return 0;
}
