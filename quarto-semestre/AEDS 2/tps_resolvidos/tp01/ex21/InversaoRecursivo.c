#include <stdio.h>
#include <string.h>


void swap(char *entrada, int esquerda, int direita)
{
    char temp = entrada[esquerda];
    entrada[esquerda] = entrada[direita];
    entrada[direita] = temp;
}

void inverterStringRecursivo(char *entrada, int esquerda, int direita) {

    // Se chega no fim retorna
    if (esquerda >= direita) {
        return;
    }

    swap(entrada, esquerda, direita);

    inverterStringRecursivo(entrada, esquerda + 1, direita - 1);
}

void inverterString(char *entrada) {
    int tamanho = strlen(entrada);
    inverterStringRecursivo(entrada, 0, tamanho - 1);
}

int main() {
    char entrada[100];
    
    fgets(entrada, sizeof(entrada), stdin);

    // essa função substitui o \n da entrada por 0
    entrada[strcspn(entrada, "\n")] = 0;
    
    while (strcmp(entrada, "FIM") != 0)
    {
        inverterString(entrada);
        printf("%s\n", entrada);
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0;
        
    }
    
   
        
    
    
    return 0;
}
