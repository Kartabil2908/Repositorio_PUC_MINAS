#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char gerarLetra(unsigned int seed) {
    srand(seed);
    return 'a' + (rand() % 26);
}

void aleatoFraseRecursiva(const char* frase, char* resposta, size_t index, char letra1, char letra2) {
    size_t len = strlen(frase);

  
    if (index == len) {
        resposta[index] = '\0';
        return;
    }

    if (frase[index] == letra1) {
        resposta[index] = letra2;
    } else {
        resposta[index] = frase[index];
    }


    aleatoFraseRecursiva(frase, resposta, index + 1, letra1, letra2);
}

void aleatoFrase(const char* frase, unsigned int seed) {
    char letra1 = gerarLetra(seed);
    char letra2 = gerarLetra(seed + 1);

    size_t len = strlen(frase);
    char resposta[len + 1];
    
 
    aleatoFraseRecursiva(frase, resposta, 0, letra1, letra2);

    printf("%s\n", resposta);
}

int main() {
    char palavra1[100];
    unsigned int seed = 4;

    while (fgets(palavra1, sizeof(palavra1), stdin)) {
        palavra1[strcspn(palavra1, "\n")] = '\0';

        if (strcmp(palavra1, "FIM") == 0) {
            break;
        }

        aleatoFrase(palavra1, seed);
    }

    return 0;
}
