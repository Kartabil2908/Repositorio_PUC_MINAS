#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define ARQUIVO_CAMINHO "/tmp/pokemon.csv"
#define MAX_POKEMONS 802
#define MAX_BUFFER 1000
#define MAX_LISTA 50
#define MAX_TAMANHO_HABILIDADE 50
#define verdade 1
#define falso 0
#define MAX_NOMES 200
#define MAX_IDS 200
#define K 10

typedef struct Lista {
    char itens[MAX_LISTA][50];
    int contagem;
} Lista;

typedef struct Pokemon {
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

int num_movimentacoes = 0;
int num_comparacoes = 0;


void incrementar_movimentacao() {
    num_movimentacoes++;
}

void incrementar_comparacao() {
    num_comparacoes++;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------
void criarLog(double tempoExecucao, int comparacoes, int movimentacoes, const char *arquivo);
char* trim(char *str);
char *extrair_sub(char *, size_t, size_t);
char *remover_espaco(char *);
void substituir_caracter(char *, char, char);
Lista converter_para_lista(char[]);
void adicionar_elemento(Lista *lista, const char *elemento);
void exibir_elementos(Lista*);
Pokemon inicializar_pokemon();
char *encontrar_separador(char**, const char*);
int pesquisa_binaria(Pokemon *pokemons, char* name, int n);
void preencher_array_pokemons(Pokemon[]);
int comparar_pokemon(const void *a, const void *b);
void exibir_pokemon(Pokemon pokemon);
void swap(Pokemon *a, Pokemon *b);
void swap_pokemons(Pokemon lista[], int primeiro, int segundo);
int findMinIndex(Pokemon pokemons[], int start, int n);
void selectionSortRec(Pokemon pokemons[], int start, int n, int *comparacoes, int *movimentacoes);
void ordenarPokemonsPorNome(Pokemon pokemons[], int n);
void shellsort(Pokemon pokemon_array[], int n);
void executarQuickSort(Pokemon pokemon_array[], int tamanho_array);
void executarBubble(Pokemon pokemon_array[], int tamanho_array);
void construirHeapInvertido(Pokemon pokemons[], int n, int i, int* comparacoes, int* movimentacoes);
void adicionar_pokemon_ao_heap(Pokemon heap[], int pos);
bool tem_filhos(int indice, int tamanho);
void ordenar_parcialmente_heap(Pokemon lista[], int total);
int comparar_alturas(Pokemon p1, Pokemon p2);
void ajustar_heap(Pokemon heap[], int tamanho);
int encontrar_maior_filho(Pokemon heap[], int indice, int tamanho);
int compara_datas(struct tm data1, struct tm data2);
struct tm string_para_data(const char *data_str);
void insercao_parcial_ordenacao(Pokemon *lista_pokes, int total, int limite);
int obter_valor_caractere(const char *habilidade, int posicao);
int encontrar_tam_max_nome(Pokemon *pkm, int total);
int encontrar_tam_max_habilidade(Pokemon *pkm, int total);
void ordenacao_radix(Pokemon *pkm, int total, int tam_habilidade, int tam_nome);
// ---------------------------------------------------------------------------------------------------------------------------------------------

/*int main() { // QUESTAO 4
    char entrada[200];
    int resposta;
    int qtddPokemons = 0;

    char nomeArquivo[30] = "1449304_binaria.txt";

    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        for (int i = 0, j = 0; i < 802; i++) {
            resposta = strcmp(pokemons[i].id, entrada);
            incrementar_comparacao();
            if (resposta == 0) {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                incrementar_movimentacao();
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

    for (int i = 0; i < qtddPokemons; i++) {
        pokemonsEntrada[i] = temporario[i];
    }

    free(temporario);

    clock_t start, end;
    start = clock();

    ordenarPokemonsPorNome(pokemonsEntrada,qtddPokemons);

    end = clock();
    double tempoExecucao = ((double)(end - start)) / CLOCKS_PER_SEC;

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        if (pesquisa_binaria(pokemonsEntrada, entrada, qtddPokemons)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        scanf("%s", entrada);
    }

    // Gravar resultados em um arquivo

    criarLog(tempoExecucao,num_comparacoes,num_movimentacoes,nomeArquivo);
  

    return 0;
}*/



/*int main() { // QUESTAO 6

    char entrada[200];
    int resposta;
    int qtddPokemons = 0;
    int i = 0;
    int j = 0;


    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        for ( i = 0; i < 802; i++) {
            resposta = strcmp(pokemons[i].id, entrada);
    
            if (resposta == 0) {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

        for ( i = 0; i < qtddPokemons; i++) {
        pokemonsEntrada[i] = temporario[i];
        }

        free(temporario);

        ordenarPokemonsPorNome(pokemonsEntrada,qtddPokemons);
    
     for ( i = 0; i < qtddPokemons; i++) {
        exibir_pokemon(pokemonsEntrada[i]);
    }

   
  
}*/

/*int main() 
{ // QUESTAO 8

    char entrada[200];
    int resposta;
    int qtddPokemons = 0;
    int i = 0;
    int j = 0;


    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        for ( i = 0; i < 802; i++) {
            resposta = strcmp(pokemons[i].id, entrada);
    
            if (resposta == 0) {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

        for ( i = 0; i < qtddPokemons; i++) {
        pokemonsEntrada[i] = temporario[i];
        }

        free(temporario);


        shellsort(pokemonsEntrada,qtddPokemons);

     for ( i = 0; i < qtddPokemons; i++) {
        exibir_pokemon(pokemonsEntrada[i]);


    }

   
  
}*/


/*int main() 
{ // QUESTAO 10

    char entrada[200];
    int resposta;
    int qtddPokemons = 0;
    int i = 0;
    int j = 0;


    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        for ( i = 0; i < 802; i++) {
            resposta = strcmp(pokemons[i].id, entrada);
    
            if (resposta == 0) {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

        for ( i = 0; i < qtddPokemons; i++) {
        pokemonsEntrada[i] = temporario[i];
        }

        free(temporario);


        executarQuickSort(pokemonsEntrada, qtddPokemons);

     for ( i = 0; i < qtddPokemons; i++) {
        exibir_pokemon(pokemonsEntrada[i]);


    }

   
  
}*/



/*int main()
{ // QUESTAO 14

    char entrada[200];
    int resposta;
    int qtddPokemons = 0;
    int total_pokemons = 802;
    int i = 0;
    int j = 0;


    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        for ( i = 0; i < 802; i++) {
            resposta = strcmp(pokemons[i].id, entrada);
    
            if (resposta == 0) {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

        for ( i = 0; i < qtddPokemons; i++) {
        pokemonsEntrada[i] = temporario[i];
        }

        free(temporario);


        int tam_max_nome = encontrar_tam_max_nome(pokemonsEntrada, qtddPokemons);
        int tam_max_habilidade = encontrar_tam_max_habilidade(pokemonsEntrada, qtddPokemons);

        ordenacao_radix(pokemonsEntrada, qtddPokemons, tam_max_habilidade, tam_max_nome);

     for ( i = 0; i < qtddPokemons; i++) {
        exibir_pokemon(pokemonsEntrada[i]);
    }

}*/

/*int main()
{ // QUESTAO 16

    char entrada[200];
    int resposta;
    int qtddPokemons = 0;
    int i = 0;
    int j = 0;


    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        for ( i = 0; i < 802; i++) {
            resposta = strcmp(pokemons[i].id, entrada);
    
            if (resposta == 0) {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

        for ( i = 0; i < qtddPokemons; i++) {
        pokemonsEntrada[i] = temporario[i];
        }

        free(temporario);


        insercao_parcial_ordenacao(pokemonsEntrada, qtddPokemons,10);

     for ( i = 0; i < 10; i++) {
        exibir_pokemon(pokemonsEntrada[i]);
    }

   
  
}*/


int main()
{ // QUESTAO 17

    char entrada[200];
    int resposta;
    int qtddPokemons = 0;
    int i = 0;
    int j = 0;


    Pokemon pokemons[802];
    preencher_array_pokemons(pokemons);

    Pokemon *temporario = malloc(802 * sizeof(Pokemon));

    scanf("%s", entrada);

    while (strcmp(entrada, "FIM") != 0) {
        for ( i = 0; i < 802; i++) {
            resposta = strcmp(pokemons[i].id, entrada);
    
            if (resposta == 0) {
                temporario[j] = pokemons[i];
                qtddPokemons++;
                j++;
            }
        }
        scanf("%s", entrada);
    }

    Pokemon pokemonsEntrada[qtddPokemons];

        for ( i = 0; i < qtddPokemons; i++) {
        pokemonsEntrada[i] = temporario[i];
        }

        free(temporario);


        ordenar_parcialmente_heap(pokemonsEntrada, qtddPokemons);

     for ( i = 0; i < 10; i++) {
        exibir_pokemon(pokemonsEntrada[i]);
    }

   
  
}




   
  






// ---------------------------------------------------------------------------------------------------------------------------------------------

// METODOS GERAIS:

// SELECTION SORT RECURSIVO -------------------------------------------------------------------------------------------------------------------

int findMinIndex(Pokemon pokemons[], int start, int n) {
    int minIndex = start;
    for (int i = start + 1; i < n; i++) {
        if (strcmp(pokemons[i].nomePokemon, pokemons[minIndex].nomePokemon) < 0) {
            minIndex = i;
        }
    }
    return minIndex;
}

void selectionSortRec(Pokemon pokemons[], int start, int n, int *comparacoes, int *movimentacoes) {
    if (start >= n - 1) return;  // Caso base: fim da ordenação

    // Encontrar o índice do menor nome a partir de start
    int minIndex = findMinIndex(pokemons, start, n);
    (*comparacoes) += (n - start - 1);  // Comparações feitas na função findMinIndex

    // Trocar o menor com o elemento na posição start
    if (minIndex != start) {
        swap(&pokemons[start], &pokemons[minIndex]);
        (*movimentacoes) += 3;  // Cada troca conta como 3 movimentações
    }

    selectionSortRec(pokemons, start + 1, n, comparacoes, movimentacoes);
}

void ordenarPokemonsPorNome(Pokemon pokemons[], int n) 
{
    clock_t tempoInicio = clock();  // Início do tempo de execução
    int comparacoes = 0;
    int movimentacoes = 0;
    char nomeArquivo[50] = "1449304_selecaoRecursiva.txt";


    selectionSortRec(pokemons, 0, n, &comparacoes, &movimentacoes);

    clock_t tempoFim = clock();  // Fim do tempo de execução

 double tempoExecucao = ((double)(tempoFim - tempoInicio) / CLOCKS_PER_SEC);

    criarLog(tempoExecucao,comparacoes,movimentacoes, nomeArquivo);


}  
void swap(Pokemon *a, Pokemon *b){
    Pokemon temp = *a;
    *a = *b;
    *b = temp;
    num_movimentacoes +=3;
}


// SELECTION SORT RECURSIVO ----------------------------------------------------------------------------------------------------


// SHELL SORT ----------------------------------------------------------------------------------------------------

void shellsort(Pokemon pokemon_array[], int n) {
    
    int j;
    clock_t tempoInicio = clock();
    char nomeArquivo[50] = "1449304_shellsort.txt";
 

    // Calculando o intervalo inicial
    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2) 
    {

        for (int i = intervalo; i < n; i++) {

            Pokemon temp = pokemon_array[i];
            incrementar_movimentacao();

            // Loop de inserção com a condição correta
            for (j = i; j >= intervalo && 
            (atof(temp.peso) < atof(pokemon_array[j - intervalo].peso) || 
            (atof(temp.peso) == atof(pokemon_array[j - intervalo].peso) && 
            strcmp(temp.nomePokemon, pokemon_array[j - intervalo].nomePokemon) < 0));
            j -= intervalo) 
            {
            incrementar_comparacao();
            pokemon_array[j] = pokemon_array[j - intervalo]; // Desloca o elemento para frente
            incrementar_movimentacao();
            }

            // Insere o elemento na posição correta
            pokemon_array[j] = temp; 
            incrementar_movimentacao();
        }

    }

    clock_t tempoFim = clock();
    double tempoExecucao = ((double)(tempoFim - tempoInicio) / CLOCKS_PER_SEC);

     criarLog(tempoExecucao,num_comparacoes,num_movimentacoes, nomeArquivo);


}



// SHELL SORT ----------------------------------------------------------------------------------------------------


// QUICK SORT ----------------------------------------------------------------------------------------------------

// quick sort para comparar o atributo geracao_dados, ou seja, a geração do pokemon
// o if dentro do primeiro for da função particao basicamente tem a mesma condição de desempate
// dos outros, mas o que muda é qye está em relação ao pivô
//NAO TA FUNCIONANDO O PIVO NO MEIO


int particao(Pokemon pokemon_array[], int esquerda, int direita) {
    Pokemon pivô = pokemon_array[direita]; // Usando o último elemento como pivô, pois testei MUITAS vezes com ele no meio, mas o critério de desempate tava dando erro
    int i = esquerda - 1;

    for (int j = esquerda; j < direita; j++) {
      
        if (strcmp(pokemon_array[j].geracao_dados, pivô.geracao_dados) < 0 ||
            (strcmp(pokemon_array[j].geracao_dados, pivô.geracao_dados) == 0 &&
             strcmp(pokemon_array[j].nomePokemon, pivô.nomePokemon) < 0)) {
            i++;
            swap(&pokemon_array[i], &pokemon_array[j]);
        }
        incrementar_comparacao();
    }
    swap(&pokemon_array[i + 1], &pokemon_array[direita]);
    return i + 1;
}


void quicksort(Pokemon pokemon_array[], int esquerda, int direita) 
{
    if (esquerda < direita) {
        int pi = particao(pokemon_array, esquerda, direita);
        quicksort(pokemon_array, esquerda, pi - 1);
        quicksort(pokemon_array, pi + 1, direita);
    }
}

void executarQuickSort(Pokemon pokemon_array[], int tamanho_array)
{   
    clock_t tempoInicio = clock();
    char nomeArquivo[50] = "1449304_quicksort.txt";

    quicksort(pokemon_array, 0, tamanho_array - 1);

    clock_t tempoFim = clock();
    double tempoExecucao = ((double)(tempoFim - tempoInicio) / CLOCKS_PER_SEC);
    criarLog(tempoExecucao,num_comparacoes,num_movimentacoes, nomeArquivo);

}


// QUICK SORT ----------------------------------------------------------------------------------------------------

// BUBBLE SORT ----------------------------------------------------------------------------------------------------

int compara_int(Pokemon pokemon1, Pokemon pokemon2) {
    return atoi(pokemon1.id) > atoi(pokemon2.id);
}


void bubble_sort(Pokemon *pokemons,int tamanho){
    int i;
    int j;
    for(i=0; i < tamanho - 1;i++){
        for(j = 0; j < tamanho - 1 - i; j++){
            if(compara_int(pokemons[j],pokemons[j+1]) ==1){
                swap(&pokemons[j],&pokemons[j+1]);
            }
        }
    }
}
void executarBubble(Pokemon pokemon_array[], int tamanho_array)
{   
    clock_t tempoInicio = clock();
    char nomeArquivo[50] = "1449304_bolha.txt";

    bubble_sort(pokemon_array, tamanho_array);

    clock_t tempoFim = clock();
    double tempoExecucao = ((double)(tempoFim - tempoInicio) / CLOCKS_PER_SEC);
    criarLog(tempoExecucao,num_comparacoes,num_movimentacoes, nomeArquivo);

}

// BUBBLE SORT ----------------------------------------------------------------------------------------------------


void countingSort(Pokemon pokemon_array[], int tamanho_array, int exp) {
    Pokemon *output = malloc(tamanho_array * sizeof(Pokemon));
    int count[256] = {0}; // O número máximo de habilidades

    // Armazena a contagem das habilidades
    for (int i = 0; i < tamanho_array; i++) {
        if (exp < pokemon_array[i].habilidades_elementos->contagem) {
            count[pokemon_array[i].habilidades_elementos->itens[exp][0]]++;
        }
    }

    // Faz a soma cumulativa
    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    // Monta o array de saída
    for (int i = tamanho_array - 1; i >= 0; i--) {
        if (exp < pokemon_array[i].habilidades_elementos->contagem) {
            output[count[pokemon_array[i].habilidades_elementos->itens[exp][0]] - 1] = pokemon_array[i];
            count[pokemon_array[i].habilidades_elementos->itens[exp][0]]--;
        }
    }

    // Copia o array de saída de volta ao array original
    for (int i = 0; i < tamanho_array; i++) {
        pokemon_array[i] = output[i];
    }

    free(output);
}



// INSERTION SORT ----------------------------------------------------------------------------------------------------

// Função para ordenação parcial por inserção (ordena os primeiros k elementos)
void insercao_parcial_ordenacao(Pokemon *lista_pokes, int total, int limite) {
    int atual_idx, anterior_idx;

    for (atual_idx = 1; atual_idx < total; atual_idx++) {
        Pokemon poke_atual = lista_pokes[atual_idx];
        struct tm data_atual = string_para_data(poke_atual.dataCaptura);
        anterior_idx = atual_idx - 1;

        // Move os elementos maiores para a direita
        while (anterior_idx >= 0) {
            struct tm data_anterior = string_para_data(lista_pokes[anterior_idx].dataCaptura);

            // Se a data_atual for anterior, o elemento é movido
            if (compara_datas(data_atual, data_anterior) < 0) {
                lista_pokes[anterior_idx + 1] = lista_pokes[anterior_idx];
            } else {
                break;
            }
            anterior_idx--;
        }
        lista_pokes[anterior_idx + 1] = poke_atual;  // Insere o Pokémon no lugar certo
    }
}

// Função que transforma uma string "dd/mm/yyyy" em struct tm
struct tm string_para_data(const char *data_str) {
    struct tm data_formatada = {0}; 
    int dia, mes, ano;

    // Converte a string em dia, mês e ano
    sscanf(data_str, "%d/%d/%d", &dia, &mes, &ano);

    // Preenche os campos da struct tm
    data_formatada.tm_mday = dia;
    data_formatada.tm_mon = mes - 1;  // Ajuste porque janeiro é 0
    data_formatada.tm_year = ano - 1900;  // Ajuste para anos a partir de 1900

    return data_formatada;
}


struct tm criar_data_formatada(int dia, int mes, int ano) {
    struct tm nova_data = {0};  
    nova_data.tm_mday = dia;
    nova_data.tm_mon = mes - 1;  
    nova_data.tm_year = ano - 1900; 
    return nova_data;
}

// Função para comparar duas datas
int compara_datas(struct tm data1, struct tm data2) {
    // Comparação de anos
    if (data1.tm_year < data2.tm_year) {
        return -1;
    } else if (data1.tm_year > data2.tm_year) {
        return 1;
    }

    // Comparação de meses
    if (data1.tm_mon < data2.tm_mon) {
        return -1;
    } else if (data1.tm_mon > data2.tm_mon) {
        return 1;
    }

    // Comparação de dias
    if (data1.tm_mday < data2.tm_mday) {
        return -1;
    } else if (data1.tm_mday > data2.tm_mday) {
        return 1;
    }

    // Se as datas forem iguais
    return 0;
}




// INSERTION SORT ----------------------------------------------------------------------------------------------------


// HEAP SORT ----------------------------------------------------------------------------------------------------


void swap_pokemons(Pokemon lista[], int primeiro, int segundo) {
    Pokemon auxiliar = lista[primeiro];  
    lista[primeiro] = lista[segundo];
    lista[segundo] = auxiliar;
}

int comparar_alturas(Pokemon p1, Pokemon p2) {
    float altura1 = atof(p1.altura);
    float altura2 = atof(p2.altura);

    if (altura1 != altura2) {
        return (altura1 > altura2) ? 1 : -1; 
    }
    return strcmp(p1.nomePokemon, p2.nomePokemon); 
}

void adicionar_pokemon_ao_heap(Pokemon heap[], int pos) {
    while (pos > 1 && comparar_alturas(heap[pos], heap[pos / 2]) > 0) {
        swap_pokemons(heap, pos, pos / 2);
        pos /= 2;
    }
}

bool tem_filhos(int indice, int tamanho){
    return (2 * indice <= tamanho);
}

int encontrar_maior_filho(Pokemon heap[], int indice, int tamanho) {
    if (2 * indice + 1 > tamanho) {
        return 2 * indice;  
    }
    return (comparar_alturas(heap[2 * indice], heap[2 * indice + 1]) >= 0) ? (2 * indice) : (2 * indice + 1);
}

void ajustar_heap(Pokemon heap[], int tamanho) {
    int pos = 1;
    while (tem_filhos(pos, tamanho)) {
        int filho = encontrar_maior_filho(heap, pos, tamanho);
        if (comparar_alturas(heap[pos], heap[filho]) < 0) {
            swap_pokemons(heap, pos, filho);
            pos = filho;
        } else {
            break;
        }
    }
}

void ordenar_parcialmente_heap(Pokemon lista[], int total) {
    int tamanho_heap = 0;
    Pokemon heap[28];
    
    // Inicializa o heap com os primeiros 10 elementos
    for (int i = 0; i < 10 && i < total; i++) {
        heap[i + 1] = lista[i];
        adicionar_pokemon_ao_heap(heap, i + 1);
        tamanho_heap++;
    }

    // Processa os elementos restantes
    for (int i = 10; i < total; i++) {
        if (comparar_alturas(lista[i], heap[1]) < 0) {
            heap[1] = lista[i];
            ajustar_heap(heap, 10);
        }
    }

    // Ordena o heap
    tamanho_heap = 10;
    while (tamanho_heap > 1) {
        swap_pokemons(heap, 1, tamanho_heap--);
        ajustar_heap(heap, tamanho_heap);
    }

    
    for (int i = 0; i < 10; i++) {
        lista[i] = heap[i + 1]; 
    }
}

// HEAP SORT ----------------------------------------------------------------------------------------------------


// RADIX SORT ----------------------------------------------------------------------------------------------------

void ordenacao_radix(Pokemon *pkm, int total, int tam_habilidade, int tam_nome) {
    Pokemon *buffer = (Pokemon *)malloc(total * sizeof(Pokemon));
    int indice, posicao;
    if (buffer == NULL) {
        printf("Erro na alocação de memória\n");
        return;
    }

    // Aplicando Radix Sort para o nome 
    for (posicao = tam_nome - 1; posicao >= 0; posicao--) {
        int contador[256] = {0};

        // Contagem da frequência de cada caractere no nome
        for (indice = 0; indice < total; indice++) {
            int valor_caractere = obter_valor_caractere(pkm[indice].nomePokemon, posicao);
            contador[valor_caractere]++;
        }

        // Ajuste das posições no array temporário
        for (indice = 1; indice < 256; indice++) {
            contador[indice] += contador[indice - 1];
        }

        // Coloca os Pokémon na ordem correta de acordo com o nome
        for (indice = total - 1; indice >= 0; indice--) {
            int valor_caractere = obter_valor_caractere(pkm[indice].nomePokemon, posicao);
            buffer[--contador[valor_caractere]] = pkm[indice];
        }

        // Copia o array temporário de volta para o array original
        for (indice = 0; indice < total; indice++) {
            pkm[indice] = buffer[indice];
        }
    }

    // Aplicando Radix Sort para as habilidades
    for (posicao = tam_habilidade - 1; posicao >= 0; posicao--) {
        int contador[256] = {0};

        // Contagem da frequência de cada caractere na primeira habilidade
        for (indice = 0; indice < total; indice++) {
            int valor_caractere = obter_valor_caractere(pkm[indice].habilidades_elementos->itens[0], posicao);
            contador[valor_caractere]++;
        }

        // Ajuste das posições no array temporário
        for (indice = 1; indice < 256; indice++) {
            contador[indice] += contador[indice - 1];
        }

        // Coloca os Pokémon na ordem correta de acordo com a habilidade
        for (indice = total - 1; indice >= 0; indice--) {
            int valor_caractere = obter_valor_caractere(pkm[indice].habilidades_elementos->itens[0], posicao);
            buffer[--contador[valor_caractere]] = pkm[indice];
        }

        // Copia o array temporário de volta para o array original
        for (indice = 0; indice < total; indice++) {
            pkm[indice] = buffer[indice];
        }
    }

    free(buffer);
}

// Função que retorna o valor ASCII de um caractere em uma posição específica da habilidade
int obter_valor_caractere(const char *habilidade, int posicao) {
    if (posicao < strlen(habilidade)) {
        return habilidade[posicao];  // Retorna o valor ASCII
    } else {
        return 0;  // Retorna 0 se a posição for maior que o tamanho da string
    }
}

// Função para calcular o maior comprimento de um nome
int encontrar_tam_max_nome(Pokemon *pkm, int total) {
    int max_comprimento = 0, indice;
    for (indice = 0; indice < total; indice++) {
        int comprimento = strlen(pkm[indice].nomePokemon);
        if (comprimento > max_comprimento) {
            max_comprimento = comprimento;
        }
    }
    return max_comprimento;
}

// Função para calcular o maior comprimento de uma habilidade
int encontrar_tam_max_habilidade(Pokemon *pkm, int total) {
    int max_comprimento = 0, indice;
    for (indice = 0; indice < total; indice++) {
        int comprimento = strlen(pkm[indice].habilidades_elementos->itens[0]);
        if (comprimento > max_comprimento) {
            max_comprimento = comprimento;
        }
    }
    return max_comprimento;
}

// RADIX SORT ----------------------------------------------------------------------------------------------------

// CRIAR LOG -------------------------------------------------------------------------------------------------------------------
 // Não sei o porquê, mas o tempo de execução não está sendo registrado
 // Pelo que eu entendi, fiz certo em fazer o clock inicial e o final, subtrair eles e dividir pelo CLOCKS_PER_SEC
 // para achar o segundos. Depois multiplicamos por 1000 para transformar em milissegundos

void criarLog(double tempoExecucao, int comparacoes, int movimentacoes, const char *arquivo)  
{
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de log!\n");
        return;
    }
     fprintf(fp, "Matrícula: 1449304");
    fprintf(fp, "Tempo de execução: %f segundos\n", tempoExecucao * 1000.0);
    fprintf(fp, "Comparações: %d\n", comparacoes);
    fprintf(fp, "Movimentações: %d\n", movimentacoes);
    fclose(fp);
}

// CRIAR LOG -------------------------------------------------------------------------------------------------------------------




// MÉTODOS DE LISTA ----------------------------------------------------------------------------------------------------------

char* remover_espaco(char *entrada) {
    if (!entrada) return NULL;

    // Encontrar o primeiro e o último caractere não-espaço
    char *inicio = entrada;
    while (isspace((unsigned char)*inicio)) inicio++;

    char *fim = entrada + strlen(entrada) - 1;
    while (fim > inicio && isspace((unsigned char)*fim)) fim--;

    // Calcular o novo tamanho e alocar memória
    size_t tamanho = fim - inicio + 1;
    char *saida = (char*)malloc(tamanho + 1);
    if (saida) {
        strncpy(saida, inicio, tamanho);
        saida[tamanho] = '\0'; // Adiciona o terminador nulo
    }
    return saida;
}

char* extrair_sub(char *entrada, size_t inicio, size_t fim) {
    char *subcampo = NULL;
    size_t tamanho_entrada = strlen(entrada);
    if (inicio < tamanho_entrada && fim < tamanho_entrada && inicio <= fim) {
        size_t comprimento = fim - inicio + 1;
        subcampo = (char*) malloc((comprimento+1) * sizeof(char));
        if (subcampo) {
            size_t j = 0;
            for (size_t i = inicio; i <= fim; i++) {
                *(subcampo+j) = *(entrada+i);
                j++;
            }
            *(subcampo+j) = '\0';
        }
    }
    return subcampo;
}


void substituir_caracter(char *entrada, char buscar_caracter, char substituir_caracter) {
    char *ptr = strchr(entrada, buscar_caracter);
    while (ptr != NULL) {
        *ptr = substituir_caracter;
        ptr = strchr(ptr + 1, buscar_caracter);
    }
}

Lista converter_para_lista(char *string_habilidades) {
    Lista lista;
    lista.contagem = 0;

    // Remover os caracteres de formatação
    substituir_caracter(string_habilidades, '[', ' '); // Remove '['
    substituir_caracter(string_habilidades, ']', ' '); // Remove ']'
    substituir_caracter(string_habilidades, '\'', ' '); // Remove '\''

    // Debug: mostrar a string antes da conversão
    //printf("String antes da conversão: '%s'\n", string_habilidades);

    // Tokeniza a string por vírgulas
    char *token = strtok(string_habilidades, ",");
    while (token != NULL && lista.contagem < MAX_LISTA) {
        // Remove espaços em branco do início e do final
        char *habilidade = trim(token);
        if (strlen(habilidade) > 0) {
            // Debug: exibir a habilidade antes de adicionar
            //printf("Adicionando habilidade: '%s'\n", habilidade);
            // Copie a habilidade para a lista sem truncar
            strncpy(lista.itens[lista.contagem], habilidade, sizeof(lista.itens[lista.contagem]) - 1);
            lista.itens[lista.contagem][sizeof(lista.itens[lista.contagem]) - 1] = '\0'; // Garante que a string esteja terminada
            lista.contagem++; // Incrementa a contagem após adicionar a habilidade
        }
        // Pega o próximo token
        token = strtok(NULL, ",");
    }

    return lista;
}

char* trim(char* str) {
    char* end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Null terminate after the last non-space character
    *(end+1) = '\0';

    return str;
}

void adicionar_elemento(Lista *lista, const char *elemento) {
    if (lista->contagem < MAX_LISTA) {

        // printf("Adicionando habilidade: '%s'\n", elemento); // Print para ver a string que está sendo adicionada
        // Usar strncpy para evitar buffer overflow
        strncpy(lista->itens[lista->contagem], elemento, MAX_TAMANHO_HABILIDADE - 1);
        lista->itens[lista->contagem][MAX_TAMANHO_HABILIDADE - 1] = '\0'; // Garantir terminação nula
        lista->contagem++;
    } else {
        printf("Lista cheia. Não foi possível adicionar o elemento: '%s'\n", elemento);
    }
}

void exibir_elementos(Lista *lista) {
   printf("[", lista->contagem);
    for (int i = 0; i < lista->contagem; i++) {
        printf("'%s'", lista->itens[i]);
        if (i + 1 < lista->contagem) {
            printf(", ");
        }
    }
    printf("]");
}

// MÉTODOS DE LISTA ----------------------------------------------------------------------------------------------------------

// PESQUISA BINÁRIA ----------------------------------------------------------------------------------------------------------

// por algum motivo, que eu não consigo encontrar, algumas pesquisas estão erradas. Tirei por volta de 78% na questão

int pesquisa_binaria(Pokemon *pokemons, char* name, int n){
    int inicio,meio,fim;
    inicio = 0; fim = n-1;

    while(inicio <= fim){
        meio = (inicio + fim) / 2;

        incrementar_comparacao();

     int comparacao = strcmp(pokemons[meio].nomePokemon, name);
        
        if(comparacao == 0){
            return 1;  
        } 
        else if(comparacao > 0){
            fim = meio - 1;
        } 
        else {
            inicio = meio + 1;
        }
    }

    return 0;
}


// PESQUISA BINÁRIA ----------------------------------------------------------------------------------------------------------



// MÉTODOS DO POKEMON ----------------------------------------------------------------------------------------------------------

Pokemon inicializar_pokemon() {
    Pokemon pkm;
    strcpy(pkm.id, "");
    strcpy(pkm.geracao_dados, "");
    strcpy(pkm.nomePokemon, "");
    strcpy(pkm.descricaoPokemon, "");
    pkm.tipos_elementos = (Lista*) malloc(sizeof(Lista));
    pkm.tipos_elementos->contagem = 0;
    pkm.habilidades_elementos = (Lista*) malloc(sizeof(Lista));
    pkm.habilidades_elementos->contagem = 0;
    strcpy(pkm.peso, "");
    strcpy(pkm.altura, "");
    strcpy(pkm.taxaCaptura, "");
    pkm.e_lendario = falso;
    strcpy(pkm.dataCaptura, "");
    return pkm;
}

char *encontrar_separador(char **strings, const char *delimitador) {
    char *inicio = *strings;
    char *fim;

    if (inicio == NULL) {
        return NULL;
    }

    fim = strpbrk(inicio, delimitador);
    if (fim) {
        *fim = '\0';
        *strings = fim + 1;
    } else {
        *strings = NULL;
    }

    return inicio;
}

// LEITURA DO CSV 
void preencher_array_pokemons(Pokemon pokemon_array[]) {
    FILE *arquivo = fopen(ARQUIVO_CAMINHO, "r");
    if (!arquivo) {
        printf("Erro: Arquivo não encontrado\n");
        exit(1);
    }

    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, arquivo); 

    int i = 0;
    while (fgets(buffer, MAX_BUFFER, arquivo)) {
        char *inicio_partes[3] = {NULL, NULL, NULL};
        int conta_partes_inicial = 0;

        // Tokeniza a linha baseada em aspas
        char *parte = strtok(buffer, "\"");
        while (parte && conta_partes_inicial < 3) {
            inicio_partes[conta_partes_inicial++] = parte;
            parte = strtok(NULL, "\"");
        }

        char nova_linha[MAX_BUFFER];
        if (conta_partes_inicial > 2) {
            snprintf(nova_linha, MAX_BUFFER, "%s%s", inicio_partes[0], inicio_partes[2]);
        } else {
            strncpy(nova_linha, buffer, MAX_BUFFER);
        }

        char *partes[12] = {NULL};
        int conta_partes = 0;
        char *temporario = nova_linha;

        // Tokeniza a linha baseada em vírgulas
        while((parte = encontrar_separador(&temporario, ",")) != NULL && conta_partes < 12) {
            partes[conta_partes++] = parte;
        }

        if (conta_partes >= 10) {
            Pokemon pokemon_atual = inicializar_pokemon();
            strcpy(pokemon_atual.id, partes[0]);
            strcpy(pokemon_atual.geracao_dados, partes[1]);
            strcpy(pokemon_atual.nomePokemon, partes[2]);
            strcpy(pokemon_atual.descricaoPokemon, partes[3]);

            // Converte tipos
            Lista tipos_atual = converter_para_lista(partes[4]);
            if (partes[5] && strlen(partes[5]) > 0) {
                adicionar_elemento(&tipos_atual, partes[5]);
            }
            *pokemon_atual.tipos_elementos = tipos_atual;

            // Inicializa habilidades_elementos
            pokemon_atual.habilidades_elementos = (Lista *)malloc(sizeof(Lista));
            if (!pokemon_atual.habilidades_elementos) {
                printf("Erro: Falha ao alocar memória para habilidades\n");
                exit(1);
            }


            //printf("String antes da conversão: '%s'\n", inicio_partes[1]);

            // Converte e atribui habilidades
            Lista habilidades_atual = converter_para_lista(inicio_partes[1]);
            *pokemon_atual.habilidades_elementos = habilidades_atual;

            // Debug: Exibir habilidades
            //printf("Elementos da lista de habilidades:\n");
            //exibir_elementos(pokemon_atual.habilidades_elementos);
            //printf("\n");

            // Atribuindo peso, altura e outros atributos
            if (partes[7] && strlen(partes[7]) > 0) {
                strcpy(pokemon_atual.peso, partes[7]);
            } else {
                strcpy(pokemon_atual.peso, "0.0");
            }

            if (partes[8] && strlen(partes[8]) > 0) {
                strcpy(pokemon_atual.altura, partes[8]);
            } else {
                strcpy(pokemon_atual.altura, "0.0");
            }

            strcpy(pokemon_atual.taxaCaptura, partes[9]);
            pokemon_atual.e_lendario = strcmp(partes[10], "1") == 0 ? verdade : falso;

            if (conta_partes >= 12 && strlen(partes[11]) > 0) {
                strcpy(pokemon_atual.dataCaptura, partes[11]);
            }

            pokemon_array[i++] = pokemon_atual;

            if (i >= MAX_POKEMONS) {
                break;
            }
        }
    }

    fclose(arquivo);
}


// PRINT DO POKEMON
void exibir_pokemon(Pokemon pokemon) {
    printf("[#%s -> %s: %s - ", pokemon.id, pokemon.nomePokemon, pokemon.descricaoPokemon);

    if (pokemon.tipos_elementos != NULL) {
        exibir_elementos(pokemon.tipos_elementos);
    }

    printf(" - ");

    if (pokemon.habilidades_elementos != NULL) {
        exibir_elementos(pokemon.habilidades_elementos);
    }

    printf(" - %skg - %sm - %s%% - %s - %s gen]",
        pokemon.peso, pokemon.altura, pokemon.taxaCaptura,
        pokemon.e_lendario ? "true" : "false", pokemon.geracao_dados);

    char *data_sem_espaco = remover_espaco(pokemon.dataCaptura);
    if (strlen(data_sem_espaco) > 0) {
        printf(" - %s", data_sem_espaco);
    } else {
        printf(" - Data não disponível");
    }

    printf("\n");
}



int comparar_pokemon(const void *poke1, const void *poke2) {
     incrementar_comparacao();

    const Pokemon *pokemon1 = (const Pokemon *)poke1;
    const Pokemon *pokemon2 = (const Pokemon *)poke2;
    return strcmp(pokemon1->nomePokemon, pokemon2->nomePokemon);
}   

// Função para comparar dois Pokémon
int comparePokemonsAltura(Pokemon p1, Pokemon p2) {
    // Comparar alturas
    if (p1.altura != p2.altura) {
        return (p1.altura > p2.altura) - (p1.altura < p2.altura); // 1 se p1 for maior, -1 se p1 for menor
    }
    // Em caso de empate, comparar os nomes
    return strcmp(p1.nomePokemon, p2.nomePokemon);
}