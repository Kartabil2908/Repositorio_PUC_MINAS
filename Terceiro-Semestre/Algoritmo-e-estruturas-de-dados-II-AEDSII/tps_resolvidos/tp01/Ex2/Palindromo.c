#include <stdio.h>
#include <string.h>

void verificarPalindromo(char *palavra) {
    int i, j;
    int tamanho = strlen(palavra);
    int ehPalindromo = 1; 

  
    for (i = 0, j = tamanho - 1; i < j; i++, j--) {
        if (palavra[i] != palavra[j]) {
            ehPalindromo = 0; 
            break;
        }
    }

    if (ehPalindromo) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }
}

int main() {
    char palavra[1000]; 

    while (1) {
        fgets(palavra, sizeof(palavra), stdin);

      
        palavra[strcspn(palavra, "\n")] = '\0';

        if (strcmp(palavra, "FIM") == 0) {
            break;
        }

        verificarPalindromo(palavra);
    }

    return 0;
}


