#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define ARQUIVO_CAMINHO "/tmp/pokemon.csv"
#define MAX_POKEMONS 801
#define MAX_BUFFER 1000
#define MAX_LISTA 50
#define MAX_TAMANHO_HABILIDADE 50
#define verdade 1
#define falso 0
#define MAX_NOMES 200
#define MAX_IDS 200
#define K 10

typedef struct Lista
{
    char itens[MAX_LISTA][50];
    int contagem;
} Lista;

typedef struct Pokemon
{
    char id[4];
    char geracao_dados[5];
    char nomePokemon[50];
    char descricaoPokemon[50];
    Lista *tipos_elementos;
    Lista *habilidades_elementos;
    char peso[200];
    char altura[200];
    char taxaCaptura[200];
    bool e_lendario;
    char dataCaptura[11];
} Pokemon;

typedef struct No
{
    Pokemon pokemon;
    struct No *esq, *dir;
    int altura;
} No;

typedef struct Arvore
{
    No *raiz;
    int numComparacoes;
    int numMovimentacoes;
} Arvore;

// protótipos de funções:

void criarLog(double tempoExecucao, int comparacoes, int movimentacoes, const char *arquivo);
char *trim(char *str);
char *extrair_sub(char *, size_t, size_t);
char *remover_espaco(char *);
void substituir_caracter(char *, char, char);
Lista converter_para_lista(char[]);
void adicionar_elemento(Lista *lista, const char *elemento);
void exibir_elementos(Lista *);
Pokemon inicializar_pokemon();
char *encontrar_separador(char **, const char *);
void preencher_array_pokemons(Pokemon[]);
void exibir_pokemon(Pokemon pokemon);

Pokemon buscarPokemonPorId(const char *id, Pokemon *pokemons, int numPokemons);
void inserirPokemonArvore(Arvore *arvore, Pokemon pokemon);
bool buscarPokemonArvore(Arvore *arvore, const char *nome);
void inicializarArvore(Arvore *arvore);

// Funções AVL
int altura(No *n);
int max(int a, int b);
No *rotacaoDireita(No *y);
No *rotacaoEsquerda(No *x);
int getBalanceamento(No *n);
No *balancearArvore(No *n, Pokemon pokemon);
No *inserirNoAVL(No *no, Pokemon pokemon, Arvore *arvore);

// MAIN ----------------------------------------------------------------------------------------------------------

int main()
{

    char entrada[200];
    char nome[200];
    int resposta;
    int qtddPokemons = 0;
    int i = 0;
    int j = 0;

    Arvore arvore;
    inicializarArvore(&arvore);

    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0)
    {
        for (i = 0; i < 802; i++)
        {
            resposta = strcmp(pokemons[i].id, entrada);

            if (resposta == 0)
            {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

    for (i = 0; i < qtddPokemons; i++)
    {
        pokemonsEntrada[i] = temporario[i];
    }

    free(temporario);

    // Medir o tempo de execução
    clock_t inicio = clock();

    for (i = 0; i < qtddPokemons; i++)
    {
        arvore.raiz = inserirNoAVL(arvore.raiz, pokemonsEntrada[i], &arvore);
    }

    while (1)
    {
        scanf("%s", nome);
        if (strcmp(nome, "FIM") == 0)
            break;

        bool encontrado = buscarPokemonArvore(&arvore, nome);
        if (encontrado)
        {
            printf("SIM\n");
        }
        else
        {
            printf("NAO\n");
        }
    }

    clock_t fim = clock();
    double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    criarLog(tempoExecucao, arvore.numComparacoes, arvore.numMovimentacoes, "1449304_avl.txt");
}
// MAIN ----------------------------------------------------------------------------------------------------------

// MÉTODOS DE LISTA DE HABILIDADES ----------------------------------------------------------------------------------------------------------

char *remover_espaco(char *entrada)
{
    if (!entrada)
        return NULL;

    char *inicio = entrada;
    while (isspace((unsigned char)*inicio))
        inicio++;

    char *fim = entrada + strlen(entrada) - 1;
    while (fim > inicio && isspace((unsigned char)*fim))
        fim--;

    size_t tamanho = fim - inicio + 1;
    char *saida = (char *)malloc(tamanho + 1);
    if (saida)
    {
        strncpy(saida, inicio, tamanho);
        saida[tamanho] = '\0';
    }
    return saida;
}

char *extrair_sub(char *entrada, size_t inicio, size_t fim)
{
    char *subcampo = NULL;
    size_t tamanho_entrada = strlen(entrada);
    if (inicio < tamanho_entrada && fim < tamanho_entrada && inicio <= fim)
    {
        size_t comprimento = fim - inicio + 1;
        subcampo = (char *)malloc((comprimento + 1) * sizeof(char));
        if (subcampo)
        {
            size_t j = 0;
            for (size_t i = inicio; i <= fim; i++)
            {
                *(subcampo + j) = *(entrada + i);
                j++;
            }
            *(subcampo + j) = '\0';
        }
    }
    return subcampo;
}

void substituir_caracter(char *entrada, char buscar_caracter, char substituir_caracter)
{
    char *ptr = strchr(entrada, buscar_caracter);
    while (ptr != NULL)
    {
        *ptr = substituir_caracter;
        ptr = strchr(ptr + 1, buscar_caracter);
    }
}

Lista converter_para_lista(char *string_habilidades)
{
    Lista lista;
    lista.contagem = 0;

    substituir_caracter(string_habilidades, '[', ' ');
    substituir_caracter(string_habilidades, ']', ' ');
    substituir_caracter(string_habilidades, '\'', ' ');

    char *token = strtok(string_habilidades, ",");
    while (token != NULL && lista.contagem < MAX_LISTA)
    {
        char *habilidade = trim(token);
        if (strlen(habilidade) > 0)
        {
            strncpy(lista.itens[lista.contagem], habilidade, sizeof(lista.itens[lista.contagem]) - 1);
            lista.itens[lista.contagem][sizeof(lista.itens[lista.contagem]) - 1] = '\0';
            lista.contagem++;
        }
        token = strtok(NULL, ",");
    }

    return lista;
}

char *trim(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';

    return str;
}

void adicionar_elemento(Lista *lista, const char *elemento)
{
    if (lista->contagem < MAX_LISTA)
    {
        strncpy(lista->itens[lista->contagem], elemento, MAX_TAMANHO_HABILIDADE - 1);
        lista->itens[lista->contagem][MAX_TAMANHO_HABILIDADE - 1] = '\0';
        lista->contagem++;
    }
    else
    {
        printf("Lista cheia. Não foi possível adicionar o elemento: '%s'\n", elemento);
    }
}

void exibir_elementos(Lista *lista)
{
    printf("[", lista->contagem);
    for (int i = 0; i < lista->contagem; i++)
    {
        printf("'%s'", lista->itens[i]);
        if (i + 1 < lista->contagem)
        {
            printf(", ");
        }
    }
    printf("]");
}

// MÉTODOS DE LISTA DE HABILIDADES ---------------------------------------------------------------------------------------------

// MÉTODOS DO POKEMON ----------------------------------------------------------------------------------------------------------

Pokemon inicializar_pokemon()
{
    Pokemon pkm;
    strcpy(pkm.id, "");
    strcpy(pkm.geracao_dados, "");
    strcpy(pkm.nomePokemon, "");
    strcpy(pkm.descricaoPokemon, "");
    pkm.tipos_elementos = (Lista *)malloc(sizeof(Lista));
    pkm.tipos_elementos->contagem = 0;
    pkm.habilidades_elementos = (Lista *)malloc(sizeof(Lista));
    pkm.habilidades_elementos->contagem = 0;
    strcpy(pkm.peso, "");
    strcpy(pkm.altura, "");
    strcpy(pkm.taxaCaptura, "");
    pkm.e_lendario = falso;
    strcpy(pkm.dataCaptura, "");
    return pkm;
}

char *encontrar_separador(char **strings, const char *delimitador)
{
    char *inicio = *strings;
    char *fim;

    if (inicio == NULL)
    {
        return NULL;
    }

    fim = strpbrk(inicio, delimitador);
    if (fim)
    {
        *fim = '\0';
        *strings = fim + 1;
    }
    else
    {
        *strings = NULL;
    }

    return inicio;
}

void preencher_array_pokemons(Pokemon pokemon_array[])
{
    FILE *arquivo = fopen(ARQUIVO_CAMINHO, "r");
    if (!arquivo)
    {
        printf("Erro: Arquivo não encontrado\n");
        exit(1);
    }

    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, arquivo);

    int i = 0;
    while (fgets(buffer, MAX_BUFFER, arquivo))
    {
        char *inicio_partes[3] = {NULL, NULL, NULL};
        int conta_partes_inicial = 0;

        char *parte = strtok(buffer, "\"");
        while (parte && conta_partes_inicial < 3)
        {
            inicio_partes[conta_partes_inicial++] = parte;
            parte = strtok(NULL, "\"");
        }

        char nova_linha[MAX_BUFFER];
        if (conta_partes_inicial > 2)
        {
            snprintf(nova_linha, MAX_BUFFER, "%s%s", inicio_partes[0], inicio_partes[2]);
        }
        else
        {
            strncpy(nova_linha, buffer, MAX_BUFFER);
        }

        char *partes[12] = {NULL};
        int conta_partes = 0;
        char *temporario = nova_linha;

        while ((parte = encontrar_separador(&temporario, ",")) != NULL && conta_partes < 12)
        {
            partes[conta_partes++] = parte;
        }

        if (conta_partes >= 10)
        {
            Pokemon pokemon_atual = inicializar_pokemon();
            strcpy(pokemon_atual.id, partes[0]);
            strcpy(pokemon_atual.geracao_dados, partes[1]);
            strcpy(pokemon_atual.nomePokemon, partes[2]);
            strcpy(pokemon_atual.descricaoPokemon, partes[3]);

            Lista tipos_atual = converter_para_lista(partes[4]);
            if (partes[5] && strlen(partes[5]) > 0)
            {
                adicionar_elemento(&tipos_atual, partes[5]);
            }
            *pokemon_atual.tipos_elementos = tipos_atual;

            pokemon_atual.habilidades_elementos = (Lista *)malloc(sizeof(Lista));
            if (!pokemon_atual.habilidades_elementos)
            {
                printf("Erro: Falha ao alocar memória para habilidades\n");
                exit(1);
            }

            Lista habilidades_atual = converter_para_lista(inicio_partes[1]);
            *pokemon_atual.habilidades_elementos = habilidades_atual;

            if (partes[7] && strlen(partes[7]) > 0)
            {
                strcpy(pokemon_atual.peso, partes[7]);
            }
            else
            {
                strcpy(pokemon_atual.peso, "0.0");
            }

            if (partes[8] && strlen(partes[8]) > 0)
            {
                strcpy(pokemon_atual.altura, partes[8]);
            }
            else
            {
                strcpy(pokemon_atual.altura, "0.0");
            }

            strcpy(pokemon_atual.taxaCaptura, partes[9]);
            pokemon_atual.e_lendario = strcmp(partes[10], "1") == 0 ? verdade : falso;

            if (conta_partes >= 12 && strlen(partes[11]) > 0)
            {
                strcpy(pokemon_atual.dataCaptura, partes[11]);
            }

            pokemon_array[i++] = pokemon_atual;

            if (i >= MAX_POKEMONS)
            {
                break;
            }
        }
    }

    fclose(arquivo);
}

void exibir_pokemon(Pokemon pokemon)
{
    printf("[#%s -> %s: %s - ", pokemon.id, pokemon.nomePokemon, pokemon.descricaoPokemon);

    if (pokemon.tipos_elementos != NULL)
    {
        exibir_elementos(pokemon.tipos_elementos);
    }

    printf(" - ");

    if (pokemon.habilidades_elementos != NULL)
    {
        exibir_elementos(pokemon.habilidades_elementos);
    }

    printf(" - %skg - %sm - %s%% - %s - %s gen]",
           pokemon.peso, pokemon.altura, pokemon.taxaCaptura,
           pokemon.e_lendario ? "true" : "false", pokemon.geracao_dados);

    char *data_sem_espaco = remover_espaco(pokemon.dataCaptura);
    if (strlen(data_sem_espaco) > 0)
    {
        printf(" - %s", data_sem_espaco);
    }
    else
    {
        printf(" - Data não disponível");
    }

    printf("\n");
}

// MÉTODOS DA ÁRVORE BINÁRIA ----------------------------------------------------------------------------------------------------------

void inicializarArvore(Arvore *arvore)
{
    arvore->raiz = NULL;
    arvore->numComparacoes = 0;
    arvore->numMovimentacoes = 0;
}

No *criarNo(Pokemon pokemon)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->pokemon = pokemon;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 1;
    return novoNo;
}

int altura(No *n)
{
    if (n == NULL)
        return 0;
    return n->altura;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

No *rotacaoDireita(No *y)
{
    No *x = y->esq;
    No *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), 
    
    (y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

No *rotacaoEsquerda(No *x)
{
    No *y = x->dir;
    No *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

int getBalanceamento(No *n)
{
    if (n == NULL)
        return 0;
    return altura(n->esq) - altura(n->dir);
}

No *balancearArvore(No *n, Pokemon pokemon)
{
    int balanceamento = getBalanceamento(n);

    if (balanceamento > 1 && strcmp(pokemon.nomePokemon, n->esq->pokemon.nomePokemon) < 0)
        return rotacaoDireita(n);

    if (balanceamento < -1 && strcmp(pokemon.nomePokemon, n->dir->pokemon.nomePokemon) > 0)
        return rotacaoEsquerda(n);

    if (balanceamento > 1 && strcmp(pokemon.nomePokemon, n->esq->pokemon.nomePokemon) > 0)
    {
        n->esq = rotacaoEsquerda(n->esq);
        return rotacaoDireita(n);
    }

    if (balanceamento < -1 && strcmp(pokemon.nomePokemon, n->dir->pokemon.nomePokemon) < 0)
    {
        n->dir = rotacaoDireita(n->dir);
        return rotacaoEsquerda(n);
    }

    return n;
}

No *inserirNoAVL(No *no, Pokemon pokemon, Arvore *arvore)
{
    if (no == NULL)
        return criarNo(pokemon);

    arvore->numComparacoes++;
    if (strcmp(pokemon.nomePokemon, no->pokemon.nomePokemon) < 0)
        no->esq = inserirNoAVL(no->esq, pokemon, arvore);
    else if (strcmp(pokemon.nomePokemon, no->pokemon.nomePokemon) > 0)
        no->dir = inserirNoAVL(no->dir, pokemon, arvore);
    else
        return no;

    no->altura = 1 + max(altura(no->esq), altura(no->dir));

    return balancearArvore(no, pokemon);
}

bool buscarPokemonArvore(Arvore *arvore, const char *nome)
{
    printf("%s\n", nome);
    printf("raiz ");
    No *atual = arvore->raiz;
    while (atual != NULL)
    {
        arvore->numComparacoes++;
        int cmp = strcmp(nome, atual->pokemon.nomePokemon);
        if (cmp == 0)
        {
            return true;
        }
        else if (cmp < 0)
        {
            printf("esq ");
            atual = atual->esq;
        }
        else
        {
            printf("dir ");
            atual = atual->dir;
        }
    }
    return false;
}

// MÉTODO PARA CRIAR O LOG ----------------------------------------------------------------------------------------------------------

void criarLog(double tempoExecucao, int comparacoes, int movimentacoes, const char *arquivo)
{
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL)
    {
        printf("Erro ao criar o arquivo de log\n");
        return;
    }
    fprintf(fp, "Tempo de Execução: %lf segundos\n", tempoExecucao);
    fprintf(fp, "Número de Comparações: %d\n", comparacoes);
    fprintf(fp, "Número de Movimentações: %d\n", movimentacoes);
    fclose(fp);
}