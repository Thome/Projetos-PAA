#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define M 1103515245
#define D 12345

FILE* input;
FILE* output;

int potencia(int b, int e, int p){
    int result = 1;
    b = b % p;
    while (e > 0){
        if (e & 1){
            result = (result * b) % p;
        }
        e = e>>1;
        b = (b*b) % p;
    }
    return result;
}


int G(unsigned int key, char* msg){
    static unsigned char j = 0, y = 0;
    int tamanho = strlen(msg);
    int z, i;

    for (i = 0; i < tamanho; i++){
        if (y > 3){
            int aux = key;
            key = M * aux + D;
            y = 0;
            j = 0;
        }
        z = (key >> j) & 0xFF;
        fprintf(output, "%d ", z^msg[i]);
        y++;
        j+=8;
    }
    fprintf(output, "\n");
    return key;
}

int main(int argc, char* argv[]) {

	printf("#ARGS = %i\n", argc);
	printf("PROGRAMA = %s\n", argv[0]);
	printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);

	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");

	int chaveA, chaveB;
	int primoP, baseG;
	int NM, contador = 0;
    	fscanf(input, "A %d ", &chaveA);
    	fscanf(input, "B %d ", &chaveB);
    	fscanf(input, "DH %d %d ", &primoP, &baseG);

    	int A = potencia(baseG, chaveA, primoP);
    	fprintf(output, "A->B: %d\n", A);
    	int B = potencia(baseG, chaveB, primoP);
    	fprintf(output, "B->A: %d\n", B);

    	int S = potencia(B, chaveA, primoP);
    	int chaveK = S;
    	chaveK = M * chaveK + D;
    	char* mensagem;

    	fscanf(input, "%d ", &NM);
    	while (contador < NM){
        	mensagem = malloc(1001 * sizeof(char));
        	fscanf(input, "%s ", mensagem);
        	if (contador % 2 == 0) {
            		fprintf(output, "A->B: ");
        	} else {
            		fprintf(output, "B->A: ");
        	}
        	chaveK = G(chaveK,mensagem);
        	contador++;
        	free(mensagem);
    	}

	fclose(input);
	fclose(output);

    	return 0;
}
