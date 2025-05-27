#include <stdio.h>
#include <string.h>

int economizarNumero(char* anterior, char* atual) {
    int i = 0;
    while (anterior[i] != '\0' && atual[i] != '\0' && anterior[i] == atual[i]) {
        i++;
    }
    return i;
}

int main() {
    int n;
    char telefoneAnterior[201], telefoneAtual[201];

    while (scanf("%d", &n) == 1) {
        int totalEconomizado = 0;

        // Lê o primeiro telefone
        scanf("%s", telefoneAnterior);

        for (int i = 1; i < n; i++) {
            scanf("%s", telefoneAtual);
            totalEconomizado += economizarNumero(telefoneAnterior, telefoneAtual);
            strcpy(telefoneAnterior, telefoneAtual);
        }

        printf("%d\n", totalEconomizado);
    }

    return 0;
}
