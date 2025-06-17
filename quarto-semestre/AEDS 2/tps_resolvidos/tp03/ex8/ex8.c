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
typedef struct Show {
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


typedef struct ListaDupla
{
    Show show;
    struct ListaDupla *prox;
    struct ListaDupla *ant;

}ListaDupla;

/* ============================ VARIÁVEIS GLOBAIS ============================ */
long long comparacoes = 0;
long long movimentacoes = 0;

/* ============================ PROTÓTIPOS DAS FUNÇÕES ============================ */



// Funções para manipulação de listas
void ordenar_lista(Lista *lista);
Lista separar_lista(char *campo);

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
    

/* ============================ FUNÇÕES PARA MANIPULAÇÃO DE LISTAS DINAMICAS  DUPLAMENTE ENCADEADAS ============================ */

void inicializarListaDuplaPopulada(ListaDupla **lista, Show *shows, int total) {
    *lista = NULL;
    ListaDupla *ultimo = NULL;

    for (int i = 0; i < total; i++) {
        ListaDupla *novo = (ListaDupla *)malloc(sizeof(ListaDupla));
        if (novo == NULL) {
            perror("Erro ao alocar memória para lista dupla");
            exit(1);
        }
        novo->show = clonarShow(shows[i]);
        novo->prox = NULL;
        novo->ant = ultimo;

        if (*lista == NULL) {
            *lista = novo; // Primeiro elemento
        } else {
            ultimo->prox = novo; // Liga o último ao novo
        }
        ultimo = novo; // Atualiza o último
    }
}


void liberarListaDupla(ListaDupla *lista) {
    ListaDupla *atual = lista;
    while (atual != NULL) {
        ListaDupla *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

void imprimirListaDupla(ListaDupla *lista)
{
    ListaDupla *atual = lista;
    while (atual != NULL) {
        imprimir_show(atual->show);
        atual = atual->prox;
    }
    
}



/* ============================ FUNÇÕES PARA MANIPULAÇÃO DE ATRIBUTOS ============================ */

void extrairDateAdded(Show show, int* dia, int* mes, int* ano) {
    char mesStr[20], diaStr[10], anoStr[10];

    // Exemplo: "September 24, 2021"
    sscanf(show.dateAdded, "%s %s %s", mesStr, diaStr, anoStr);

    // Remove a vírgula do dia
    diaStr[strcspn(diaStr, ",")] = '\0';

    // Converte strings para inteiros
    *dia = atoi(diaStr);
    *ano = atoi(anoStr);

    // Converte o mês por extenso para número
    if (strcmp(mesStr, "January") == 0) *mes = 1;
    else if (strcmp(mesStr, "February") == 0) *mes = 2;
    else if (strcmp(mesStr, "March") == 0) *mes = 3;
    else if (strcmp(mesStr, "April") == 0) *mes = 4;
    else if (strcmp(mesStr, "May") == 0) *mes = 5;
    else if (strcmp(mesStr, "June") == 0) *mes = 6;
    else if (strcmp(mesStr, "July") == 0) *mes = 7;
    else if (strcmp(mesStr, "August") == 0) *mes = 8;
    else if (strcmp(mesStr, "September") == 0) *mes = 9;
    else if (strcmp(mesStr, "October") == 0) *mes = 10;
    else if (strcmp(mesStr, "November") == 0) *mes = 11;
    else if (strcmp(mesStr, "December") == 0) *mes = 12;
    else *mes = 0; // mês inválido
}

// Função que compara datas (formato: dia/mes/ano)
int compararData(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) {
    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
}

// Compara dois nós da lista por data e título
int compararDateEtitle(Show a, Show b) {
    int d1, m1, a1, d2, m2, a2;
    extrairDateAdded(a, &d1, &m1, &a1);
    extrairDateAdded(b, &d2, &m2, &a2);

    int cmpData = compararData(d1, m1, a1, d2, m2, a2);
    if (cmpData != 0) return cmpData;

    char tituloA[300];
    char tituloB[300];

    // converte título A para minúsculo
    for (int i = 0; a.title[i]; i++) {
        tituloA[i] = tolower((unsigned char)a.title[i]);
        tituloA[i+1] = '\0';
    }

    // converte título B para minúsculo
    for (int i = 0; b.title[i]; i++) {
        tituloB[i] = tolower((unsigned char)b.title[i]);
        tituloB[i+1] = '\0';
    }

    return strcmp(tituloA, tituloB);
}
// Troca os conteúdos de dois nós
void trocarShows(ListaDupla *a, ListaDupla *b) {
    Show temp = a->show;
    a->show = b->show;
    b->show = temp;

    movimentacoes += 3;
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



// Compara dois shows pelo dateAdded, depois pelo title em caso de empate
int compararShows(const Show* a, const Show* b) {
    int resultado;
    
    // Comparação por diretor
    if (a->director.tamanho == 0 && b->director.tamanho == 0) {
        resultado = 0; // Ambos sem diretor
    } else if (a->director.tamanho == 0) {
        return 1; // a sem diretor (vem depois)
    } else if (b->director.tamanho == 0) {
        return -1; // b sem diretor (vem depois)
    } else {
        // Compara pelo primeiro nome da lista de diretores
        resultado = strcmp(a->director.elementos[0], b->director.elementos[0]);
    }

    if (resultado != 0) {
        return resultado;
    } else {
        // Desempate pelo título
        return strcmp(a->title, b->title);
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

/* ============================ FUNÇÃO ORDENAÇÃO ============================ */

// Particiona a lista duplamente encadeada com base no pivô
ListaDupla* particionar(ListaDupla *inicio, ListaDupla *fim) {
    Show pivo = fim->show;
    ListaDupla *i = inicio->ant;

    for (ListaDupla *j = inicio; j != fim; j = j->prox) {
        comparacoes++;
        if (compararDateEtitle(j->show, pivo) <= 0) {
            i = (i == NULL) ? inicio : i->prox;
            trocarShows(i, j);
        }
    }

    i = (i == NULL) ? inicio : i->prox;
    trocarShows(i, fim);
    return i;
}

// Função recursiva do quicksort para lista duplamente encadeada
void quicksortListaDupla(ListaDupla *inicio, ListaDupla *fim) {
    if (fim != NULL && inicio != fim && inicio != fim->prox) {
        ListaDupla *pivo = particionar(inicio, fim);
        quicksortListaDupla(inicio, pivo->ant);
        quicksortListaDupla(pivo->prox, fim);
    }
}

void gravarLogQuicksort(long comparacoes, long movimentacoes, double tempo) {
    FILE *arquivo = fopen("838966_quicksort2.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "838966\t%ld\t%ld\t%.6f\n", comparacoes, movimentacoes, tempo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de log.\n");
    }
}


    

/* ============================ FUNÇÃO PRINCIPAL ============================ */
int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    Show *shows = NULL;
    int total = carregar_shows("/tmp/disneyplus.csv", &shows);

    int quantidadeFiltrados = 0;
    Show *showsFiltrados = lerEntrada(shows, total, &quantidadeFiltrados);

    ListaDupla *listaDupla = NULL;
    inicializarListaDuplaPopulada(&listaDupla, showsFiltrados, quantidadeFiltrados);

    ListaDupla *inicio = listaDupla;
    ListaDupla *fim = listaDupla;
    while (fim->prox != NULL) {
        fim = fim->prox;
    }

    quicksortListaDupla(inicio, fim);

    gravarLogQuicksort(comparacoes, movimentacoes, (double)clock() / CLOCKS_PER_SEC);

    imprimirListaDupla(listaDupla);

    liberarListaDupla(listaDupla);
    free(shows);
    free(showsFiltrados);

    return 0;
}
