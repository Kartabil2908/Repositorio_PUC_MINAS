/* ============================ BIBLIOTECAS E DEFINIÇÕES ============================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

/* Tamanhos máximos para strings e listas */
#define MAX_LINE 10000 // Tamanho máximo de uma linha do CSV
#define MAX_STR 300    // Tamanho máximo de uma string individual
#define MAX_ELEM 30    // Máximo de elementos em uma lista (diretores, atores e categorias)

/* ============================ ESTRUTURAS DE DADOS ============================ */

// Lista de strings (usada para diretores, elenco e categorias)
typedef struct
{
    char elementos[MAX_ELEM][MAX_STR]; // Vetor de strings
    int tamanho;                       // Número atual de elementos válidos na lista
} Lista;

// Estrutura que representa um show
typedef struct
{
    char showId[MAX_STR];    // ID
    char type[MAX_STR];      // Tipo
    char title[MAX_STR];     // Título
    Lista director;          // Lista de diretores
    Lista cast;              // Lista de atores
    char country[MAX_STR];   // País de origem
    char dateAdded[MAX_STR]; // Data em que foi adicionado ao catálogo
    int releaseYear;         // Ano de lançamento
    char rating[MAX_STR];    // Classificação indicativa
    char duration[MAX_STR];  // Duração
    Lista listedIn;          // Lista de gêneros/categorias
} Show;

long long comparacoes = 0;
long long movimentacoes = 0;

/* ============================ FUNÇÕES AUXILIARES ============================ */

// Substitui strings nulas ou vazias por "NaN"
void check_nan(char *str)
{
    if (str == NULL || strlen(str) == 0)
    {
        strcpy(str, "NaN");
    }
}

// Ordena alfabeticamente os elementos de uma lista
void ordenar_lista(Lista *lista)
{
    for (int i = 0; i < lista->tamanho - 1; i++)
    {
        for (int j = i + 1; j < lista->tamanho; j++)
        {
            if (strcmp(lista->elementos[i], lista->elementos[j]) > 0)
            {
                char temp[MAX_STR];
                strcpy(temp, lista->elementos[i]);
                strcpy(lista->elementos[i], lista->elementos[j]);
                strcpy(lista->elementos[j], temp);
            }
        }
    }
}

// Converte uma string separada por vírgulas em uma lista
Lista separar_lista(char *campo)
{
    Lista lista;
    lista.tamanho = 0;

    char *token = strtok(campo, ",");
    while (token != NULL && lista.tamanho < MAX_ELEM)
    {
        while (*token == ' ')
        {
            token++; // Remove espaços iniciais
        }

        token[strcspn(token, "\r\n")] = 0; // Remove quebras de linha

        strcpy(lista.elementos[lista.tamanho], token);
        lista.tamanho++;

        token = strtok(NULL, ",");
    }

    return lista; // Importante: a ordenação será feita fora, apenas onde for necessário
}

/* ============================ FUNÇÕES DE IMPRESSÃO ============================ */

// Imprime uma lista de forma formatada com colchetes (ex: [A, B, C])
void imprimir_lista(Lista lista)
{
    printf("[");
    for (int i = 0; i < lista.tamanho; i++)
    {
        printf("%s", lista.elementos[i]);
        if (i < lista.tamanho - 1)
        {
            printf(", ");
        }
    }
    printf("]");
}

// Imprime a lista de diretores (sem colchetes e sem ordenação)
void imprimir_diretores(Lista lista)
{
    if (lista.tamanho == 0)
    {
        printf("NaN");
    }
    else
    {
        for (int i = 0; i < lista.tamanho; i++)
        {
            printf("%s", lista.elementos[i]);
            if (i < lista.tamanho - 1)
            {
                printf(", ");
            }
        }
    }
}

// Imprime todos os campos de um Show no formato do enunciado
void imprimir_show(Show show)
{
    printf("=> ");

    if (strlen(show.showId) > 0)
    {
        printf("%s ## ", show.showId);
    }
    else
    {
        printf("NaN ## ");
    }

    if (strlen(show.title) > 0)
    {
        printf("%s ## ", show.title);
    }
    else
    {
        printf("NaN ## ");
    }

    if (strlen(show.type) > 0)
    {
        printf("%s ## ", show.type);
    }
    else
    {
        printf("NaN ## ");
    }

    imprimir_diretores(show.director); // Diretores não ordenados
    printf(" ## ");

    if (show.cast.tamanho > 0)
    {
        ordenar_lista(&show.cast); // Elenco ordenado
        imprimir_lista(show.cast);
    }
    else
    {
        printf("[NaN]");
    }
    printf(" ## ");

    if (strlen(show.country) > 0)
    {
        printf("%s ## ", show.country);
    }
    else
    {
        printf("NaN ## ");
    }

    if (strlen(show.dateAdded) > 0)
    {
        printf("%s ## ", show.dateAdded);
    }
    else
    {
        printf("NaN ## ");
    }

    if (show.releaseYear > 0)
    {
        printf("%d ## ", show.releaseYear);
    }
    else
    {
        printf("0 ## ");
    }

    if (strlen(show.rating) > 0)
    {
        printf("%s ## ", show.rating);
    }
    else
    {
        printf("NaN ## ");
    }

    if (strlen(show.duration) > 0)
    {
        printf("%s ## ", show.duration);
    }
    else
    {
        printf("NaN ## ");
    }

    if (show.listedIn.tamanho > 0)
    {
        ordenar_lista(&show.listedIn); // Categorias ordenadas
        imprimir_lista(show.listedIn);
    }
    else
    {
        printf("NaN");
    }

    printf(" ##\n");
}

/* ============================ PARSEAMENTO DE CSV ============================ */

// Converte uma linha do CSV em uma struct Show
void parse_csv_line(char *line, Show *show)
{
    char campos[12][MAX_STR] = {""}; // Armazena os campos extraídos
    int campo_idx = 0;               // Índice do campo atual
    int i = 0;                       // Índice para percorrer a linha
    bool in_aspas = false;           // Indica se está dentro de aspas
    char c;
    char buffer[MAX_STR]; // Buffer para construir cada campo
    int buf_idx = 0;      // Índice do buffer

    while ((c = line[i++]) != '\0' && campo_idx < 12)
    {
        if (c == '"')
        {
            in_aspas = !in_aspas;
        }
        else if (c == ',' && !in_aspas)
        {
            buffer[buf_idx] = '\0';
            strcpy(campos[campo_idx++], buffer);
            buf_idx = 0;
        }
        else
        {
            buffer[buf_idx++] = c;
        }
    }

    buffer[buf_idx] = '\0';
    strcpy(campos[campo_idx], buffer);

    strcpy(show->showId, campos[0]);
    strcpy(show->type, campos[1]);
    strcpy(show->title, campos[2]);

    if (strlen(campos[3]) > 0)
    {
        show->director = separar_lista(campos[3]); // NÃO ordenar diretores aqui, porque no exercício 2 eles não estão ordenados
    }
    else
    {
        show->director.tamanho = 0;
    }

    if (strlen(campos[4]) > 0)
    {
        show->cast = separar_lista(campos[4]);
    }
    else
    {
        show->cast.tamanho = 0;
    }

    strcpy(show->country, campos[5]);
    strcpy(show->dateAdded, campos[6]);

    if (strlen(campos[7]) > 0)
    {
        show->releaseYear = atoi(campos[7]);
    }
    else
    {
        show->releaseYear = 0;
    }

    strcpy(show->rating, campos[8]);
    strcpy(show->duration, campos[9]);

    if (strlen(campos[10]) > 0)
    {
        show->listedIn = separar_lista(campos[10]);
    }
    else
    {
        show->listedIn.tamanho = 0;
    }
}

/* ============================ LEITURA DO CSV ============================ */

// Lê o arquivo CSV e armazena os registros em um vetor dinâmico de Shows
int carregar_shows(const char *caminho, Show **shows)
{
    FILE *file = fopen(caminho, "r"); // Abre o arquivo para leitura
    if (!file)
    {
        perror("Erro ao abrir o arquivo CSV");
        exit(1);
    }

    char line[MAX_LINE];         // Buffer para leitura de linha
    fgets(line, MAX_LINE, file); // Ignora cabeçalho

    int capacidade = 100; // Capacidade inicial do vetor
    int count = 0;        // Quantidade de registros lidos

    *shows = (Show *)malloc(capacidade * sizeof(Show));
    if (*shows == NULL)
    {
        perror("Erro ao alocar memória inicial");
        exit(1);
    }

    while (fgets(line, MAX_LINE, file))
    {
        if (count >= capacidade)
        {
            capacidade *= 2;
            *shows = (Show *)realloc(*shows, capacidade * sizeof(Show));
            if (*shows == NULL)
            {
                perror("Erro ao realocar memória");
                exit(1);
            }
        }

        line[strcspn(line, "\n")] = 0; // Remove quebra de linha
        parse_csv_line(line, &((*shows)[count]));
        count++;
    }

    fclose(file);
    return count;
}

Show clonarShow(Show original)
{
    Show copia;

    // Copiar strings simples
    strcpy(copia.showId, original.showId);
    strcpy(copia.type, original.type);
    strcpy(copia.title, original.title);
    strcpy(copia.country, original.country);
    strcpy(copia.dateAdded, original.dateAdded);
    strcpy(copia.rating, original.rating);
    strcpy(copia.duration, original.duration);
    copia.releaseYear = original.releaseYear;

    // Copiar listas (director, cast, listedIn)
    copia.director.tamanho = original.director.tamanho;
    for (int i = 0; i < original.director.tamanho; i++)
    {
        strcpy(copia.director.elementos[i], original.director.elementos[i]);
    }

    copia.cast.tamanho = original.cast.tamanho;
    for (int i = 0; i < original.cast.tamanho; i++)
    {
        strcpy(copia.cast.elementos[i], original.cast.elementos[i]);
    }

    copia.listedIn.tamanho = original.listedIn.tamanho;
    for (int i = 0; i < original.listedIn.tamanho; i++)
    {
        strcpy(copia.listedIn.elementos[i], original.listedIn.elementos[i]);
    }

    return copia;
}

/* ============================ BUSCA POR ID ============================ */

// Lê os IDs digitados e retorna um array de Shows filtrados
Show *lerEntrada(Show *shows, int total, int *quantidadeFiltrados)
{
    char input[MAX_STR];
    int capacidade = 100;
    *quantidadeFiltrados = 0;

    Show *filtrados = (Show *)malloc(capacidade * sizeof(Show));

    while (fgets(input, MAX_STR, stdin))
    {
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "FIM") == 0)
        {
            break;
        }

        for (int i = 0; i < total; i++)
        {
            if (strcmp(shows[i].showId, input) == 0)
            {
                if (*quantidadeFiltrados >= capacidade)
                {
                    capacidade *= 2;
                    filtrados = (Show *)realloc(filtrados, capacidade * sizeof(Show));
                }

                filtrados[*quantidadeFiltrados] = clonarShow(shows[i]);
                (*quantidadeFiltrados)++;
                break; // Já encontrou o show, pode sair do for
            }
        }
    }

    return filtrados;
}

/* ============================ FUNÇÕES DE ORDENAÇÃO ============================ */

void swap(Show* a, Show* b) {
    Show temp = *a;
    *a = *b;
    *b = temp;
    movimentacoes++;
}

int encontrarMenorIndex(Show shows[], int inicio, int n) {
    int menor = inicio;
    for (int i = inicio + 1; i < n; i++) {
        comparacoes++;
        if (strcmp(shows[i].title, shows[menor].title) < 0) {
            menor = i;
        }
    }
    return menor;
}

void selecaoRecursiva(Show shows[], int inicio, int n, clock_t tempo_inicio, const char *matricula)
{
    
    if (inicio >= n - 1)
    {
        // CASO BASE: Array totalmente ordenado
        clock_t tempo_fim = clock();
        double tempo_execucao = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

        // Criação do arquivo de log
        FILE *log = fopen("838966SelecaoRecursiva.txt", "w");
        if (log == NULL)
        {
            printf("Erro ao criar arquivo de log.\n");
            return;
        }

        fprintf(log, "%s\t%lld\t%lld\t%lf\n", matricula, comparacoes, movimentacoes, tempo_execucao);
        fclose(log);

        return;
    }

    int indiceMenor = encontrarMenorIndex(shows, inicio, n);

    if (indiceMenor != inicio)
    {
        
    swap(&shows[inicio], &shows[indiceMenor]);
    }

    selecaoRecursiva(shows, inicio + 1, n, tempo_inicio, matricula);
}

/* ============================ FUNÇÃO PRINCIPAL ============================ */

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

    Show *shows = NULL;
    int total = carregar_shows("../tmp/disneyplus.csv", &shows);

    int quantidadeFiltrados = 0;
    char tituloBusca[MAX_STR];
    const char *matricula = "838966";

    Show *showsFiltrados = lerEntrada(shows, total, &quantidadeFiltrados);

    free(shows);

    clock_t inicio = clock();
    selecaoRecursiva(showsFiltrados, 0, quantidadeFiltrados, inicio, matricula);

    for (int i = 0; i < quantidadeFiltrados; i++)
    {
        imprimir_show(showsFiltrados[i]);
    }

    free(showsFiltrados);

    return 0;
}