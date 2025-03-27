#include <stdio.h>
#include <string.h>

void combinar(char *palavra1, char *palavra2, char *resultado)
{
    int i = 0, j = 0, controle = 0;
    int len1 = strlen(palavra1);
    int len2 = strlen(palavra2);

    while(i < len1 && j < len2)
    {
        resultado[controle++] = palavra1[i++];
        resultado[controle++] = palavra2[j++];
    
    }

    while(i < len1)
    {
        resultado[controle++] = palavra1[i++];
    }

    while(j < len2)
    {
        resultado[controle++] = palavra2[j++];

    }

}


int main()
{
    char palavra1[50];
    char palavra2[50];
    char resultado[100];





    // Continuar lendo enquanto não encontrar o final da entrada
    while (scanf("%s" "%s", palavra1, palavra2) == 2)
    {
       combinar(palavra1, palavra2, resultado);

       printf("palavra 1: %s\n", palavra1);
       printf("palavra 2: %s\n", palavra2);
       printf("String combinada: %s\n", resultado);

    
        
    }

    return 0;

    
}
