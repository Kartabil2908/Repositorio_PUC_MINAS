#include <stdio.h>

void criarCompetidores(int competidores[], int n)
{

    for(int i = 0; i < n; i++)
    {
        
        scanf("%d", &competidores[i]);

    }
       
}

void criarChegada(int chegada[], int n)
{

    for(int i = 0; i < n; i++)
    {
        
        scanf("%d", &chegada[i]);

    }
       
}


void printarVetor(int competidores[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d", competidores[i]);
    }
}


int contarUltrapassagem(int largada[],int chegada[], int n)
{
    int ultrapassagem = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(largada[i] == chegada[j])
            {
                if(i > j) // ultrapassou
                {
                    ultrapassagem = ultrapassagem + (i - j);
                }

            }
        }
    }


    return ultrapassagem;
}

int main()
{   
    int resposta = 0;
    int n;
    scanf("%d",&n);
    getchar();

    int competidores[n];
    int chegada[n];

    criarCompetidores(competidores, n);
    criarChegada(chegada, n);

    resposta = contarUltrapassagem(competidores, chegada, n);
    
    printf("%d",resposta);


    return 0;
}