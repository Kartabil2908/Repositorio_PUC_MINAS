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

    // Método para formatar a data de captura
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

    // Método para imprimir os detalhes do Pokémon
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

    // Método para comparar dois Pokémon por geração e nome
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

    // Método para separar as strings do CSV
    public String[] separarTresStrings(String teste) {
        // Separando as strings
        String[] separarPrimeiraString = teste.split(",", 7);
        String[] separarStringHabilidades = separarPrimeiraString[6].split("]");

        // Coloca as strings da primeira parte numa outra variável, pra ficar mais organizado
        String[] primeiraString = new String[6];
        for (int i = 0; i < 6; i++) {
            primeiraString[i] = separarPrimeiraString[i];
        }

        // Formata as habilidades e separa depois em vírgulas
        String habilidadeString = separarStringHabilidades[0].replaceAll("[\\[\\]'\"\\\\]", "").trim(); // Remove colchetes e aspas
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

    // Método para ler o CSV e preencher o array de Pokémon
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

    // Método para ler IDs de entrada
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

    // Método para ler nomes de entrada
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


    // Método para criar o arquivo de log
    public void criarLog(int numComparacoes, int numMovimentacoes) throws IOException {
            FileWriter writer = new FileWriter("1449304_arvoreBinaria.txt");
            writer.write("Matrícula: 1449304\tTempo de Execução: " + System.currentTimeMillis() + "ms " + "\tNúmero de Comparações: "+ numComparacoes + "\tNúmero de Movimentações: " + numMovimentacoes);
            writer.close();
        }
    }
    
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    
    // Classe do nó da árvore binária
    class NoRB {
        Pokemon pokemon;
        NoRB esq, dir, pai;
        boolean isRed; // Determina se o nó é vermelho (true) ou preto (false)
    
        NoRB(Pokemon pokemon) {
            this.pokemon = pokemon;
            this.esq = null;
            this.dir = null;
            this.pai = null;
            this.isRed = true; // Por padrão, novos nós são vermelhos
        }
    }
    
    

    class ArvoreRB {
        private NoRB raiz;
        private final NoRB SENTINELA; // Nó sentinela que representa folhas (é sempre preto)
    
        public int numComparacoes = 0; // Contagem de comparações
        public int numMovimentacoes = 0; // Contagem de movimentações
    
        // Construtor
        public ArvoreRB() {
            SENTINELA = new NoRB(null);
            SENTINELA.isRed = false; // Nós sentinelas são pretos
            raiz = SENTINELA; // Inicialmente, a raiz é o sentinela
        }
    
        // Método público para inserir um Pokémon
        public void inserir(Pokemon pokemon) {
            NoRB novoNo = new NoRB(pokemon);
            novoNo.esq = SENTINELA;
            novoNo.dir = SENTINELA;
            inserirRB(novoNo);
        }
    
        // Método privado para inserir um nó na árvore RB
        private void inserirRB(NoRB novoNo) {
            NoRB pai = null;
            NoRB atual = raiz;
    
            // Busca o local correto para inserir o nó
            while (atual != SENTINELA) {
                pai = atual;
                numComparacoes++;
                if (novoNo.pokemon.getName().compareTo(atual.pokemon.getName()) < 0) {
                    atual = atual.esq;
                } else {
                    atual = atual.dir;
                }
            }
    
            // Define o pai do novo nó
            novoNo.pai = pai;
    
            if (pai == null) {
                raiz = novoNo; // O novo nó é a raiz
            } else if (novoNo.pokemon.getName().compareTo(pai.pokemon.getName()) < 0) {
                pai.esq = novoNo; // Inserir como filho à esquerda
            } else {
                pai.dir = novoNo; // Inserir como filho à direita
            }
    
            numMovimentacoes++;
            novoNo.isRed = true; // Todo novo nó é vermelho inicialmente
            ajustarInsercao(novoNo);
        }
    
        // Ajusta a árvore após uma inserção para manter as propriedades da árvore RB
        private void ajustarInsercao(NoRB no) {
            while (no.pai != null && no.pai.isRed) {
                NoRB avo = no.pai.pai;
    
                // Caso o pai seja filho esquerdo do avô
                if (no.pai == avo.esq) {
                    NoRB tio = avo.dir;
    
                    if (tio.isRed) { // Caso 1: O tio é vermelho
                        no.pai.isRed = false;
                        tio.isRed = false;
                        avo.isRed = true;
                        no = avo; // Move o nó para cima
                    } else {
                        if (no == no.pai.dir) { // Caso 2: Nó é filho direito
                            no = no.pai;
                            rotacaoEsquerda(no);
                        }
                        // Caso 3: Nó é filho esquerdo
                        no.pai.isRed = false;
                        avo.isRed = true;
                        rotacaoDireita(avo);
                    }
                } else { // Caso o pai seja filho direito do avô
                    NoRB tio = avo.esq;
    
                    if (tio.isRed) { // Caso 1: O tio é vermelho
                        no.pai.isRed = false;
                        tio.isRed = false;
                        avo.isRed = true;
                        no = avo; // Move o nó para cima
                    } else {
                        if (no == no.pai.esq) { // Caso 2: Nó é filho esquerdo
                            no = no.pai;
                            rotacaoDireita(no);
                        }
                        // Caso 3: Nó é filho direito
                        no.pai.isRed = false;
                        avo.isRed = true;
                        rotacaoEsquerda(avo);
                    }
                }
            }
            raiz.isRed = false; // A raiz é sempre preta
        }
    
        // Realiza uma rotação à esquerda
        private void rotacaoEsquerda(NoRB no) {
            NoRB filhoDir = no.dir;
            no.dir = filhoDir.esq;
    
            if (filhoDir.esq != SENTINELA) {
                filhoDir.esq.pai = no;
            }
    
            filhoDir.pai = no.pai;
            if (no.pai == null) {
                raiz = filhoDir;
            } else if (no == no.pai.esq) {
                no.pai.esq = filhoDir;
            } else {
                no.pai.dir = filhoDir;
            }
    
            filhoDir.esq = no;
            no.pai = filhoDir;
            numMovimentacoes++;
        }
    
        // Realiza uma rotação à direita
        private void rotacaoDireita(NoRB no) {
            NoRB filhoEsq = no.esq;
            no.esq = filhoEsq.dir;
    
            if (filhoEsq.dir != SENTINELA) {
                filhoEsq.dir.pai = no;
            }
    
            filhoEsq.pai = no.pai;
            if (no.pai == null) {
                raiz = filhoEsq;
            } else if (no == no.pai.dir) {
                no.pai.dir = filhoEsq;
            } else {
                no.pai.esq = filhoEsq;
            }
    
            filhoEsq.dir = no;
            no.pai = filhoEsq;
            numMovimentacoes++;
        }
    
        // Método para pesquisar um Pokémon na árvore
        public boolean pesquisar(String nome) {
            NoRB atual = raiz;

            System.out.println(nome);

            System.out.print("raiz ");
            while (atual != SENTINELA) {
                numComparacoes++;
                
                if (nome.equals(atual.pokemon.getName())) {
                    System.out.println("SIM");
                    return true;
                }
    
                numComparacoes++;
                if (nome.compareTo(atual.pokemon.getName()) < 0) {

                    System.out.print("esq ");
                    atual = atual.esq;
                } else {
                    System.out.print("dir ");
                    atual = atual.dir;
                }
            }
            System.out.println("NAO");
            return false;
        }
    }
    
    
    // ---------------------------------------------------------------------------------------------------------------------------------------------
    
    public class Q04 {
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
    
            // Cria a árvore binária de busca
            ArvoreRB arvore = new ArvoreRB();
    
            // Lê os IDs dos Pokémon para inserção na árvore
            int[] ids = new int[1000];
            int numIds = geral.lerIdsEntrada(scanner, ids);
    
            // Insere os Pokémon na árvore com base nos IDs lidos
            for (int i = 0; i < numIds; i++) {
                for (Pokemon p : PokemonsTotal) {
                    if (p != null && p.getId() == ids[i]) { // Verifica ID do Pokémon
                        arvore.inserir(p); // Insere o Pokémon na árvore
                        break;
                    }
                }
            }
    
            // Lê os nomes a serem pesquisados na árvore
            String nome = scanner.nextLine();
            while (!nome.equals("FIM")) {
                arvore.pesquisar(nome); // Faz a busca e imprime o caminho
                nome = scanner.nextLine();
            }
    
            geral.criarLog(arvore.numComparacoes, arvore.numMovimentacoes);

        scanner.close();
    }
}
