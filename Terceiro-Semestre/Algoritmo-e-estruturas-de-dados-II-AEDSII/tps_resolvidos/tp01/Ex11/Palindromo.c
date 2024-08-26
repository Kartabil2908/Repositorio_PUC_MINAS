#include <stdio.h>
#include <string.h>

int verificarPalindromoRecursivo(char *palavra, int esquerda, int direita) {

    if (esquerda >= direita) {
        return 1; // É um palíndromo
    }

    if (palavra[esquerda] != palavra[direita]) {
        return 0; // Não é um palíndromo
    }

    return verificarPalindromoRecursivo(palavra, esquerda + 1, direita - 1);
}

void verificarPalindromo(char *palavra) {
    int tamanho = strlen(palavra);

    if (verificarPalindromoRecursivo(palavra, 0, tamanho - 1)) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }
}

int main() {
    char palavra[1000]; 
    int continuar = 1;

    while (continuar) {
        fgets(palavra, sizeof(palavra), stdin);

        palavra[strcspn(palavra, "\n")] = '\0';


        if (strcmp(palavra, "FIM") == 0) {
            continuar = 0;
        } else {
            verificarPalindromo(palavra);
        }
    }

    return 0;
}


    