#include <stdio.h>
#include <string.h>

void verificarPalindromo(char frase[])
{
    int statusPalavra = 0;
    int tamanho = strlen(frase);

    for (int i = 0; i < tamanho; i++)
    {
        char letraComparada = frase[tamanho - i - 1];

        if (frase[i] == letraComparada)
        {
            statusPalavra = 1;
        }
        else
        {
            statusPalavra = 0;
            i = tamanho;
            ;
        }
    }

    if (statusPalavra == 1)
    {
        printf("SIM\n");
    }
    else
    {
        printf("NAO\n");
    }
}

int main()
{
    char frase[100];

    int condicao = 1;
    while (condicao == 1)
    {
        fgets(frase, sizeof(frase), stdin);
        frase[strcspn(frase, "\n")] = 0;

        if (strcmp(frase, "FIM") == 0)
        {
            condicao = 0;
        }

        verificarPalindromo(frase);
    }

    return 0;
}
