import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.nio.charset.StandardCharsets;

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


   // ================================================== FUNÇÃO DE ORDENAÇÃO ==================================================

   public static void mergeSort(Show[] array, int esquerda, int direita) {
      if (esquerda < direita) {
          int meio = (esquerda + direita) / 2;
          mergeSort(array, esquerda, meio);
          mergeSort(array, meio + 1, direita);
          intercalar(array, esquerda, meio, direita);
      }
  }

  private static void intercalar(Show[] array, int esquerda, int meio, int direita) {
      int tamanhoEsq = meio - esquerda + 1;
      int tamanhoDir = direita - meio;

      Show[] esquerdaArray = new Show[tamanhoEsq];
      Show[] direitaArray = new Show[tamanhoDir];

      for (int i = 0; i < tamanhoEsq; i++) {
          esquerdaArray[i] = array[esquerda + i];
      }

      for (int j = 0; j < tamanhoDir; j++) {
          direitaArray[j] = array[meio + 1 + j];
      }

      int i = 0, j = 0;
      int k = esquerda;

      while (i < tamanhoEsq && j < tamanhoDir) {
          if (compararShows(esquerdaArray[i], direitaArray[j]) <= 0) {
              array[k] = esquerdaArray[i];
              i++;
          } else {
              array[k] = direitaArray[j];
              j++;
          }
          k++;
      }

      // Copia os elementos restantes
      while (i < tamanhoEsq) {
          array[k++] = esquerdaArray[i++];
      }

      while (j < tamanhoDir) {
          array[k++] = direitaArray[j++];
      }
  }

  // Função de comparação por dateAdded, e desempate por title
  private static int compararShows(Show s1, Show s2) {
      Date d1 = s1.getDateAdded();
      Date d2 = s2.getDateAdded();

      if (d1 == null && d2 == null) {
          return s1.getTitle().compareToIgnoreCase(s2.getTitle());
      } else if (d1 == null) {
          return 1; // coloca nulos no final
      } else if (d2 == null) {
          return -1;
      }

      int comparacaoData = d1.compareTo(d2);
      if (comparacaoData != 0) {
          return comparacaoData;
      }

      // Desempate por título
      return s1.getTitle().compareToIgnoreCase(s2.getTitle());
  }
   // ================================================== FUNÇÃO MAIN ==================================================
   public static void main(String[] args) {

      
      Scanner scanner = new Scanner(System.in);
      System.setOut(new PrintStream(System.out, true, StandardCharsets.UTF_8));

      int comparacoes = 0;
      int movimentacoes = 0; 
      
      Show[] todosOsShows = Show.readShowsFromCSV("../tmp/disneyplus.csv");
  

      Show[] showsFiltrados = lerEntrada(todosOsShows, scanner);
  
      mergeSort(showsFiltrados, 0, showsFiltrados.length-1);
  
      for (int i = 0; i < showsFiltrados.length; i++) {
          showsFiltrados[i].imprimir();
      }
  }
  

   
}
