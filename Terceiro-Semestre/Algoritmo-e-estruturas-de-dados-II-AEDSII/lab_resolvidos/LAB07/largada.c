#include <stdio.h>
//---------------------------------------------------------------------------------------------------//

void criarCompetidores(int competidores[], int n) // preencher a linha de largada
{

    for (int i = 0; i < n; i++)
    {

        scanf("%d", &competidores[i]);
    }
}

/*
    Operação relevante: Comparação
    Complexidade da função: Θ = n
*/

//---------------------------------------------------------------------------------------------------//

void criarChegada(int chegada[], int n) // preencher linha de chegada
{

    for (int i = 0; i < n; i++)
    {

        scanf("%d", &chegada[i]);
    }
}

/*
    Operação relevante: Comparação
    Complexidade da função: Θ = n
*/

//---------------------------------------------------------------------------------------------------//

void printarVetor(int competidores[], int n) // printa o vetor
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", competidores[i]);
    }
}

/*
    Operação relevante: Comparação
    Complexidade da função: Θ = n
*/

//---------------------------------------------------------------------------------------------------//

int contarUltrapassagem(int largada[], int chegada[], int n)
{
    int ultrapassagem = 0;

    for (int i = 0; i < n; i++) // repete n vezes
    {
        for (int j = 0; j < n; j++) // repete n­² vezes
        {
            if (largada[i] == chegada[j]) // repete n² vezes
            {
                if (i > j) // ultrapassou
                {
                    ultrapassagem = ultrapassagem + (i - j);
                }
            }
        }
    }

    return ultrapassagem;
}

/*
    Operação relevante: Comparação
    Complexidade da função: Θ = 3n² =  Θ = n²
*/

//---------------------------------------------------------------------------------------------------//



int main()
{
    int resposta = 0;
    int n;

    while (scanf("%d", &n) == 1)
    {
        int competidores[n];
        int chegada[n];

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &competidores[i]);
        }

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &chegada[i]);
        }

        resposta = contarUltrapassagem(competidores, chegada, n);

        printf("%d\n", resposta);
    }

    return 0;
}

/*
    Operação relevante: Comparação
    Complexidade da função: n + n + n + 3n² = 3n + 3n² =  Θ = n²
*/

//---------------------------------------------------------------------------------------------------//