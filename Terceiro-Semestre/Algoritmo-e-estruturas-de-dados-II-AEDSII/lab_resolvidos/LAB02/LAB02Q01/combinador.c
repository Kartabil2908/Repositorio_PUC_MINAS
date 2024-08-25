#include <stdio.h>
#include <string.h>

void combinador(char *palavra1, char* palavra2)
{
    int tamanho1 = strlen(palavra1);
    int tamanho2 = strlen(palavra2);
    int i = 0, j = 0;
    char palavra3[201]; // 200 + 1 para '\0'

    // Alterna as letras das duas strings
    while (i < tamanho1 && i < tamanho2) {
        palavra3[j++] = palavra1[i];
        palavra3[j++] = palavra2[i];
        i++;
    }

    // Adiciona os caracteres restantes da palavra mais longa
    while (i < tamanho1) {
        palavra3[j++] = palavra1[i++];
    }

    while (i < tamanho2) {
        palavra3[j++] = palavra2[i++];
    }

    palavra3[j] = '\0'; // Adiciona o terminador de string

    printf("%s\n", palavra3);
}

int main()
{
    char palavra1[100];
    char palavra2[100];

    // Recebe as duas strings do usuário
    scanf("%s %s", palavra1, palavra2);

    // Chama a função combinador para combinar as strings
    combinador(palavra1, palavra2);

    return 0;
}
