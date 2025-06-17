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


typedef struct ListaSequencial {
    Show *elementos; // Ponteiro para o vetor de Shows
    int tamanho;     // Número atual de elementos válidos na lista
    int capacidade;  // Capacidade total do vetor
} ListaSequencial;


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
    


/* ============================ FUNÇÕES PARA MANIPULAÇÃO DE LISTA SEQUENCIAL ============================ */

// Inicializa uma lista sequencial
void inicializar_lista_sequencial(ListaSequencial *lista, int capacidade) {
    lista->elementos = (Show *)malloc(capacidade * sizeof(Show));
    if (lista->elementos == NULL) {
        perror("Erro ao alocar memória para a lista sequencial");
        exit(1);
    }
    lista->tamanho = 0;
    lista->capacidade = capacidade;
}

void inicializar_lista_sequencial_populada(ListaSequencial *lista, int capacidade, Show *shows, int numShows) {
    lista->elementos = (Show *)malloc(capacidade * sizeof(Show));
    if (lista->elementos == NULL) {
        perror("Erro ao alocar memória para a lista sequencial");
        exit(1);
    }
    lista->tamanho = 0;
    lista->capacidade = capacidade;

    for (int i = 0; i < numShows; i++) {
        lista->elementos[i] = shows[i];
        lista->tamanho++;
    }
}

// Libera a memória alocada para a lista sequencial
void liberar_lista_sequencial(ListaSequencial *lista) {
    free(lista->elementos);
    lista->elementos = NULL;
    lista->tamanho = 0;
    lista->capacidade = 0;
}


// Inserir no inicio da lista sequencial
void inserir_inicio(ListaSequencial *lista, Show show) {
    if (lista->tamanho >= lista->capacidade) {
        perror("Erro:Lista sequencial cheia, não é possível inserir no início");
        exit(1);

    }else if (lista->tamanho == 0) {
        // Se a lista estiver vazia, apenas insere o elemento
        lista->elementos[0] = show;
        lista->tamanho++;

    }else 
    {
        // Desloca os elementos para a direita
        for (int i = lista->tamanho; i > 0; i--) {
            lista->elementos[i] = lista->elementos[i - 1];
        }

        // Insere o novo elemento no início
        lista->elementos[0] = show;
        lista->tamanho++;
    }
}

void inserir_fim(ListaSequencial *lista, Show show) {

    if (lista->tamanho >= lista->capacidade) {
        perror("Erro: Lista sequencial cheia, não é possível inserir no final");
        exit(1);
    } else {
        // Insere o novo elemento no final
        lista->elementos[lista->tamanho] = show;
        lista->tamanho++;
    }

}

void inserir(ListaSequencial *lista, Show show, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho || lista->tamanho >= lista->capacidade) {
        perror("Erro: Posição inválida ou lista cheia");
        exit(1);
    }
    else
    {
        // desloca os elementos para a direita
        for (int i = lista->tamanho; i > posicao; i--) {
            lista->elementos[i] = lista->elementos[i - 1];
        }

        // Insere o novo
        lista->elementos[posicao] = show;
        lista->tamanho++;
    }

}

Show remover_inicio(ListaSequencial *lista) 
{
    if (lista->tamanho == 0)
    {
        perror("Erro: Lista sequencial vazia, não é possível remover do início");
        exit(1);
    }
    else
    {
        Show showRemovido = lista->elementos[0]; // Armazena o show a ser removido

        for(int i = 1; i < lista->tamanho; i++)
        {
            lista->elementos[i - 1] = lista->elementos[i];
        }

        lista->tamanho--; // Reduz o tamanho da lista
        return showRemovido;


    }
}

Show remover_fim(ListaSequencial *lista) {
    if(lista->tamanho == 0)
    {
        perror("Erro: Lista sequencial vazia, não é possível remover do final");
        exit(1);
    }else
    {
        Show showRemovido = lista->elementos[lista->tamanho - 1]; // Armazena o show a ser removido

        lista->tamanho--;
        return showRemovido;
    }
      
}

Show remover(ListaSequencial *lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        perror("Erro: Posição inválida");
        exit(1);
    }

    Show showRemovido = lista->elementos[posicao]; // Armazena o show a ser removido

    // Desloca os elementos para a esquerda

    for(int i = posicao; i < lista->tamanho - 1; i++)
    {
        lista->elementos[i] = lista->elementos[i + 1];
    }

    lista->tamanho--; // Reduz o tamanho

    return showRemovido;

}

void imprimir_lista_sequencial(ListaSequencial *lista)
{
    for(int i = 0; i < lista->tamanho; i++)
    {
        imprimir_show(lista->elementos[i]);
    }
}


void popular_lista(ListaSequencial *lista, Show *shows, int numShows)
{
    int numComandos;
    scanf("%d", &numComandos);
    getchar(); // Limpa o '\n' após o número

    while (numComandos > 0) {
        char linha[100];
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = '\0'; // Remove newline

        char operacao[3] = "";
        int posicao = 0;
        char showId[20] = "";
        int argumentosValidos = 1;

        // Divide a linha em partes
        char *partes[3];
        int count = 0;
        char *token = strtok(linha, " ");
        while (token != NULL && count < 3) {
            partes[count++] = token;
            token = strtok(NULL, " ");
        }

        if (count > 0) {
            strcpy(operacao, partes[0]);

            if (strcmp(operacao, "I*") == 0) {
                if (count >= 3) {
                    posicao = atoi(partes[1]);
                    strcpy(showId, partes[2]);
                } else {
                    argumentosValidos = 0;
                }
            } else if (strcmp(operacao, "II") == 0 || strcmp(operacao, "IF") == 0) {
                if (count >= 2) {
                    strcpy(showId, partes[1]);
                } else {
                    argumentosValidos = 0;
                }
            } else if (strcmp(operacao, "R*") == 0) {
                if (count >= 2) {
                    posicao = atoi(partes[1]);
                } else {
                    argumentosValidos = 0;
                }
            }
        } else {
            argumentosValidos = 0;
        }

        if (argumentosValidos) {
            Show showEncontrado;
            int encontrado = 0;

            if (strlen(showId) > 0) {
                for (int i = 0; i < numShows; i++) {
                    if (strcmp(shows[i].showId, showId) == 0) {
                        showEncontrado = clonarShow(shows[i]);
                        encontrado = 1;
                        break;
                    }
                }
            }

            if ((strcmp(operacao, "I*") == 0) && encontrado) {
                inserir(lista, showEncontrado, posicao);
            } else if ((strcmp(operacao, "II") == 0) && encontrado) {
                inserir_inicio(lista, showEncontrado);
            } else if ((strcmp(operacao, "IF") == 0) && encontrado) {
                inserir_fim(lista, showEncontrado);
            } else if (strcmp(operacao, "RI") == 0) {
                Show removido = remover_inicio(lista);
                printf("(R) %s\n", removido.title);
            } else if (strcmp(operacao, "RF") == 0) {
                Show removido = remover_fim(lista);
                printf("(R) %s\n", removido.title);
            } else if (strcmp(operacao, "R*") == 0) {
                Show removido = remover(lista, posicao);
                printf("(R) %s\n", removido.title);
            }
        }

        numComandos--;
    }
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


/* ============================ FUNÇÃO PRINCIPAL ============================ */
int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    Show *shows = NULL;
    int total = carregar_shows("/tmp/disneyplus.csv", &shows);

    int quantidadeFiltrados = 0;
    Show *showsFiltrados = lerEntrada(shows, total, &quantidadeFiltrados);

    ListaSequencial lista;
    inicializar_lista_sequencial_populada(&lista, 1369, showsFiltrados, quantidadeFiltrados);

    popular_lista(&lista, shows, 1369);

    imprimir_lista_sequencial(&lista);

    liberar_lista_sequencial(&lista);

    free(shows);

    free(showsFiltrados); 

    return 0;
}