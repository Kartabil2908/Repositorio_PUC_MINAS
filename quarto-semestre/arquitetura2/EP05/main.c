#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t inicio, fim;
    float Tempo, media = 0;
    register int k;
    register int i = 3, j = 1;

    for (k = 1; k <= 10; k++) {
        inicio = clock();
        for (register int c = 0; c < 10000000; c++) {
            i = i * 3;
        }
        fim = clock();
        Tempo = (fim - inicio) * 1000 / CLOCKS_PER_SEC;
        printf("\nTempo: %g ms.", Tempo);
        media += Tempo;
    }

    printf("\nTempo medio gasto: %g ms.\n", media / 10);
    return 0;
}
