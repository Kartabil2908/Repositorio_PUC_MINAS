#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOME 100
#define MAX_TYPES 2
#define MAX_ABILITIES 10
#define MAX_NAME_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 256
#define MAX_DATE_LENGTH 11 // dd/MM/yyyy
#define MAX_POKEMONS 1000

typedef struct {
    int id;
    int generation;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char types[MAX_TYPES][MAX_NAME_LENGTH];
    char abilities[MAX_ABILITIES][MAX_NAME_LENGTH];
    double weight;
    double height;
    int captureRate;
    bool isLegendary;
    char captureDate[MAX_DATE_LENGTH]; // String para a data
} Pokemon;

void initPokemon(Pokemon *pokemon) {
    pokemon->id = 0;
    pokemon->generation = 0;
    strcpy(pokemon->name, "");
    strcpy(pokemon->description, "");
    for (int i = 0; i < MAX_TYPES; i++) {
        strcpy(pokemon->types[i], "");
    }
    for (int i = 0; i < MAX_ABILITIES; i++) {
        strcpy(pokemon->abilities[i], "");
    }
    pokemon->weight = 0.0;
    pokemon->height = 0.0;
    pokemon->captureRate = 0;
    pokemon->isLegendary = false;
    strcpy(pokemon->captureDate, "");
}

void printPokemon(const Pokemon *pokemon) {
    printf("[#%d -> %s: %s - [", pokemon->id, pokemon->name, pokemon->description);
    
    // Adiciona tipos
    for (int i = 0; i < MAX_TYPES; i++) {
        if (strlen(pokemon->types[i]) > 0) {
            if (i > 0) printf(", ");
            printf("'%s'", pokemon->types[i]);
        }
    }
    
    printf("] - [");

    // Adiciona habilidades
    for (int i = 0; i < MAX_ABILITIES; i++) {
        if (strlen(pokemon->abilities[i]) > 0) {
            if (i > 0) printf(", ");
            printf("'%s'", pokemon->abilities[i]);
        }
    }

    printf("] - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n",
           pokemon->weight, pokemon->height, pokemon->captureRate,
           pokemon->isLegendary ? "true" : "false", pokemon->generation, pokemon->captureDate);
}

// Função para separar strings e criar Pokémon
void parsePokemonData(char *line, Pokemon *pokemon) {
    char *token;

    // Separa os tokens da linha
    token = strtok(line, ",");
    if (token != NULL) pokemon->id = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) pokemon->generation = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) strcpy(pokemon->name, token);

    token = strtok(NULL, ",");
    if (token != NULL) strcpy(pokemon->description, token);

    // Lida com tipos (até 2 tipos)
    for (int i = 0; i < MAX_TYPES; i++) {
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(pokemon->types[i], token);
    }

    // Lida com habilidades (até 10 habilidades)
    token = strtok(NULL, ",");
    if (token != NULL) {
        // Aqui, token é esperado como uma string com habilidades em formato de lista
        char *ability = strtok(token, "[]");
        int i = 0;
        while (ability != NULL && i < MAX_ABILITIES) {
            strcpy(pokemon->abilities[i++], ability);
            ability = strtok(NULL, ", ");
        }
    }

    token = strtok(NULL, ",");
    if (token != NULL) pokemon->weight = atof(token);

    token = strtok(NULL, ",");
    if (token != NULL) pokemon->height = atof(token);

    token = strtok(NULL, ",");
    if (token != NULL) pokemon->captureRate = atoi(token);

    token = strtok(NULL, ",");
    if (token != NULL) pokemon->isLegendary = (strcmp(token, "1") == 0);

    token = strtok(NULL, ",");
    if (token != NULL) strcpy(pokemon->captureDate, token);
}


int lerNomesEntrada(char nameEntrada[][MAX_NOME]) {
    char nome[MAX_NOME];
    int posicao = 0;

    while (1) {
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0; // Remove a nova linha

        if (strcmp(nome, "FIM") == 0) {
            break;
        }
        
        strcpy(nameEntrada[posicao], nome);
        posicao++;
    }
    return posicao; // Retorna a quantidade de nomes lidos
}

int pesquisaSequencialNameSimNao(Pokemon *pokemons, char nameEntrada[][MAX_NOME], int qtd) {
    int comparacoes = 0;
    for (int i = 0; i < qtd; i++) {
        bool resposta = false;

        for (int j = 0; j < MAX_POKEMONS; j++) {
            if (strcmp(nameEntrada[i], pokemons[j].name) == 0) {
                comparacoes++;
                printf("SIM\n");
                resposta = true;
                break; // Encerra o loop se o Pokémon foi encontrado
            }
            comparacoes++;
        }

        if (!resposta) {
            printf("NAO\n");
        }
    }
    return comparacoes;
}

int main() {
    Pokemon pokemons[MAX_POKEMONS];
    int count = 0;
    char line[512];

    // Exemplo de leitura de dados (substituir pelo seu método de leitura)
    FILE *file = fopen("tmp/pokemon.csv", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }else
    {
        printf("Abrimos o arquivo!");
    }
   
  
   

    // Lê cada linha do arquivo
    while (fgets(line, sizeof(line), file) && count < MAX_POKEMONS) {
        parsePokemonData(line, &pokemons[count]);
        count++;
    }
    fclose(file);

    // Exemplo de impressão dos Pokémons
    for (int i = 0; i < count; i++) {
        printPokemon(&pokemons[i]);
    }

    return 0;
}
