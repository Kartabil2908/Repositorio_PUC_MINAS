#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int somarDigitos(int numero)
{
    if (numero == 0) {
        return 0;
    }

    int soma = 0;

    soma = numero % 10;

    return soma + somarDigitos(numero/10);
}

int main()
{
    int numero = 0;
    char entrada[100];
    int soma = 0;

    fgets(entrada,100, stdin);

    entrada[strcspn(entrada,"\n")] = 0;

    while (strcmp(entrada, "FIM") != 0)
    {
        numero = atoi(entrada);
        
        soma = somarDigitos(numero);
        printf("%d\n", soma);
        
        fgets(entrada,100, stdin);
        entrada[strcspn(entrada,"\n")] = 0;
    }

    return 0;
}