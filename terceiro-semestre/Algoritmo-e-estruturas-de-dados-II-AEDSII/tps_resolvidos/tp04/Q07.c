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
#define TAMANHO_HASH 21 // Tamanho da tabela hash

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

// Estrutura de nó para lista simples
typedef struct No
{
    char nome[50];   // Nome do Pokémon
    struct No *prox; // Ponteiro para o próximo nó
} No;

// Estrutura da tabela hash
typedef struct TabelaHash
{
    No *tabela[TAMANHO_HASH]; // Vetor de listas com TAMANHO_HASH entradas
    int comparacoes;          // Contador de comparações
    int movimentacoes;        // Contador de movimentações
} TabelaHash;

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

// protótipos de funções Tabela Hash:

int calcular_indice_hash(const char *nome);
void inicializar_tabela_hash(TabelaHash *hash);
void inserir_na_tabela(TabelaHash *hash, const char *nome);
No *buscar_na_tabela(TabelaHash *hash, const char *nome);

void inserir_na_tabela_por_id(TabelaHash *hash, const char *id, Pokemon *pokemons, int numPokemons);

// MAIN ----------------------------------------------------------------------------------------------------------

int main()
{
    char entrada[200];     
    Pokemon pokemons[802]; 
    int numPokemons = 802; 
    char nomeBusca[50];

    preencher_array_pokemons(pokemons);

    // Inicializa a tabela hash
    TabelaHash hash;
    inicializar_tabela_hash(&hash);



    scanf("%s", entrada);

    
    while (strcmp(entrada, "FIM") != 0)
    {
        inserir_na_tabela_por_id(&hash, entrada, pokemons, numPokemons);
        scanf("%s", entrada);
    }


    int controle = 1;

    while (controle == 1)
    {
        scanf("%s", nomeBusca);
        if (strcmp(nomeBusca, "FIM") == 0)
        {
            controle = 0;
        }
        else
        {
            No *encontrado = buscar_na_tabela(&hash, nomeBusca);

            if (encontrado != NULL && strcmp(encontrado->nome, nomeBusca) == 0)
            {
                int indice = calcular_indice_hash(nomeBusca);
                printf("=> %s: (Posicao: %d) SIM\n", nomeBusca, indice);
            }
            else
            {
                printf("=> %s: NAO\n", nomeBusca);
            }
        }
    }

    return 0;
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

// METODOS TABELA HASH ----------------------------------------------------------------------------------------------------------

int calcular_indice_hash(const char *nome)
{
    int soma_ascii = 0;

    for (int i = 0; i < strlen(nome); i++)
    {
        soma_ascii += (int)nome[i];
    }

    return soma_ascii % TAMANHO_HASH;
}

void inicializar_tabela_hash(TabelaHash *hash)
{
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        hash->tabela[i] = NULL; // Inicializa todas as posições com NULL
    }
    hash->comparacoes = 0;
    hash->movimentacoes = 0;
}

void inserir_na_tabela(TabelaHash *hash, const char *nome)
{
    int indice = calcular_indice_hash(nome);

    // Cria o novo nó
    No *novo_no = (No *)malloc(sizeof(No));
    strcpy(novo_no->nome, nome);
    novo_no->prox = NULL;

    hash->movimentacoes++; // Incrementa o contador de movimentações

    // Insere na lista correspondente ao índice
    if (hash->tabela[indice] == NULL)
    {
        hash->tabela[indice] = novo_no;
    }
    else
    {
        No *atual = hash->tabela[indice];

        while (atual->prox != NULL)
        {
            hash->comparacoes++; // Incrementa o contador de comparações
            atual = atual->prox;
        }

        atual->prox = novo_no;
        hash->movimentacoes++; // Incrementa as movimentações
    }
}

No *buscar_na_tabela(TabelaHash *hash, const char *nome)
{
    int indice = calcular_indice_hash(nome);
    No *atual = hash->tabela[indice];

    while (atual != NULL)
    {
        hash->comparacoes++; // Incrementa o contador de comparações

        if (strcmp(atual->nome, nome) == 0)
        {
            return atual; // Retorna o nó encontrado
        }

        atual = atual->prox;
    }

    return NULL; // Retorna NULL se o nome não for encontrado
}




void inserir_na_tabela_por_id(TabelaHash *hash, const char *id, Pokemon *pokemons, int numPokemons)
{
    // Procura o Pokémon no array pelo ID
    for (int i = 0; i < numPokemons; i++)
    {
        if (strcmp(pokemons[i].id, id) == 0)
        {
            // Se o ID for encontrado, insere o nome correspondente na tabela
            inserir_na_tabela(hash, pokemons[i].nomePokemon);
            return;
        }
    }

    printf("ID %s não encontrado no array de Pokémons.\n", id);
}
