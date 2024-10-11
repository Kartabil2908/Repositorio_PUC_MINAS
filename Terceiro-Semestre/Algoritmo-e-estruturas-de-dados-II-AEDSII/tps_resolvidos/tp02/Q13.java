
import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;

class Pokemon {
    // VALORES
    private int id;
    private int generation;
    private String name = "";
    private String description = "";
    private List<String> types;
    private List<String> abilities;
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    // CONSTRUTORES
    Pokemon(int id, int gen, String name, String description, List<String> tipos, List<String> habilidades, double peso,
            double altura, int captura, boolean lendario, Date data) {
        this.id = id;
        this.generation = gen;
        this.name = name;
        this.description = description;
        this.types = tipos;
        this.abilities = habilidades;
        this.weight = peso;
        this.height = altura;
        this.captureRate = captura;
        this.isLegendary = lendario;
        this.captureDate = data;
    }

    Pokemon() {
        this(0, 0, "", "", null, null, 0.0, 0.0, 0, false, null);
    }

    // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // METODOS

    // ID
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;

    }

    // -------------------------------------------------

    // GENERATION
    public int getGeneration() {
        return generation;
    }

    public void setGeneration(int generation) {
        this.generation = generation;
    }
    // -------------------------------------------------

    // NAME
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    // -------------------------------------------------

    // DESCRIPTION
    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }
    // -------------------------------------------------

    // TYPES
    public List<String> getTypes() {
        return types;
    }

    public void setTypes(List<String> types) {
        this.types = types;
    }
    // -------------------------------------------------

    // ABILITIES
    public List<String> getAbilities() {
        return abilities;
    }

    public void setAbilities(List<String> abilities) {
        this.abilities = abilities;
    }
    // -------------------------------------------------

    // WEIGHT
    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }
    // -------------------------------------------------

    // HEIGHT
    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }
    // --------------------------------------------------------------------------

    // CAPTURE RATE
    public int getCaptureRate() {
        return captureRate;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }
    // -------------------------------------------------

    // IS LEGENDARY
    public boolean isLegendary() {
        return isLegendary;
    }

    public void setLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }
    // -------------------------------------------------

    // CAPTURE DATE
    public Date getCaptureDate() {
        return captureDate;
    }

    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }

    public String FormatarData()
    {
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        String dataFormatada;
        if (this.captureDate != null) {
            dataFormatada = sdf.format(this.captureDate);
        } else {
            dataFormatada = "0";
        }

        return dataFormatada;
    }
    // -------------------------------------------------

    public void printarPokemon() {
        // Formatação da data

        String dataFormatada = this.FormatarData();

        // Formatação da saída
        System.out.printf("[#%d -> %s: %s - [", this.id, this.name, this.description);

        // Adiciona tipos, ignorando vazios
        boolean hasTypes = false; // Flag para verificar se existe algum tipo
        for (int i = 0; i < types.size(); i++) {
            if (!types.get(i).isEmpty()) {
                if (hasTypes) {
                    System.out.printf(", "); // Adiciona vírgula se já houver um tipo
                }
                System.out.printf("'%s'", types.get(i)); // Adiciona aspas ao tipo
                hasTypes = true; // Marca que há pelo menos um tipo
            }
        }
        System.out.printf("] - [");

        // Adiciona habilidades, ignorando vazios
        boolean hasAbilities = false; // Flag para verificar se existe alguma habilidade
        for (int i = 0; i < abilities.size(); i++) {
            if (!abilities.get(i).isEmpty()) {
                if (hasAbilities) {
                    System.out.printf(", "); // Adiciona vírgula se já houver uma habilidade
                }
                System.out.printf("'%s'", abilities.get(i)); // Adiciona aspas à habilidade
                hasAbilities = true; // Marca que há pelo menos uma habilidade
            }
        }

        // Finaliza a formatação da saída
        System.out.printf("] - %.1fkg - %.1fm - %d%% - %b - %d gen] - %s%n",
                this.weight, this.height, this.captureRate,
                this.isLegendary, this.generation, dataFormatada);
    }

}

// ---------------------------------------------------------------------------------------------------------------------------------------------

// METODOS GERAIS - FORA DA CLASSE POKEMON
class Geral {

    public String[] separarTresStrings(String teste) {

        // Separando as strings

        String[] separarPrimeiraString = teste.split(",", 7);
        String[] separarStringHabilidades = separarPrimeiraString[6].split("]");

        // coloca as strings da primeira parte numa outra vaiável, pra ficar mais
        // organizado
        String[] primeiraString = new String[6];
        for (int i = 0; i < 6; i++) {
            primeiraString[i] = separarPrimeiraString[i];
        }

        // Formata as Habilidades e separa depois em vírgulas
        String habilidadeString = separarStringHabilidades[0].replaceAll("[\\[\\]'\"\\\\]", "").trim(); // [ e \\] bucam
        // os colchetes
        // [ e ]
        String[] dadosAdicionais = separarStringHabilidades[1].split(","); // \' a aspa simples ('), \" a aspa dupla
        // ("), \\\\ a barra invertida (\)

        return new String[]{
                primeiraString[0], // ID
                primeiraString[1], // Generation
                primeiraString[2], // Nome
                primeiraString[3], // Descrição
                primeiraString[4], // Tipo1
                primeiraString[5], // Tipo2
                habilidadeString, // Habilidades
                dadosAdicionais[1], // Peso (kg)
                dadosAdicionais[2], // Altura (m)
                dadosAdicionais[3], // Taxa de Captura
                dadosAdicionais[4], // É lendário
                dadosAdicionais[5] // Data da captura
        };
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------

    public void lerCsv(Pokemon[] poketeste) throws FileNotFoundException, ParseException {

        File file = new File("tmp/pokemon.csv"); // para o verde aceitar é /tmp/pokemon.csv
        Scanner scanner = new Scanner(file);
        String teste = scanner.nextLine(); // Lendo a primeira linha do arquivo, ou seja, o título
        int controle = 0;

        while (scanner.hasNextLine()) {

            teste = scanner.nextLine();
            String[] resultado = separarTresStrings(teste);

            poketeste[controle] = new Pokemon();

            // Acessando as strings separadas
            String primeiraParte1 = resultado[0];
            String primeiraParte2 = resultado[1];
            String primeiraParte3 = resultado[2];
            String primeiraParte4 = resultado[3];
            String primeiraParte5 = resultado[4];
            String primeiraParte6 = resultado[5];
            String habilidadeString = resultado[6];
            String peso = resultado[7];
            String altura = resultado[8];
            String taxaCaptura = resultado[9];
            String eLendario = resultado[10];
            String dataCaptura = resultado[11];

            List<String> habilidades = new ArrayList<>();
            String[] habilidadesArray = habilidadeString.split(", ");

            // Atribuindo os valores e convertendo eles

            for (String habilidade : habilidadesArray) {
                habilidades.add(habilidade.trim());
            }

            List<String> tipos = new ArrayList<>();
            tipos.add(primeiraParte5.trim());
            tipos.add(primeiraParte6.trim());

            try {
                poketeste[controle].setId(Integer.parseInt(primeiraParte1));
            } catch (Exception e) {
                poketeste[controle].setId(0);
            }

            poketeste[controle].setGeneration(Integer.parseInt(primeiraParte2));
            poketeste[controle].setName(primeiraParte3);
            poketeste[controle].setDescription(primeiraParte4);
            poketeste[controle].setTypes(tipos);
            poketeste[controle].setAbilities(habilidades);

            // Verificando se o peso e altura estão vazios antes de converter
            if (!peso.isEmpty()) {
                poketeste[controle].setWeight(Double.parseDouble(peso));
            } else {
                poketeste[controle].setWeight(0.0);
            }

            if (!altura.isEmpty()) {
                poketeste[controle].setHeight(Double.parseDouble(altura));
            } else {
                poketeste[controle].setHeight(0.0);
            }

            poketeste[controle].setCaptureRate(Integer.parseInt(taxaCaptura));
            poketeste[controle].setLegendary(eLendario.equals("1"));

            // Convertendo a data
            SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
            Date capturaDate = sdf.parse(dataCaptura);
            poketeste[controle].setCaptureDate(capturaDate);

            controle++;
        }

        scanner.close();
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------


    public int lerIdsEntrada(Scanner leitura, int[] identrada) {
        String texto = "";
        int posicao = 0;

        while (!texto.equals("FIM")) {
            texto = leitura.next();
            leitura.nextLine();

            if (!texto.equals("FIM")) {
                identrada[posicao] = Integer.parseInt(texto);
                posicao++;
            }
        }
        return posicao; // Retorna a quantidade de IDs lidos
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------


    public int lerNomesEntrada(Scanner leitura, String[] nameEntrada) {
        String nome = "";
        int posicao = 0;

        while (!nome.equals("FIM")) {
            nome = leitura.nextLine();

            if (!nome.equals("FIM")) {
                nameEntrada[posicao] = nome.trim();
                posicao++;
            }
        }
        return posicao; // Retorna a quantidade de nomes lidos
    }

    public int pesquisaSequencialNameSimNao(Pokemon[] pokemons, int[] identrada, String[] nameEntrada, int qtd) {
        int comparacoes = 0;
        for (int i = 0; i < qtd; i++) {
            boolean resposta = false;


            if (nameEntrada[i] != null) {
                for (Pokemon pokemon : pokemons) {
                    comparacoes++;
                    if (nameEntrada[i].equals(pokemon.getName()) && identrada[i] == pokemon.getId()) {
                        System.out.println("SIM");
                        resposta = true;
                        break; // Encerra o loop se o Pokémon foi encontrado
                    }
                }

                if (!resposta) {
                    System.out.println("NAO");
                }
            }

        }
        return comparacoes;
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------


    // ---------------------------------------------------------------------------------------------------------------------------------------------


    public void criarLog(long tempoExecucao, int comparacoes, int movimentacoes, String finaldoArquivo) { // A PARTIR DA QUESTÃO 7, SERÁ USADO ESSE
        String nomeArquivo = "1449304" + "_" + finaldoArquivo;
        try (FileWriter logWriter = new FileWriter(nomeArquivo)) {
            logWriter.write("1449304" + "\t" + comparacoes + "\t" + movimentacoes + "\t" + tempoExecucao + "ms\n");
        } catch (IOException e) {
            System.out.println("Erro ao criar o arquivo de log.");
            e.printStackTrace();
        }
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------


    public void atribuirPokemons(Pokemon[] pokemonTodo, Pokemon[] pokemonSelecionado, int[] identrada) {
        int i = 0;

        while (i < identrada.length && identrada[i] != 0) {

            boolean encontrado = false; // Flag para verificar se o Pokémon foi encontrado

            for (int j = 0; j < pokemonTodo.length; j++) {

                // Verifica se o ID do Pokémon atual corresponde ao ID de entrada
                if (pokemonTodo[j].getId() == identrada[i]) {

                    pokemonSelecionado[i] = pokemonTodo[j];
                    encontrado = true;
                }
            }

            if (!encontrado) {
                pokemonSelecionado[i] = null; // Se não encontrar, define como null
            }

            i++;
        }
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------


    public void ordenarPokemonsPorNome(Pokemon[] pokemons) {
        String matricula = "1449304";
        long tempoInicio = System.nanoTime();

        int comparacoes = 0;
        int movimentacoes = 0;

        int n = pokemons.length;
        for (int i = 0; i < n - 1; i++) {
            // Encontrar o índice do menor nome
            int minIndex = i;

            for (int j = i + 1; j < n; j++) {
                if (pokemons[j] != null && pokemons[minIndex] != null) {
                    comparacoes++;
                    if (pokemons[j].getName().compareTo(pokemons[minIndex].getName()) < 0) {
                        minIndex = j;
                    }
                }
            }

            // Trocar o Pokémon com o menor nome encontrado com o Pokémon na posição i
            if (minIndex != i) {
                Pokemon temp = pokemons[i];
                pokemons[i] = pokemons[minIndex];
                pokemons[minIndex] = temp;
                movimentacoes += 3; // CADA SWAP SÃO 3 MOVIMENTAÇÕES
            }
        }

        long tempoFim = System.nanoTime();
        long tempoExecucao = tempoFim - tempoInicio;

        criarLog(tempoExecucao, comparacoes, movimentacoes, "sequencial.txt");
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------

    public void ordenarPokemonsPorDataInsercao(Pokemon[] pokemons) {
        // Consiste em ordenar o subvetor à esquerda (ordenado) com o resto do vetor à direita (desordenado)

        int movimentacoes = 0;
        int comparacoes = 0;
        long tempoInicio = System.nanoTime();

        for (int i = 1; i < pokemons.length; i++) {
            // Armazena o Pokémon atual na parte ordenada

            Pokemon pokemonAtual = pokemons[i];
            Date chaveAtual = pokemonAtual.getCaptureDate();
            String nomeAtual = pokemonAtual.getName();

            int indiceAnterior = i - 1;

            // Move os Pokémons que têm data de captura depois da chaveAtual para a direita
            while (indiceAnterior >= 0 && (pokemons[indiceAnterior].getCaptureDate().after(chaveAtual) || (pokemons[indiceAnterior].getCaptureDate().equals(chaveAtual) &&
                    pokemons[indiceAnterior].getName().compareTo(nomeAtual) > 0))) {
                comparacoes += 2; // seria 2 se os dois tiverem a mesma data

                pokemons[indiceAnterior + 1] = pokemons[indiceAnterior];
                movimentacoes++;

                indiceAnterior--;
            }
            // Insere o Pokémon atual na posição correta
            pokemons[indiceAnterior + 1] = pokemonAtual;
            movimentacoes++;
        }
        long tempoFim = System.nanoTime();
        long tempoExecucao = tempoFim - tempoInicio;

        criarLog(tempoExecucao, comparacoes, movimentacoes, "insercao.txt");
    }

    // ---------------------------------------------------------------------------------------------------------------------------------------------

    public void countingSort(Pokemon[] pokemons, int totalPokemons) {
        int maxTaxaCaptura = 801;

        int[] contagem = new int[maxTaxaCaptura + 1]; // Array para contar as taxas de captura
        Pokemon[] resultado = new Pokemon[totalPokemons]; // Array para armazenar os Pokémons ordenados

        int totalComparacoes = 0;
        int totalMovimentacoes = 0;

        // Conta as taxas de captura
        for (int i = 0; i < totalPokemons; i++) {
            contagem[pokemons[i].getCaptureRate()]++;
            totalMovimentacoes++;
        }

        // Soma as contagens para que cada índice tenha a posição correta
        for (int i = 1; i <= maxTaxaCaptura; i++) {
            contagem[i] += contagem[i - 1];
            totalComparacoes++;
        }

        // Constrói o array de saída
        for (int i = totalPokemons - 1; i >= 0; i--) {
            int taxaCaptura = pokemons[i].getCaptureRate();
            int posicao = contagem[taxaCaptura] - 1;

            // Insere o Pokémon no array de saída
            resultado[posicao] = pokemons[i];
            contagem[taxaCaptura]--;
            totalMovimentacoes++;
        }

        // Realiza a ordenação pelo nome em caso de empate
        for (int i = 1; i < totalPokemons; i++) {
            Pokemon pokemonAtual = resultado[i];
            String nomeAtual = pokemonAtual.getName();
            int indiceAnterior = i - 1;

            // Move os Pokémons que têm taxa de captura iguais e nome maior para a direita
            while (indiceAnterior >= 0 &&
                    resultado[indiceAnterior].getCaptureRate() == pokemonAtual.getCaptureRate() &&
                    resultado[indiceAnterior].getName().compareTo(nomeAtual) > 0) {
                resultado[indiceAnterior + 1] = resultado[indiceAnterior];
                indiceAnterior--;
                totalMovimentacoes++;
            }


            resultado[indiceAnterior + 1] = pokemonAtual;
            totalMovimentacoes++;
        }

        // Copia o array de saída de volta para o array original
        for (int i = 0; i < totalPokemons; i++) {
            pokemons[i] = resultado[i];
            totalMovimentacoes++;
        }


        long tempoExecucao = System.currentTimeMillis(); // Calcule o tempo total após a execução
        criarLog(tempoExecucao, totalComparacoes, totalMovimentacoes, "countingsort.txt");
    }

    public void ordenarPokemonsPorTipo(Pokemon[] pokemons) {
        int movimentacoes = 0;
        int comparacoes = 0;
        long tempoInicio = System.nanoTime();

        // Chama o método mergesort
        pokemons = mergesort(pokemons);

        long tempoFim = System.nanoTime();
        long tempoExecucao = tempoFim - tempoInicio;

        criarLog(tempoExecucao, comparacoes, movimentacoes, "matrícula_mergesort.txt");
    }

    public Pokemon[] mergesort(Pokemon[] pokemons) {
        if (pokemons.length <= 1) {
            return pokemons; // Retorna se o array tiver 0 ou 1 elemento
        }

        int meio = pokemons.length / 2;
        Pokemon[] esquerda = new Pokemon[meio];
        Pokemon[] direita;

        if (pokemons.length % 2 == 0) {
            direita = new Pokemon[meio];
        } else {
            direita = new Pokemon[meio + 1];
        }

        // Divide o array em dois subarrays
        System.arraycopy(pokemons, 0, esquerda, 0, meio);
        System.arraycopy(pokemons, meio, direita, 0, direita.length);

        // Chama recursivamente o mergesort
        esquerda = mergesort(esquerda);
        direita = mergesort(direita);

        // Mescla os subarrays ordenados
        return merge(esquerda, direita);
    }

    public Pokemon[] merge(Pokemon[] esquerda, Pokemon[] direita) {
        Pokemon[] resultado = new Pokemon[esquerda.length + direita.length];
        int i = 0, j = 0, k = 0;

        while (i < esquerda.length && j < direita.length) {
            // Acessa o primeiro tipo de cada Pokémon (assumindo que não está vazio)
            String tipoEsquerda = esquerda[i].getTypes().get(0); // Obter o primeiro tipo da lista
            String tipoDireita = direita[j].getTypes().get(0); // Obter o primeiro tipo da lista

            // Compara os tipos e, em caso de empate, compara os nomes
            if (tipoEsquerda.compareTo(tipoDireita) < 0 ||
                    (tipoEsquerda.equals(tipoDireita) &&
                            esquerda[i].getName().compareTo(direita[j].getName()) < 0)) {
                resultado[k++] = esquerda[i++];
            } else {
                resultado[k++] = direita[j++];
            }
        }

        // Adiciona os elementos restantes da esquerda
        while (i < esquerda.length) {
            resultado[k++] = esquerda[i++];
        }

        // Adiciona os elementos restantes da direita
        while (j < direita.length) {
            resultado[k++] = direita[j++];
        }

        return resultado;
    }

}

    // ---------------------------------------------------------------------------------------------------------------------------------------------









// QUESTÕES DO TP - FAVOR RETIRAR O COMENTÁRIO PARA EXECUTAR A QUESTÃO DE SUA
// PREFERÊNCIA E MUDE O NOME DO ARQUIVO PARA Qx.java

/*public class Q01 {
    public static void main(String[] args) throws FileNotFoundException, ParseException {

      Scanner leitura = new Scanner(System.in);
        int[] identrada = new int[200];

        
        // Inicializa o array de Pokémons e carrega os dados do CSV
        Pokemon[] pokemons = new Pokemon[801];
        Geral comGeral = new Geral();
        comGeral.lerCsv(pokemons);

        int qtdIds = comGeral.lerIdsEntrada(leitura, identrada);

        for (int j = 0; j < controle; j++) {
            for (int i = 0; i < pokemons.length; i++) {
                if (pokemons[i].getId() == entrada[j]) {
                    pokemons[i].printarPokemon();
                }
            }
        }
    }
}*/


/*public class Q03 {

    public static void main(String[] args) throws FileNotFoundException, ParseException {

        Scanner leitura = new Scanner(System.in);

        int[] identrada = new int[200];
        String[] nameEntrada = new String[200];

        // Inicializa o array de Pokémons e carrega os dados do CSV
        Pokemon[] pokemons = new Pokemon[801];
        Geral comGeral = new Geral();
        comGeral.lerCsv(pokemons);

        int qtdIds = comGeral.lerIdsEntrada(leitura, identrada);
        int qtdNomes = comGeral.lerNomesEntrada(leitura, nameEntrada);




        leitura.close();



    }
}*/

/*public class Q05 {
    public static void main(String[] args) throws FileNotFoundException, ParseException {

        Scanner leitura = new Scanner(System.in);
        int[] identrada = new int[200];

        // lê o csv
        Pokemon[] pokemons = new Pokemon[801];
        Geral comGeral = new Geral();
        comGeral.lerCsv(pokemons);


        int qtdIds = comGeral.lerIdsEntrada(leitura, identrada); // Lê os ids

        Pokemon[] pokemonsSelecionados = new Pokemon[qtdIds];
        comGeral.atribuirPokemons(pokemons, pokemonsSelecionados, identrada);

        comGeral.ordenarPokemonsPorNome(pokemonsSelecionados); // ordena por seleção os nomes


        for(int i = 0; i < qtdIds; i++)
        {
            if(pokemonsSelecionados[i] != null){
            pokemonsSelecionados[i].printarPokemon();
            }
        }


    }
*/


/*public class Q07 
{
    public static void main(String[] args) throws FileNotFoundException, ParseException 
    {
        Scanner leitura = new Scanner(System.in);
        int[] identrada = new int[200];

        // lê o csv
        Pokemon[] pokemons = new Pokemon[801];
        Geral comGeral = new Geral();
        comGeral.lerCsv(pokemons);


        int qtdIds = comGeral.lerIdsEntrada(leitura, identrada); // Lê os ids

        Pokemon[] pokemonsSelecionados = new Pokemon[qtdIds];
        comGeral.atribuirPokemons(pokemons, pokemonsSelecionados, identrada);

        comGeral.ordenarPokemonsPorDataInsercao(pokemonsSelecionados);

        for(int i = 0; i < qtdIds; i++)
        {
            if(pokemonsSelecionados[i] != null){
            pokemonsSelecionados[i].printarPokemon();
            }
        }


    }
}*/


/*public class Q09
{
    public static void main(String[] args) throws FileNotFoundException, ParseException 
    {
        Scanner leitura = new Scanner(System.in);
        int[] identrada = new int[200];

        // lê o csv
        Pokemon[] pokemons = new Pokemon[801];
        Geral comGeral = new Geral();
        comGeral.lerCsv(pokemons);


        int qtdIds = comGeral.lerIdsEntrada(leitura, identrada); // Lê os ids

        Pokemon[] pokemonsSelecionados = new Pokemon[qtdIds];
        comGeral.atribuirPokemons(pokemons, pokemonsSelecionados, identrada);

        comGeral.heapSortHeight(pokemonsSelecionados);;

        for(int i = 0; i < qtdIds; i++)
        {
            if(pokemonsSelecionados[i] != null){
            pokemonsSelecionados[i].printarPokemon();
            }
        }


    }
}*/

/*public class Q11
{
    public static void main(String[] args) throws FileNotFoundException, ParseException
    {
        Scanner leitura = new Scanner(System.in);
        int[] identrada = new int[200];

        // lê o csv
        Pokemon[] pokemons = new Pokemon[801];
        Geral comGeral = new Geral();
        comGeral.lerCsv(pokemons);


        int qtdIds = comGeral.lerIdsEntrada(leitura, identrada); // Lê os ids

        Pokemon[] pokemonsSelecionados = new Pokemon[qtdIds];
        comGeral.atribuirPokemons(pokemons, pokemonsSelecionados, identrada);


        for(int i = 0; i < qtdIds; i++)
        {
            if(pokemonsSelecionados[i] != null) {
                pokemonsSelecionados[i].printarPokemon();
            }
        }


    }
}*/

public class Q13
{
    public static void main(String[] args) throws FileNotFoundException, ParseException {
        Scanner leitura = new Scanner(System.in);
        int[] identrada = new int[200];

        // lê o csv
        Pokemon[] pokemons = new Pokemon[801];
        Geral comGeral = new Geral();
        comGeral.lerCsv(pokemons);


        int qtdIds = comGeral.lerIdsEntrada(leitura, identrada); // Lê os ids

        Pokemon[] pokemonsSelecionados = new Pokemon[qtdIds];
        comGeral.atribuirPokemons(pokemons, pokemonsSelecionados, identrada);

        comGeral.mergesort(pokemonsSelecionados);
        ;

        for (int i = 0; i < qtdIds; i++) {
            if (pokemonsSelecionados[i] != null) {
                pokemonsSelecionados[i].printarPokemon();
            }
        }


    }
}

