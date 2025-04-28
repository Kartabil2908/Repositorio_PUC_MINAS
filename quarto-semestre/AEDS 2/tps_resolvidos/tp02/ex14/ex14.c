/* ============================ BIBLIOTECAS ============================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>

/* ============================ DEFINIÇÕES ============================ */
#define MAX_LINE 10000 // Tamanho máximo de uma linha do CSV
#define MAX_STR 300    // Tamanho máximo de uma string individual
#define MAX_ELEM 30    // Máximo de elementos em uma lista (diretores, atores e categorias)

/* ============================ ESTRUTURAS DE DADOS ============================ */
// Lista de strings (usada para diretores, elenco e categorias)
typedef struct {
    char elementos[MAX_ELEM][MAX_STR]; // Vetor de strings
    int tamanho;                       // Número atual de elementos válidos na lista
} Lista;

// Estrutura que representa um show
typedef struct {
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

/* ============================ VARIÁVEIS GLOBAIS ============================ */
long long comparacoes = 0;
long long movimentacoes = 0;

/* ============================ PROTÓTIPOS DAS FUNÇÕES ============================ */
// Funções auxiliares para manipulação de strings
void trim(char *str);
int compareIgnoreCase(const char *str1, const char *str2);

// Funções para manipulação de listas
void ordenar_lista(Lista *lista);
Lista separar_lista(char *campo);

// Funções para manipulação de datas
int mes_para_numero(const char *mes);
int extrair_ano(const char *data);
int extrair_mes(const char *data);
int extrair_dia(const char *data);
int comparar_datas(const char *data1, const char *data2);
int comparar_titles(const char *title1, const char *title2);
int comparar_shows(Show a, Show b);

// Funções de impressão
void imprimir_lista(Lista lista);
void imprimir_diretores(Lista lista);
void imprimir_show(Show show);

// Funções para parseamento de CSV
void parse_csv_line(char *line, Show *show);
int carregar_shows(const char *caminho, Show **shows);
Show clonarShow(Show original);

// Funções para leitura de entrada e processamento
Show *lerEntrada(Show *shows, int total, int *quantidadeFiltrados);

// Funções de ordenação
void swap(Show *a, Show *b);
int particionar(Show *v, int low, int high);
void quicksort(Show *v, int low, int high);

// Função para geração de log
void gerar_log(const char *nome_arquivo, double tempo_execucao);

/* ============================ FUNÇÕES AUXILIARES PARA STRINGS ============================ */
// Remove espaços em branco no início e no final da string
void trim(char *str) {
    int inicio = 0;
    int fim = strlen(str) - 1;
    int i;

    // Avança o índice "inicio" até encontrar um caractere não-espaço
    while (isspace((unsigned char)str[inicio])) {
        inicio++;
    }

    // Retrocede o índice "fim" até encontrar um caractere não-espaço
    while (fim > inicio && isspace((unsigned char)str[fim])) {
        fim--;
    }

    // Copia os caracteres úteis para o início da string
    for (i = 0; inicio <= fim; i++, inicio++) {
        str[i] = str[inicio];
    }

    // Finaliza a string
    str[i] = '\0';
}

// Função que compara duas strings ignorando maiúsculas/minúsculas
int compareIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        char char1 = tolower((unsigned char)*str1);
        char char2 = tolower((unsigned char)*str2);

        if (char1 != char2) {
            return char1 - char2;
        }

        str1++;
        str2++;
    }

    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}

/* ============================ FUNÇÕES PARA MANIPULAÇÃO DE LISTAS ============================ */
// Ordena alfabeticamente os elementos de uma lista
void ordenar_lista(Lista *lista) {
    for (int i = 0; i < lista->tamanho - 1; i++) {
        for (int j = i + 1; j < lista->tamanho; j++) {
            if (strcmp(lista->elementos[i], lista->elementos[j]) > 0) {
                char temp[MAX_STR];
                strcpy(temp, lista->elementos[i]);
                strcpy(lista->elementos[i], lista->elementos[j]);
                strcpy(lista->elementos[j], temp);
            }
        }
    }
}

// Converte uma string separada por vírgulas em uma lista
Lista separar_lista(char *campo) {
    Lista lista;
    lista.tamanho = 0;

    char *token = strtok(campo, ",");
    while (token != NULL && lista.tamanho < MAX_ELEM) {
        while (*token == ' ') {
            token++; // Remove espaços iniciais
        }

        token[strcspn(token, "\r\n")] = 0; // Remove quebras de linha

        strcpy(lista.elementos[lista.tamanho], token);
        lista.tamanho++;

        token = strtok(NULL, ",");
    }

    return lista; // A ordenação será feita fora, apenas onde for necessário
}

/* ============================ FUNÇÕES PARA MANIPULAÇÃO DE DATAS ============================ */
// Converte mês de string para número
int mes_para_numero(const char *mes) {
    if (strcmp(mes, "January") == 0) return 1;
    if (strcmp(mes, "February") == 0) return 2;
    if (strcmp(mes, "March") == 0) return 3;
    if (strcmp(mes, "April") == 0) return 4;
    if (strcmp(mes, "May") == 0) return 5;
    if (strcmp(mes, "June") == 0) return 6;
    if (strcmp(mes, "July") == 0) return 7;
    if (strcmp(mes, "August") == 0) return 8;
    if (strcmp(mes, "September") == 0) return 9;
    if (strcmp(mes, "October") == 0) return 10;
    if (strcmp(mes, "November") == 0) return 11;
    if (strcmp(mes, "December") == 0) return 12;
    return 0; // Se não encontrar mês, retorna 0
}

// Extrai o ano da string de data
int extrair_ano(const char *data) {
    int ano;
    sscanf(data, "%*s %*d, %d", &ano);
    return ano;
}

// Extrai o mês da string de data
int extrair_mes(const char *data) {
    char mes[20];
    sscanf(data, "%s", mes);
    return mes_para_numero(mes);
}

// Extrai o dia da string de data
int extrair_dia(const char *data) {
    int dia;
    sscanf(data, "%*s %d,", &dia);
    return dia;
}

// Compara duas datas no formato "September 24, 2021"
int comparar_datas(const char *data1, const char *data2) {
    if (strlen(data1) == 0 && strlen(data2) == 0) return 0;
    if (strlen(data1) == 0) return 1;  // Campo vazio é considerado maior
    if (strlen(data2) == 0) return -1;

    int ano1 = extrair_ano(data1);
    int ano2 = extrair_ano(data2);

    if (ano1 != ano2) {
        return ano1 - ano2;
    }

    int mes1 = extrair_mes(data1);
    int mes2 = extrair_mes(data2);

    if (mes1 != mes2) {
        return mes1 - mes2;
    }

    int dia1 = extrair_dia(data1);
    int dia2 = extrair_dia(data2);

    return dia1 - dia2;
}

// Compara dois titles (ignorando espaços antes/depois e maiúsculas/minúsculas)
int comparar_titles(const char *title1, const char *title2) {
    char t1[300], t2[300];

    strcpy(t1, title1);
    strcpy(t2, title2);

    // Remove espaços em branco nas pontas
    trim(t1);
    trim(t2);

    return strcasecmp(t1, t2); // Compara sem considerar maiúsculas/minúsculas
}

// Compara dois shows pelo dateAdded, depois pelo title em caso de empate
int comparar_shows(Show a, Show b) {
    comparacoes++;

    int resultado_data = comparar_datas(a.dateAdded, b.dateAdded);

    if (resultado_data != 0) {
        return resultado_data;
    } else {
        return comparar_titles(a.title, b.title);
    }
}

/* ============================ FUNÇÕES DE IMPRESSÃO ============================ */
// Imprime uma lista de forma formatada com colchetes (ex: [A, B, C])
void imprimir_lista(Lista lista) {
    printf("[");
    for (int i = 0; i < lista.tamanho; i++) {
        printf("%s", lista.elementos[i]);
        if (i < lista.tamanho - 1) {
            printf(", ");
        }
    }
    printf("]");
}

// Imprime a lista de diretores (sem colchetes e sem ordenação)
void imprimir_diretores(Lista lista) {
    if (lista.tamanho == 0) {
        printf("NaN");
    } else {
        for (int i = 0; i < lista.tamanho; i++) {
            printf("%s", lista.elementos[i]);
            if (i < lista.tamanho - 1) {
                printf(", ");
            }
        }
    }
}

// Imprime todos os campos de um Show no formato do enunciado
void imprimir_show(Show show) {
    printf("=> ");

    if (strlen(show.showId) > 0) {
        printf("%s ## ", show.showId);
    } else {
        printf("NaN ## ");
    }

    if (strlen(show.title) > 0) {
        printf("%s ## ", show.title);
    } else {
        printf("NaN ## ");
    }

    if (strlen(show.type) > 0) {
        printf("%s ## ", show.type);
    } else {
        printf("NaN ## ");
    }

    imprimir_diretores(show.director); // Diretores não ordenados
    printf(" ## ");

    if (show.cast.tamanho > 0) {
        ordenar_lista(&show.cast); // Elenco ordenado
        imprimir_lista(show.cast);
    } else {
        printf("[NaN]");
    }
    printf(" ## ");

    if (strlen(show.country) > 0) {
        printf("%s ## ", show.country);
    } else {
        printf("NaN ## ");
    }

    if (strlen(show.dateAdded) > 0) {
        printf("%s ## ", show.dateAdded);
    } else {
        printf("NaN ## ");
    }

    if (show.releaseYear > 0) {
        printf("%d ## ", show.releaseYear);
    } else {
        printf("0 ## ");
    }

    if (strlen(show.rating) > 0) {
        printf("%s ## ", show.rating);
    } else {
        printf("NaN ## ");
    }

    if (strlen(show.duration) > 0) {
        printf("%s ## ", show.duration);
    } else {
        printf("NaN ## ");
    }

    if (show.listedIn.tamanho > 0) {
        ordenar_lista(&show.listedIn); // Categorias ordenadas
        imprimir_lista(show.listedIn);
    } else {
        printf("NaN");
    }

    printf(" ##\n");
}

/* ============================ PARSEAMENTO DE CSV ============================ */
// Converte uma linha do CSV em uma struct Show
void parse_csv_line(char *line, Show *show) {
    char campos[12][MAX_STR] = {""}; // Armazena os campos extraídos
    int campo_idx = 0;               // Índice do campo atual
    int i = 0;                       // Índice para percorrer a linha
    bool in_aspas = false;           // Indica se está dentro de aspas
    char c;
    char buffer[MAX_STR]; // Buffer para construir cada campo
    int buf_idx = 0;      // Índice do buffer

    while ((c = line[i++]) != '\0' && campo_idx < 12) {
        if (c == '"') {
            in_aspas = !in_aspas;
        } else if (c == ',' && !in_aspas) {
            buffer[buf_idx] = '\0';
            strcpy(campos[campo_idx++], buffer);
            buf_idx = 0;
        } else {
            buffer[buf_idx++] = c;
        }
    }

    buffer[buf_idx] = '\0';
    strcpy(campos[campo_idx], buffer);

    strcpy(show->showId, campos[0]);
    strcpy(show->type, campos[1]);
    strcpy(show->title, campos[2]);

    if (strlen(campos[3]) > 0) {
        show->director = separar_lista(campos[3]); // NÃO ordenar diretores aqui
    } else {
        show->director.tamanho = 0;
    }

    if (strlen(campos[4]) > 0) {
        show->cast = separar_lista(campos[4]);
    } else {
        show->cast.tamanho = 0;
    }

    strcpy(show->country, campos[5]);
    strcpy(show->dateAdded, campos[6]);

    if (strlen(campos[7]) > 0) {
        show->releaseYear = atoi(campos[7]);
    } else {
        show->releaseYear = 0;
    }

    strcpy(show->rating, campos[8]);
    strcpy(show->duration, campos[9]);

    if (strlen(campos[10]) > 0) {
        show->listedIn = separar_lista(campos[10]);
    } else {
        show->listedIn.tamanho = 0;
    }
}

/* ============================ LEITURA DO CSV ============================ */
// Lê o arquivo CSV e armazena os registros em um vetor dinâmico de Shows
int carregar_shows(const char *caminho, Show **shows) {
    FILE *file = fopen(caminho, "r"); // Abre o arquivo para leitura
    if (!file) {
        perror("Erro ao abrir o arquivo CSV");
        exit(1);
    }

    char line[MAX_LINE];         // Buffer para leitura de linha
    fgets(line, MAX_LINE, file); // Ignora cabeçalho

    int capacidade = 100; // Capacidade inicial do vetor
    int count = 0;        // Quantidade de registros lidos

    *shows = (Show *)malloc(capacidade * sizeof(Show));
    if (*shows == NULL) {
        perror("Erro ao alocar memória inicial");
        exit(1);
    }

    while (fgets(line, MAX_LINE, file)) {
        if (count >= capacidade) {
            capacidade *= 2;
            *shows = (Show *)realloc(*shows, capacidade * sizeof(Show));
            if (*shows == NULL) {
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

// Clona um objeto Show
Show clonarShow(Show original) {
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
    for (int i = 0; i < original.director.tamanho; i++) {
        strcpy(copia.director.elementos[i], original.director.elementos[i]);
    }

    copia.cast.tamanho = original.cast.tamanho;
    for (int i = 0; i < original.cast.tamanho; i++) {
        strcpy(copia.cast.elementos[i], original.cast.elementos[i]);
    }

    copia.listedIn.tamanho = original.listedIn.tamanho;
    for (int i = 0; i < original.listedIn.tamanho; i++) {
        strcpy(copia.listedIn.elementos[i], original.listedIn.elementos[i]);
    }

    return copia;
}

/* ============================ LEITURA DE ENTRADA E PROCESSAMENTO ============================ */
// Lê os IDs digitados e retorna um array de Shows filtrados
Show *lerEntrada(Show *shows, int total, int *quantidadeFiltrados) {
    char input[MAX_STR];
    int capacidade = 100;
    *quantidadeFiltrados = 0;

    Show *filtrados = (Show *)malloc(capacidade * sizeof(Show));

    while (fgets(input, MAX_STR, stdin)) {
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "FIM") == 0) {
            break;
        }

        for (int i = 0; i < total; i++) {
            if (strcmp(shows[i].showId, input) == 0) {
                if (*quantidadeFiltrados >= capacidade) {
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

/* ============================ RADIX SORT ============================ */
/*
    O Radix Sort é um algoritmo de ordenação que NÃO compara os elementos diretamente.
    Em vez disso, ele organiza os itens olhando para cada dígito separadamente.

    A ideia aqui é começar pelo dígito menos importante (no caso, o último número do ano de lançamento)
    e ir indo para o mais importante (o primeiro número).

    Para cada "passada" em um dígito, a gente usa um algoritmo de ordenação que é estável.
    A escolha foi usar o Counting Sort, só que adaptado para desempatar usando o título (title)
    se os anos forem iguais.

    --- Complexidade:
    - Melhor, médio e pior caso: O(d * (n + k))
    
    Onde:
    - n = número de elementos que estamos ordenando
    - k = intervalo dos valores possíveis (aqui é o intervalo dos anos de lançamento)
    - d = número de dígitos (para anos, são sempre 4 dígitos, tipo 2024)

    Como tanto o número de dígitos (d) quanto o intervalo (k) são pequenos e fixos,
    na prática o Radix Sort se comporta quase como O(n), bem rápido!

    --- Observação:
    Como Radix Sort é estável, o desempate por título funciona certinho:
    se dois shows tiverem o mesmo releaseYear, eles ficam ordenados pelo title.
*/

void swap(Show *a, Show *b) {
    Show temp = *a;
    *a = *b;
    *b = temp;
}

/* Função auxiliar para encontrar o maior releaseYear */
int encontrar_maior_releaseYear(Show *v, int n) {
    int maior = v[0].releaseYear;
    for (int i = 1; i < n; i++) {
        comparacoes++;
        if (v[i].releaseYear > maior) {
            maior = v[i].releaseYear;
        }
    }
    return maior;
}

/* Counting Sort adaptado para Radix Sort (estável e com desempate por title) */
void counting_sort(Show *v, int n, int exp) {
    Show *output = (Show *)malloc(n * sizeof(Show));
    int count[10] = {0}; // Para os dígitos 0-9

    // Conta a ocorrência dos dígitos considerando o dígito atual (exp)
    for (int i = 0; i < n; i++) {
        int digito = (v[i].releaseYear / exp) % 10;
        count[digito]++;
    }

    // Ajusta count[i] para que cada posição contenha a posição correta no output
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Constrói o vetor de saída de trás para frente (para estabilidade)
    for (int i = n - 1; i >= 0; i--) {
        int digito = (v[i].releaseYear / exp) % 10;
        output[count[digito] - 1] = clonarShow(v[i]);
        count[digito]--;
        movimentacoes++;
    }

    // Copia o vetor ordenado de volta para v
    for (int i = 0; i < n; i++) {
        v[i] = clonarShow(output[i]);
        movimentacoes++;
    }

    free(output);
}

/* Função principal de Radix Sort para releaseYear (com desempate por title) */
void radix_sort(Show *v, int n) {
    // Encontra o maior releaseYear para saber quantos dígitos existem
    int maior = encontrar_maior_releaseYear(v, n);

    // Aplica Counting Sort para cada dígito, começando pelo menos significativo
    for (int exp = 1; maior / exp > 0; exp *= 10) {
        counting_sort(v, n, exp);
    }

    /* 
        Após o Radix Sort pelos dígitos de releaseYear,
        fazemos uma ordenação final por título apenas entre elementos
        que possuem o mesmo releaseYear.
    */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n && v[i].releaseYear == v[j].releaseYear; j++) {
            comparacoes++;
            if (comparar_titles(v[i].title, v[j].title) > 0) {
                swap(&v[i], &v[j]);
                movimentacoes += 3;
            }
        }
    }
}

/* ============================ FUNÇÃO DE LOG ============================ */

// Função para gerar o log da execução
void gerar_log(const char *nome_arquivo, double tempo_execucao) {
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de log.\n");
        return;
    }

    fprintf(arquivo, "838966\t%lld\t%lld\t%.6lf\n", comparacoes, movimentacoes, tempo_execucao);

    fclose(arquivo);
}

/* ============================ FUNÇÃO PRINCIPAL ============================ */
int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    Show *shows = NULL;
    int total = carregar_shows("/tmp/disneyplus.csv", &shows);

    int quantidadeFiltrados = 0;
    Show *showsFiltrados = lerEntrada(shows, total, &quantidadeFiltrados);

    free(shows); 

    clock_t inicio = clock();
    radix_sort(showsFiltrados, quantidadeFiltrados);
    clock_t fim = clock();

    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    gerar_log("838966_radixsort.txt", tempo_execucao);

    for (int i = 0; i < quantidadeFiltrados; i++) {
        imprimir_show(showsFiltrados[i]);
    }

    free(showsFiltrados); 

    return 0;
}