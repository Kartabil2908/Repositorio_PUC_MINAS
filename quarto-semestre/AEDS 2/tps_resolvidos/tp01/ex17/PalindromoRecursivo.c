#include <stdio.h>
#include <string.h>

int verificarPalindromoRecursivo(char frase[], int inicio, int fim) {

    // se o início >= fim, a palavra == palíndromo
    if (inicio >= fim) {
        return 1;
    }

    // não é um palíndromo
    if (frase[inicio] != frase[fim]) {
        return 0;
    }


    return verificarPalindromoRecursivo(frase, inicio + 1, fim - 1);
}

void verificarPalindromo(char frase[]) {

    int tamanho = strlen(frase);
    int resultado = verificarPalindromoRecursivo(frase, 0, tamanho - 1);

    if (resultado) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }
}

int main() {
    char frase[100];

    int condicao = 1;
    while (condicao == 1) {

        fgets(frase, sizeof(frase), stdin);
        frase[strcspn(frase, "\n")] = 0;

        if (strcmp(frase, "FIM") == 0) {
            condicao = 0;
        }

        verificarPalindromo(frase);
    }

    return 0;
}
