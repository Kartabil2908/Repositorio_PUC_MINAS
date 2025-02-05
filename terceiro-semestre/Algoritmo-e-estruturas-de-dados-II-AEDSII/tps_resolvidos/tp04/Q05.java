import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

// Classe que representa um Pokémon
class Pokemon {
    // Atributos do Pokémon
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

    // Construtor completo
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

    // Construtor padrão
    Pokemon() {
        this(0, 0, "", "", null, null, 0.0, 0.0, 0, false, null);
    }

    // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Métodos de acesso (getters e setters)

    // ID
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    // GENERATION
    public int getGeneration() {
        return generation;
    }

    public void setGeneration(int generation) {
        this.generation = generation;
    }

    // NAME
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    // DESCRIPTION
    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    // TYPES
    public List<String> getTypes() {
        return types;
    }

    public void setTypes(List<String> types) {
        this.types = types;
    }

    // ABILITIES
    public List<String> getAbilities() {
        return abilities;
    }

    public void setAbilities(List<String> abilities) {
        this.abilities = abilities;
    }

    // WEIGHT
    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    // HEIGHT
    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    // CAPTURE RATE
    public int getCaptureRate() {
        return captureRate;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    // IS LEGENDARY
    public boolean isLegendary() {
        return isLegendary;
    }

    public void setLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    // CAPTURE DATE
    public Date getCaptureDate() {
        return captureDate;
    }

    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }

    // formatar a data de captura
    public String FormatarData() {
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        String dataFormatada;
        if (this.captureDate != null) {
            dataFormatada = sdf.format(this.captureDate);
        } else {
            dataFormatada = "0";
        }

        return dataFormatada;
    }

    // imprimir os detalhes do Pokémon
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

    // comparar dois Pokémon por geração e nome
    public static int comparePokemon(Pokemon p1, Pokemon p2) {
        // Comparar pela geração
        int generationComparison = Integer.compare(p1.getGeneration(), p2.getGeneration());
        if (generationComparison != 0) {
            return generationComparison; // Retorna a comparação de geração
        }
        // Se as gerações forem iguais, comparar pelo nome
        return p1.getName().compareTo(p2.getName());
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------

// Métodos gerais - fora da classe Pokémon
class Geral {

    public static int numComparacoes = 0;
    public static int numMovimentacoes = 0;

    // separar as strings do CSV
    public String[] separarTresStrings(String teste) {
        // Separando as strings
        String[] separarPrimeiraString = teste.split(",", 7);
        String[] separarStringHabilidades = separarPrimeiraString[6].split("]");

        // Coloca as strings da primeira parte numa outra variável, pra ficar mais
        // organizado
        String[] primeiraString = new String[6];
        for (int i = 0; i < 6; i++) {
            primeiraString[i] = separarPrimeiraString[i];
        }

        // Formata as habilidades e separa depois em vírgulas
        String habilidadeString = separarStringHabilidades[0].replaceAll("[\\[\\]'\"\\\\]", "").trim(); // Remove
                                                                                                        // colchetes e
                                                                                                        // aspas
        String[] dadosAdicionais = separarStringHabilidades[1].split(","); // Separa os dados adicionais

        return new String[] {
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

    // ler o CSV e preencher o array de Pokémon
    public void lerCsv(Pokemon[] poketeste) throws FileNotFoundException, ParseException {
        File file = new File("/tmp/pokemon.csv"); // para o verde aceitar é /tmp/pokemon.csv
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

    // ler IDs de entrada
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

    // ler nomes de entrada
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

    // criar o arquivo de log
    public void criarLog(int numComparacoes, int numMovimentacoes) throws IOException {
        FileWriter writer = new FileWriter("1449304_arvoreBinaria.txt");
        writer.write("Matrícula: 1449304\tTempo de Execução: " + System.currentTimeMillis() + "ms "
                + "\tNúmero de Comparações: " + numComparacoes + "\tNúmero de Movimentações: " + numMovimentacoes);
        writer.close();
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------

class TabelaHash {
    // Constantes para tamanhos da tabela principal e área reserva
    private static final int TAMANHO_TABELA = 21;
    private static final int TAMANHO_RESERVA = 9;

    // Estruturas para armazenamento
    private Pokemon[] tabelaHashPokemon;
    private Pokemon[] areaReserva;

    // Construtor
    TabelaHash() {
        tabelaHashPokemon = new Pokemon[TAMANHO_TABELA];
        areaReserva = new Pokemon[TAMANHO_RESERVA];
    }

    // calcular o hash a partir do nome
    public int hashNome(Pokemon pokemon) {
        String nomePokemon = pokemon.getName();

        int ascii = valorAsciiString(nomePokemon); // Soma ASCII do nome
        int posicao = ascii % TAMANHO_TABELA; // Posição na tabela principal

        return posicao;
    }

    // somar os valores ASCII de uma string
    public int valorAsciiString(String palavra) {
        int soma = 0;

        for (int i = 0; i < palavra.length(); i++) {
            soma += (int) palavra.charAt(i);
        }

        return soma;
    }

    // inserir um Pokémon na tabela
    public boolean inserir(Pokemon pokemon) {
        int posicao = hashNome(pokemon); // Calcula o hash

        // Tenta inserir na tabela principal
        if (tabelaHashPokemon[posicao] == null) {
            tabelaHashPokemon[posicao] = pokemon;
            return true; // Inserção bem-sucedida
        }

        // Se houver colisão, tenta inserir na área de reserva
        return inserirAreaReserva(pokemon);
    }

    // inserir um Pokémon na área de reserva
    public boolean inserirAreaReserva(Pokemon pokemon) {
        for (int i = 0; i < TAMANHO_RESERVA; i++) {
            if (areaReserva[i] == null) {
                areaReserva[i] = pokemon;
                return true; // Inserção bem-sucedida
            }
        }

        // Se a área de reserva estiver cheia
        return false;
    }

    // buscar um Pokémon e retornar a saída no formato correto
    // Método atualizado para buscar Pokémon na tabela ou na reserva

public String buscarPokemon(String nome) {
    int posicao = valorAsciiString(nome) % TAMANHO_TABELA;

    // Verifica na tabela principal
    if (tabelaHashPokemon[posicao] != null && tabelaHashPokemon[posicao].getName().equals(nome)) {
        return "=> " + nome + ": (Posicao: " + posicao + ") SIM";
    }

    // Verifica na área de reserva
    for (int i = 0; i < TAMANHO_RESERVA; i++) {
        if (areaReserva[i] != null && areaReserva[i].getName().equals(nome)) {
            return "=> " + nome + ": (Posicao: " + (TAMANHO_TABELA + i) + ") SIM";
        }
    }

    // Se não encontrado
    return "=> " + nome + ": NAO";
}
   
}

// ---------------------------------------------------------------------------------------------------------------------------------------------

public class Q05 {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        Geral geral = new Geral(); // Classe de métodos auxiliares

        // Lê os Pokémons do arquivo CSV
        Pokemon[] PokemonsTotal = new Pokemon[805];
        try {
            geral.lerCsv(PokemonsTotal);
        } catch (FileNotFoundException e) {
            System.err.println("Arquivo CSV não foi encontrado.");
            e.printStackTrace();
        } catch (ParseException e) {
            System.err.println("Erro ao parsear data no CSV.");
            e.printStackTrace();
        }

        // Cria a Tabela Hash
        TabelaHash tabela = new TabelaHash();

        // Lê os IDs dos Pokémon para inserção na tabela
        int[] ids = new int[1000];
        int numIds = geral.lerIdsEntrada(scanner, ids);

        // Insere os Pokémon na tabela com base nos IDs lidos
        for (int i = 0; i < numIds; i++) {
            for (Pokemon p : PokemonsTotal) {
                if (p != null && p.getId() == ids[i]) { // Verifica ID do Pokémon
                    tabela.inserir(p); // Insere o Pokémon na tabela
                    break;
                }
            }
        }

        // Lê os nomes a serem pesquisados na tabela
        // Lê os nomes a serem pesquisados e realiza a pesquisa
        String nome = scanner.nextLine();
        while (!nome.equals("FIM")) {
            System.out.println(tabela.buscarPokemon(nome)); // Realiza a busca e exibe o resultado
            nome = scanner.nextLine(); // Lê o próximo nome
        }

        scanner.close();
    }
}
