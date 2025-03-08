#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo;
    int n;

    arquivo = fopen("valores.txt", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        char valorStr[20];
        fgets(valorStr, 20, stdin);

        // Substitui vírgula por ponto
        for (int j = 0; valorStr[j] != '\0'; j++) {
            if (valorStr[j] == ',') {
                valorStr[j] = '.';
            }
        }

        double valor = atof(valorStr); 
        fwrite(&valor, sizeof(double), 1, arquivo); 
    }

    fclose(arquivo);

    arquivo = fopen("valores.txt", "rb");

    // Move o ponteiro para o final do arquivo
    fseek(arquivo, 0, SEEK_END);
    long posicao = ftell(arquivo);

    // Leitura do arquivo de trás para frente
    for (int i = 0; i < n; i++) {
        posicao -= sizeof(double);
        fseek(arquivo, posicao, SEEK_SET);

        double valor;
        fread(&valor, sizeof(double), 1, arquivo);

        // Exibe os valores sem zeros desnecessários à direita
        if (valor == (int)valor) {
            printf("%.0f\n", valor);  // Exibe como inteiro
        } else {
            
            printf("%.15g\n", valor); // Usa %.15g para remover zeros à direita
        }
    }

    fclose(arquivo);

    return 0;
}
