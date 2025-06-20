import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.nio.charset.StandardCharsets;


class ListaSequencial
{
   public int tamanho; // Tamanho atual da lista
   public Show[] data; // Array para armazenar os dados
   public int capacidade; // Capacidade máxima da lista

   // Construtor da lista sequencial
   public ListaSequencial(int capacidade, Show[] shows) {
      this.capacidade = capacidade;
      this.data = new Show[capacidade];
      this.tamanho = 0;

      // Popula a lista com os shows fornecidos
      for (int i = 0; i < shows.length && i < capacidade; i++) {
         data[i] = shows[i].clonar(); // Clona o show para evitar referências diretas
         tamanho++;
      }
   }

   // Método para inserir no início da lista
   public void inserirInicio(Show show) {
      if (tamanho < capacidade) {

         // Desloca os elementos para a direita
         for (int i = tamanho; i > 0; i--) {
            data[i] = data[i - 1];
         }
         data[0] = show; // Insere o novo show no início
         tamanho++;
      } else {
         System.out.println("Lista cheia, não é possível inserir no início.");
      }
   }

   // Método para inserir no final da lista
   public void inserirFim(Show show){
      if (tamanho < capacidade) {
         data[tamanho] = show; // Insere o novo show no final
         tamanho++;
      } else {
         System.out.println("Lista cheia, não é possível inserir no final.");
      }
   }

   // Método para inserir em uma posição específica
   public void inserir(Show show, int posicao) {
      if (posicao < 0 || posicao > tamanho || tamanho >= capacidade) {
         System.out.println("Posição inválida ou lista cheia.");
         return;
      }
      // Desloca os elementos para a direita
      for (int i = tamanho; i > posicao; i--) {
         data[i] = data[i - 1];
      }
      data[posicao] = show; // Insere o novo show na posição especificada
      tamanho++;
   }

// Método para remover do início da lista
   public Show removerInicio() {
      if (tamanho == 0) {
         System.out.println("Lista vazia, não é possível remover do início.");
         return null;
      }
      Show showRemovido = data[0]; // Armazena o show a ser removido

      // Desloca os elementos para a esquerda
      for (int i = 1; i < tamanho; i++) {
         data[i - 1] = data[i];
      }
      tamanho--; // Reduz o tamanho da lista
      return showRemovido; // Retorna o show removido
   }

// Método para remover do final da lista
   public Show removerFim() {
      if (tamanho == 0) {
         System.out.println("Lista vazia, não é possível remover do final.");
         return null;
      }
      tamanho--; // Reduz o tamanho da lista
      return data[tamanho]; // Retorna o show removido do final
   }

// Método para remover de uma posição específica
   public Show remover(int posicao) {
      if (posicao < 0 || posicao >= tamanho) {
         System.out.println("Posição inválida.");
         return null;
      }
      Show showRemovido = data[posicao]; // Armazena o show a ser removido

      // Desloca os elementos para a esquerda
      for (int i = posicao + 1; i < tamanho; i++) {
         data[i - 1] = data[i];
      }
      tamanho--; // Reduz o tamanho da lista
      return showRemovido; // Retorna o show removido
   }





   // Método para popular a lista com um array de shows
   public void popular(Show[] shows, Scanner scanner)
   {
      int numComandos = scanner.nextInt(); // Lê o número de comandos
      scanner.nextLine(); // Limpa o buffer do scanner

      while(numComandos > 0)
      {
         String comando = scanner.nextLine();
         String[] partes = comando.split(" "); // Divide o comando em partes

         String operacao = partes[0]; // A primeira parte é a operação
         String idShow = null; // Variável para armazenar o ID do show, inicializada como null
         int posicao = 0;




         // Determina idShow e posicao com base na operacao, verificando o tamanho de 'partes'
         if (operacao.equals("I*")) {
            if (partes.length > 2) {
               posicao = Integer.parseInt(partes[1]);
               idShow = partes[2];
            } else {
               
               numComandos--;
               continue;     // Pula para o próximo comando
            }
         } else if (operacao.equals("II") || operacao.equals("IF")) {
            if (partes.length > 1) {
               idShow = partes[1];
            } else {
               
               numComandos--;
               continue;     // Pula para o próximo comando
            }
         } else if (operacao.equals("R*")) {
            if (partes.length < 2) {

               numComandos--;
               continue;     // Pula para o próximo comando
            }
            
         }
         

         Show showEncontrado = null; 

         // Busca o show pelo ID no array de shows, somente se um idShow foi definido (para operações de inserção)
         if (idShow != null) {
            for (Show s : shows) { 
               if (s.getShowId().equals(idShow)) {
                  showEncontrado = s.clonar(); // Clona o show encontrado
                  break; // Para o loop ao encontrar o show
               }
            }
         }

         // Verifica a operação e executa a ação correspondente
         switch(operacao)
         {
            case "I*":
               inserir(showEncontrado, posicao);
               //System.out.println("(I) " + showEncontrado.getTitle() + " na posição " + posicao); // Imprime o título do show inserido

               break; 

            case "II":
               inserirInicio(showEncontrado); // Insere o show no início
               //System.out.println("(I) " + showEncontrado.getTitle() + " no início"); // Imprime o título do show inserido

               break;
            
            case "IF":
               inserirFim(showEncontrado); // Insere o show no final
               //System.out.println("(I) " + showEncontrado.getTitle() + " no final"); // Imprime o título do show inserido

               break;

            case "RI":
               Show showRemovidoInicio = removerInicio(); // Remove do início
               if (showRemovidoInicio != null) {
                  System.out.println("(R) " + showRemovidoInicio.getTitle()); // Imprime o título do show removido
               }
               break;
            
            case "RF":
               Show showRemovidoFim = removerFim(); // Remove do final
               if (showRemovidoFim != null) {
                  System.out.println("(R) " + showRemovidoFim.getTitle()); // Imprime o título do show removido
            
               }
               break;

            case "R*":
               posicao = Integer.parseInt(partes[1]); // Posição para remover
               Show showRemovido = remover(posicao); // Remove da posição especificada
               if (showRemovido != null) {
                  System.out.println("(R) " + showRemovido.getTitle()); // Imprime o título do show removido
               }
               break;

            }

         numComandos--;


      }
   }



   // Método para imprimir a lista
   public void imprimir() {
      for (int i = 0; i < tamanho; i++) {
         data[i].imprimir(); // Chama o método imprimir de cada show
      }
   }
}


public class Show {

   
   private String showId; // ID único do show
   private String type; // Tipo do conteúdo (Movie ou TV Show)
   private String title; // Título do show
   private ArrayList<String> director; // Lista de diretores
   private ArrayList<String> cast; // Lista de atores
   private String country; // País de origem
   private Date dateAdded; // Data em que foi adicionado à plataforma
   private int releaseYear; // Ano de lançamento
   private String rating; // Classificação indicativa
   private String duration; // Duração (ou temporadas)
   private ArrayList<String> listedIn; // Lista de gêneros

   // Métodos Getters e Setters

   public String getShowId() {
      return showId;
   }

   public void setShowId(String id) {
      this.showId = id;
   }

   public String getType() {
      return type;
   }

   public void setType(String type) {
      this.type = type;
   }

   public String getTitle() {
      return title;
   }

   public void setTitle(String title) {
      this.title = title;
   }

   public ArrayList<String> getDirector() {
      return director;
   }

   public void setDirector(ArrayList<String> director) {
      this.director = director;
   }

   public ArrayList<String> getCast() {
      return cast;
   }

   public void setCast(ArrayList<String> cast) {
      this.cast = cast;
   }

   public String getCountry() {
      return country;
   }

   public void setCountry(String country) {
      this.country = country;
   }

   public Date getDateAdded() {
      return dateAdded;
   }

   public void setDateAdded(Date dateAdded) {
      this.dateAdded = dateAdded;
   }

   public int getReleaseYear() {
      return releaseYear;
   }

   public void setReleaseYear(int releaseYear) {
      this.releaseYear = releaseYear;
   }

   public String getRating() {
      return rating;
   }

   public void setRating(String rating) {
      this.rating = rating;
   }

   public String getDuration() {
      return duration;
   }

   public void setDuration(String duration) {
      this.duration = duration;
   }

   public ArrayList<String> getListedIn() {
      return listedIn;
   }

   public void setListedIn(ArrayList<String> listedIn) {
      this.listedIn = listedIn;
   }

   public Show clonar() {
      Show show = new Show(); // Cria um novo objeto Show
      show.setShowId(this.showId);
      show.setType(this.type);
      show.setTitle(this.title);
      show.setDirector(new ArrayList<>(this.director)); // Copia a lista de diretores
      show.setCast(new ArrayList<>(this.cast)); // Copia a lista de atores
      show.setCountry(this.country);
      show.setDateAdded(this.dateAdded);
      show.setReleaseYear(this.releaseYear);
      show.setRating(this.rating);
      show.setDuration(this.duration);
      show.setListedIn(new ArrayList<>(this.listedIn)); // Copia a lista de gêneros
      return show; // Retorna o novo objeto Show
   }


   // ================================================== FUNÇÃO IMPRIMIR ================================================== //

   // Método responsável por imprimir todos os dados de um objeto Show formatados

   public void imprimir() {
      SimpleDateFormat dateFormat = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH); // Define formato da data

      System.out.print("=> ");

      // Impressão campo por campo com verificação de nulo

      if (showId != null) {
         System.out.print(showId + " ## "); // Imprime showId
      } else {
         System.out.print("NaN ## "); // Valor padrão
      }

      if (title != null) {
         System.out.print(title.replaceAll("\"", "").trim() + " ## "); // Remove aspas e espaços
      } else {
         System.out.print("NaN ## ");
      }

      if (type != null) {
         System.out.print(type + " ## ");
      } else {
         System.out.print("NaN ## ");
      }

      if (director != null && !director.isEmpty()) {
         System.out.print(String.join(", ", director) + " ## "); // Junta os diretores com vírgula
      } else {
         System.out.print("NaN ## ");
      }

      if (cast != null && !cast.isEmpty()) {
         System.out.print(cast + " ## "); // Lista de atores
      } else {
         System.out.print("[NaN] ## ");
      }

      if (country != null && !country.isEmpty()) {
         System.out.print(country.replaceAll("\"", "") + " ## ");
      } else {
         System.out.print("NaN ## ");
      }

      if (dateAdded != null) {
         System.out.print(dateFormat.format(dateAdded) + " ## "); // Formata data
      } else {
         System.out.print("NaN ## ");
      }

      if (releaseYear != 0) {
         System.out.print(releaseYear + " ## ");
      } else {
         System.out.print("NaN ## ");
      }

      if (rating != null && !rating.isEmpty()) {
         System.out.print(rating + " ## ");
      } else {
         System.out.print("\"NaN\" ## "); // Mantém aspas
      }

      if (duration != null && !duration.isEmpty()) {
         System.out.print(duration.replaceAll("\"", "") + " ## ");
      } else {
         System.out.print("NaN ## ");
      }

      if (listedIn != null && !listedIn.isEmpty()) {
         System.out.print("[" + String.join(", ", listedIn) + "] ##"); // Imprime gêneros entre colchetes
      } else {
         System.out.print("NaN ##");
      }

      System.out.println();
   }

   // ================================================== FUNÇÃO LER ENTRADA ================================================== //

   // método para ler e retornar os shows com base no id, fica mais fácil de
   // manipular em outras funções;
   public static Show[] lerEntrada(Show[] showCSV, Scanner scanner) {

      // Vetor temporário para armazenar os IDs digitados
      String[] tmp = new String[showCSV.length];
      int contadorEntrada = 0;

      // Lê a primeira entrada
      tmp[contadorEntrada] = scanner.nextLine();

      // Continua lendo até encontrar "FIM"
      while (!tmp[contadorEntrada].equals("FIM")) {
         contadorEntrada++;
         tmp[contadorEntrada] = scanner.nextLine();
      }

      // Cria um vetor com o número exato de entradas válidas
      String[] entrada = new String[contadorEntrada];
      for (int i = 0; i < contadorEntrada; i++) {
         entrada[i] = tmp[i];
      }

      // Cria um vetor para armazenar os shows filtrados
      Show[] showFiltrado = new Show[contadorEntrada];

      // Para cada ID de entrada, busca o Show correspondente
      for (int i = 0; i < contadorEntrada; i++) {
         String idBuscado = entrada[i].trim();

         for (Show show : showCSV) {
            if (show.getShowId().equals(idBuscado)) {
               showFiltrado[i] = show;
               break; // Para o loop interno ao encontrar o ID
            }
         }
      }

      return showFiltrado;
   }


   // ================================================== FUNÇÃO LER O CSV ================================================== //

   // Lê o arquivo CSV e cria objetos Show para cada linha
   public static Show[] readShowsFromCSV(String caminhoCSV) {
      ArrayList<Show> listaShows = new ArrayList<>(); // Lista que irá armazenar os objetos Show
      SimpleDateFormat dateFormat = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH); // Formato da data

      try (BufferedReader leitor = new BufferedReader(new InputStreamReader(new FileInputStream(caminhoCSV)))) {
         leitor.readLine(); // Ignora a primeira linha (cabeçalho)
         String linha;

         while ((linha = leitor.readLine()) != null) {
            // Expressão regular para separar campos entre vírgulas, respeitando valores
            // entre aspas
            String[] campos = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);

            Show show = new Show(); // Cria novo objeto Show

            // Preenchimento de campos com verificação de vazio
            if (!campos[0].isEmpty()) {
               show.setShowId(campos[0].trim());
            } else {
               show.setShowId("NaN");
            }

            if (!campos[1].isEmpty()) {
               show.setType(campos[1].trim());
            } else {
               show.setType("NaN");
            }

            if (!campos[2].isEmpty()) {
               show.setTitle(campos[2].replaceAll("\"", "").trim());
            } else {
               show.setTitle("NaN");
            }

            // Processamento da lista de diretores
            ArrayList<String> diretores = new ArrayList<>();
            if (!campos[3].isEmpty()) {
               for (String dir : campos[3].split(",")) {
                  diretores.add(dir.trim().replace("\"", ""));
               }
            }
            show.setDirector(diretores);

            // Processamento da lista de atores (cast)
            ArrayList<String> elenco = new ArrayList<>();
            if (!campos[4].isEmpty()) {
               for (String ator : campos[4].split(",")) {
                  elenco.add(ator.replace("\"", "").replaceAll("^\\s+", "")); // Remove só espaços do início
               }
            }

            elenco.sort((a, b) -> a.trim().compareToIgnoreCase(b.trim())); // Ordena ignorando espaços para comparar
            show.setCast(elenco); // Atribui elenco

            // Preenche o campo de país
            if (!campos[5].isEmpty()) {
               show.setCountry(campos[5].replaceAll("\"", "").trim());
            } else {
               show.setCountry("NaN");
            }

            // Tenta converter a data, tratando exceções
            try {
               if (!campos[6].trim().isEmpty()) {
                  String dataTexto = campos[6].trim().replace("\"", "");
                  Date data = dateFormat.parse(dataTexto);
                  show.setDateAdded(data);
               } else {
                  show.setDateAdded(null);
               }
            } catch (Exception e) {
               show.setDateAdded(null); // Se erro, atribui nulo
            }

            // Conversão de ano de lançamento
            try {
               if (!campos[7].isEmpty()) {
                  show.setReleaseYear(Integer.parseInt(campos[7].trim()));
               } else {
                  show.setReleaseYear(0);
               }
            } catch (Exception e) {
               show.setReleaseYear(0); // Valor padrão
            }

            // Classificação indicativa
            if (!campos[8].isEmpty()) {
               show.setRating(campos[8].replaceAll("\"", "").trim());
            } else {
               show.setRating("NaN");
            }

            // Preenchimento de duração
            if (!campos[9].isEmpty()) {
               show.setDuration(campos[9].replaceAll("\"", "").trim());
            } else {
               show.setDuration("NaN");
            }

            // Processamento da lista de gêneros
            ArrayList<String> generos = new ArrayList<>();
            if (!campos[10].isEmpty()) {
               for (String genero : campos[10].split(",")) {
                  generos.add(genero.trim().replace("\"", ""));
               }
            }
            generos.sort(null); // Ordena alfabeticamente
            show.setListedIn(generos); // Atribui lista de gêneros

            listaShows.add(show); // Adiciona à lista de objetos
         }
      } catch (Exception e) {
         e.printStackTrace(); // Em caso de erro, imprime stack trace
      }

      return listaShows.toArray(new Show[0]); // Converte lista para array

   }

   // ================================================== FUNÇÃO MAIN ==================================================
   public static void main(String[] args) {

      Scanner scanner = new Scanner(System.in);
      System.setOut(new PrintStream(System.out, true, StandardCharsets.UTF_8));

      Show[] shows = Show.readShowsFromCSV("/tmp/disneyplus.csv");

      Show[] showFiltrado = lerEntrada(shows, scanner);

      ListaSequencial lista = new ListaSequencial(1369, showFiltrado); // Cria a lista sequencial com capacidade máxima de 1368

      // Insere os shows filtrados na lista sequencial

      lista.popular(shows, scanner);

    
      
         lista.imprimir();
      

     
      
   }

   
}
