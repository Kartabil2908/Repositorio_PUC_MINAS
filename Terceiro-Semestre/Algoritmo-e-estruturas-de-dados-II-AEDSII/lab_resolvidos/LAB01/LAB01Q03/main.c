#include <stdio.h>
#include <string.h>

int verificarMaiuscula(char letra)
{
    return (letra >= 'A' && letra <= 'Z');
}

int verificarFim(char *palavra)
{
    return (strcmp(palavra, "FIM") == 0);
}

void lerFrase(char *frase, int tamanho)
{
    fgets(frase, tamanho, stdin);
    frase[strcspn(frase, "\n")] = '\0'; // Remove o caractere de nova linha
}

int contarLetrasMaiusculas(char *frase)
{
    int contador = 0;
    int tamanho = strlen(frase);

    for (int i = 0; i < tamanho; i++)
    {
        if (verificarMaiuscula(frase[i]))
        {
            contador++;
        }
    }

    return contador;
}

int main()
{
    char frase[200];

    do
    {
        lerFrase(frase, sizeof(frase));
        
        if (!verificarFim(frase))
        {
            int maiusculas = contarLetrasMaiusculas(frase);
            printf("%d\n", maiusculas);
        }

    } while (!verificarFim(frase));

    return 0;
}
