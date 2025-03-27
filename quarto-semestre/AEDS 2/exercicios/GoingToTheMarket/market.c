#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fruta
{
    char *nome;
    float preco;
} Fruta;

// Função para criar uma fruta
Fruta criarFruta()
{
    Fruta fruta;

    fruta.nome = (char *)malloc(50 * sizeof(char));
    if (fruta.nome == NULL)
    {
        printf("Erro ao alocar memória para o nome da fruta.\n");
        exit(1);
    }

    // Lê o nome e o preço da fruta
    scanf("%s %f", fruta.nome, &fruta.preco);

    return fruta;
}

// Função para criar um array de frutas
Fruta *criarListaDeFrutas(int quantidade)
{
    Fruta *frutas = (Fruta *)malloc(quantidade * sizeof(Fruta));
    if (frutas == NULL)
    {
        printf("Erro ao alocar memória para a lista de frutas.\n");
        exit(1);
    }

    // Preenchendo o array de frutas
    for (int i = 0; i < quantidade; i++)
    {
        frutas[i] = criarFruta();
    }

    return frutas;
}

// Função para exibir a lista de frutas
void exibirListaDeFrutas(Fruta *frutas, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        printf("%s %.2f\n", frutas[i].nome, frutas[i].preco);
    }
}

// Função para liberar a memória alocada
void liberarListaDeFrutas(Fruta *frutas, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        free(frutas[i].nome);
    }
    free(frutas);

}


float calcularDinheiro(Fruta *frutasMercado, int frutasNaFeira, Fruta *listaCompras, int frutasComprar)
{
    float dinheiroNecessario = 0;

    for (int i = 0; i < frutasComprar; i++)
    {
        // Para cada fruta na lista de compras
        int quantidadeCompras = (int) listaCompras[i].preco;  // Aqui a quantidade na verdade chamamos de preco
        
        for (int j = 0; j < frutasNaFeira; j++)
        {
            // Se o nome da fruta na feira for igual ao da lista de compras, somamos o preço
            if (strcmp(frutasMercado[j].nome, listaCompras[i].nome) == 0)
            {
                // Soma o preço, multiplicado pela quantidade
                dinheiroNecessario += frutasMercado[j].preco * quantidadeCompras;
                break;  // Achou a fruta, então sai do loop
            }
        }
    }

    return dinheiroNecessario;
}



int main()
{
    int casosTeste, frutasNaFeira, frutasComprar;
    float dinheiroNecessario;

    scanf("%d", &casosTeste);

    for (int i = 0; i < casosTeste; i++)
    {
        scanf("%d", &frutasNaFeira); // lendo o num de frutas na feira

        // Criando a lista de frutas dinamicamente
        Fruta *frutasMercado = criarListaDeFrutas(frutasNaFeira);

        scanf("%d", &frutasComprar); // lendo o num de frutas na lista de compras

        Fruta *listaCompras = criarListaDeFrutas(frutasComprar); // criando a lista de compras;

        dinheiroNecessario = calcularDinheiro(frutasMercado,frutasNaFeira, listaCompras, frutasComprar);

        printf("R$ %.2f\n" , dinheiroNecessario);
        
    }

    return 0;
}
