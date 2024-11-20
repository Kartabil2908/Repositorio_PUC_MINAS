#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define ARQUIVO_CAMINHO "tmp/pokemon.csv"
#define MAX_POKEMONS 801
#define MAX_BUFFER 1000
#define MAX_LISTA 50
#define MAX_TAMANHO_HABILIDADE 50
#define verdade 1
#define falso 0
#define MAX_NOMES 200
#define MAX_IDS 200
#define K 10

// Essa lista não é para a lista de pokemons, mas sim  para a lista de habilidades e tipos;

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


// esta é a lista sequencial pokemon
typedef struct {
    Pokemon array[MAX_POKEMONS];
    int n;
} ListaSequencial;

typedef struct {
    Pokemon array[MAX_POKEMONS];
    int topo;
} Pilha;

typedef struct {
    Pokemon array[MAX_POKEMONS + 1];
    int primeiro;
    int ultimo; 
} FilaCircular;


// Protótipos da lista sequencial Pokemon
void inicializarLista(ListaSequencial* lista);
void inserirInicio(ListaSequencial* lista, Pokemon pokemon);
void inserir(ListaSequencial* lista, Pokemon pokemon, int pos);
void inserirFim(ListaSequencial* lista, Pokemon pokemon);
Pokemon removerInicio(ListaSequencial* lista);
Pokemon remover(ListaSequencial* lista, int pos);
Pokemon removerFim(ListaSequencial* lista);
void mostrar(ListaSequencial* lista);
Pokemon buscarPokemonPorId(const char* id, Pokemon* pokemons, int numPokemons);

// protótipos da pilha sequencial pokemon
void inicializarPilha(Pilha* pilha);
void empilhar(Pilha* pilha, Pokemon pokemon);
Pokemon desempilhar(Pilha* pilha);
void mostrarPilha(Pilha* pilha);

// protótipos da fila circular pokemon

void inserirFilaCircular(FilaCircular* fila, Pokemon pokemon);
Pokemon removerFilaCircular(FilaCircular* fila);
void inicializarFilaCircular(FilaCircular* fila);
void mostrarFilaCircular(FilaCircular* fila);




// MAIN ----------------------------------------------------------------------------------------------------------

int main() { //Q03
    Pokemon basePokemons[MAX_POKEMONS];
    FilaCircular fila;
    inicializarFilaCircular(&fila);
    char entrada[10];
    int numPokemons = 801;

    preencher_array_pokemons(basePokemons);

    // Leitura da primeira parte (fila Circular)
    while (1) {
        scanf("%s", entrada);
        if (strcmp(entrada, "FIM") == 0) break;
        
        Pokemon p = buscarPokemonPorId(entrada, basePokemons, numPokemons);
        inserirFilaCircular(&fila, p);
    }

    // Leitura do número de operações
    int numOps;
    scanf("%d", &numOps);

    // Processamento das operações
    for (int i = 0; i < numOps; i++) {
        char cmd;
        scanf(" %c", &cmd);

        if (cmd == 'I') {
            char id[10];
            scanf("%s", id);
            Pokemon p = buscarPokemonPorId(id, basePokemons, numPokemons);
            inserirFilaCircular(&fila, p);
        }
        else if (cmd == 'R') {
            Pokemon removido = removerFilaCircular(&fila);
            printf("(R) %s\n", removido.nomePokemon);
        }
    }

    // Mostrar a Fila Circular final
    mostrarFilaCircular(&fila);

    return 0;
}

// MAIN ----------------------------------------------------------------------------------------------------------



// MÉTODOS DE LISTA DE HABILIDADES ----------------------------------------------------------------------------------------------------------




char *remover_espaco(char *entrada)
{
    if (!entrada)
        return NULL;

    // Encontrar o primeiro e o último caractere não-espaço
    char *inicio = entrada;
    while (isspace((unsigned char)*inicio))
        inicio++;

    char *fim = entrada + strlen(entrada) - 1;
    while (fim > inicio && isspace((unsigned char)*fim))
        fim--;

    // Calcular o novo tamanho e alocar memória
    size_t tamanho = fim - inicio + 1;
    char *saida = (char *)malloc(tamanho + 1);
    if (saida)
    {
        strncpy(saida, inicio, tamanho);
        saida[tamanho] = '\0'; // Adiciona o terminador nulo
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

    // Remover os caracteres de formatação
    substituir_caracter(string_habilidades, '[', ' ');  // Remove '['
    substituir_caracter(string_habilidades, ']', ' ');  // Remove ']'
    substituir_caracter(string_habilidades, '\'', ' '); // Remove '\''

    // Debug: mostrar a string antes da conversão
    // printf("String antes da conversão: '%s'\n", string_habilidades);

    // Tokeniza a string por vírgulas
    char *token = strtok(string_habilidades, ",");
    while (token != NULL && lista.contagem < MAX_LISTA)
    {
        // Remove espaços em branco do início e do final
        char *habilidade = trim(token);
        if (strlen(habilidade) > 0)
        {
            // Debug: exibir a habilidade antes de adicionar
            // printf("Adicionando habilidade: '%s'\n", habilidade);
            // Copie a habilidade para a lista sem truncar
            strncpy(lista.itens[lista.contagem], habilidade, sizeof(lista.itens[lista.contagem]) - 1);
            lista.itens[lista.contagem][sizeof(lista.itens[lista.contagem]) - 1] = '\0'; // Garante que a string esteja terminada
            lista.contagem++;                                                            // Incrementa a contagem após adicionar a habilidade
        }
        // Pega o próximo token
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

        // printf("Adicionando habilidade: '%s'\n", elemento); // Print para ver a string que está sendo adicionada
        // Usar strncpy para evitar buffer overflow
        strncpy(lista->itens[lista->contagem], elemento, MAX_TAMANHO_HABILIDADE - 1);
        lista->itens[lista->contagem][MAX_TAMANHO_HABILIDADE - 1] = '\0'; // Garantir terminação nula
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

// LEITURA DO CSV
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

        // Tokeniza a linha baseada em aspas
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

        // Tokeniza a linha baseada em vírgulas
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

            // Converte tipos
            Lista tipos_atual = converter_para_lista(partes[4]);
            if (partes[5] && strlen(partes[5]) > 0)
            {
                adicionar_elemento(&tipos_atual, partes[5]);
            }
            *pokemon_atual.tipos_elementos = tipos_atual;

            // Inicializa habilidades_elementos
            pokemon_atual.habilidades_elementos = (Lista *)malloc(sizeof(Lista));
            if (!pokemon_atual.habilidades_elementos)
            {
                printf("Erro: Falha ao alocar memória para habilidades\n");
                exit(1);
            }

            // printf("String antes da conversão: '%s'\n", inicio_partes[1]);

            // Converte e atribui habilidades
            Lista habilidades_atual = converter_para_lista(inicio_partes[1]);
            *pokemon_atual.habilidades_elementos = habilidades_atual;

            // Debug: Exibir habilidades
            // printf("Elementos da lista de habilidades:\n");
            // exibir_elementos(pokemon_atual.habilidades_elementos);
            // printf("\n");

            // Atribuindo peso, altura e outros atributos
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

// PRINT DO POKEMON
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

// MÉTODOS DE LISTA SEQUENCIAL POKEMON ----------------------------------------------------------------------------------------------------------

// Inicializar lista
void inicializarLista(ListaSequencial* lista) {
    lista->n = 0;
}

// Inserir no início
void inserirInicio(ListaSequencial* lista, Pokemon pokemon) {
    if (lista->n >= MAX_POKEMONS) {
        printf("Erro: Lista cheia\n");
        return;
    }
    
    for (int i = lista->n; i > 0; i--) {
        lista->array[i] = lista->array[i-1];
    }
    
    lista->array[0] = pokemon;
    lista->n++;
}

// Inserir na posição
void inserir(ListaSequencial* lista, Pokemon pokemon, int pos) {
    if (lista->n >= MAX_POKEMONS) {
        printf("Erro: Lista cheia\n");
        return;
    }
    
    if (pos < 0 || pos > lista->n) {
        printf("Erro: Posição inválida\n");
        return;
    }
    
    for (int i = lista->n; i > pos; i--) {
        lista->array[i] = lista->array[i-1];
    }
    
    lista->array[pos] = pokemon;
    lista->n++;
}

// Inserir no fim
void inserirFim(ListaSequencial* lista, Pokemon pokemon) {
    if (lista->n >= MAX_POKEMONS) {
        printf("Erro: Lista cheia\n");
        return;
    }
    
    lista->array[lista->n] = pokemon;
    lista->n++;
}

// Remover do início
Pokemon removerInicio(ListaSequencial* lista) {
    Pokemon removido = lista->array[0];
    
    for (int i = 0; i < lista->n - 1; i++) {
        lista->array[i] = lista->array[i+1];
    }
    
    lista->n--;
    return removido;
}

// Remover da posição
Pokemon remover(ListaSequencial* lista, int pos) {
    Pokemon removido = lista->array[pos];
    
    for (int i = pos; i < lista->n - 1; i++) {
        lista->array[i] = lista->array[i+1];
    }
    
    lista->n--;
    return removido;
}

// Remover do fim
Pokemon removerFim(ListaSequencial* lista) {
    return lista->array[--lista->n];
}



// Mostrar lista
void mostrar(ListaSequencial* lista) {
    for (int i = 0; i < lista->n; i++) {
        printf("[%d]", i);
        exibir_pokemon(lista->array[i]);
    }
}

// Buscar Pokemon por ID
Pokemon buscarPokemonPorId(const char* id, Pokemon* pokemons, int numPokemons) {
    for (int i = 0; i < numPokemons; i++) {
        if (strcmp(pokemons[i].id, id) == 0) {
            return pokemons[i];
        }
    }
    Pokemon vazio = {0};
    return vazio;
}

// MÉTODOS DE LISTA SEQUENCIAL POKEMON ----------------------------------------------------------------------------------------------------------


// MÉTODOS DE PILHA SEQUENCIAL POKEMON ----------------------------------------------------------------------------------------------------------

void inicializarFilaCircular(FilaCircular* fila)
{
    fila->primeiro = fila->ultimo = 0;
}

void empilhar(Pilha* pilha, Pokemon pokemon) {
    if (pilha->topo >= MAX_POKEMONS) {
        printf("Erro: Pilha cheia\n");
        return;
    }
    pilha->array[pilha->topo] = pokemon;
    pilha->topo++;
}

Pokemon desempilhar(Pilha* pilha) {
    pilha->topo--;
    return pilha->array[pilha->topo];
}

void mostrarPilha(Pilha* pilha) {
    for (int i = 0; i < pilha->topo; i++) {
        printf("[%d] ", i);
        exibir_pokemon(pilha->array[i]);
    }
}


// MÉTODOS DE PILHA SEQUENCIAL POKEMON ----------------------------------------------------------------------------------------------------------

// MÉTODOS DE FILA CIRCULAR POKEMON ----------------------------------------------------------------------------------------------------------

int CalcularMediaInserir(FilaCircular* fila, int media)
{
    int mediaCaptureRate = 0;

      mediaCaptureRate = (fila->array->taxaCaptura[fila->ultimo] + media) / (fila->ultimo - fila->primeiro);

    return mediaCaptureRate;

}


Pokemon removerFilaCircular(FilaCircular* fila) {

   Pokemon pokemonRemovido = fila->array[fila->primeiro];
   fila->primeiro = (fila->primeiro + 1) % 6;
   return pokemonRemovido;
}



void inserirFilaCircular(FilaCircular* fila,Pokemon pokemon)
{

    if((fila->ultimo + 1) % MAX_POKEMONS == fila->primeiro) 
    {
       Pokemon pokemonRemo = removerFilaCircular(fila);
    }

    fila->array[fila->ultimo] = pokemon;
    fila->ultimo = (fila->ultimo + 1) % 6;

}

void mostrarFilaCircular (FilaCircular* fila){
   int i;
   for(i = fila->primeiro; i != fila->ultimo; i = ((i + 1) % 6)) {
      printf("[%d] ", i);
    exibir_pokemon(fila->array[i]);
   }
}
