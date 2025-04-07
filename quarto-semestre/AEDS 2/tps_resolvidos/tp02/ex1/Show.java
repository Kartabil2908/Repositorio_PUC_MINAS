package ex1;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;





public class Show
{

    private String showId;
    private String type;
    private String title;
    private ArrayList<String> director;
    private ArrayList<String> cast;
    private String country;
    private Date dateAdded;
    private int releaseYear;
    private String rating;
    private String duration;
    private ArrayList<String> listedIn;


    public String getShowId() {
        return showId;
    }
    public void setShowId(String showId) {
        this.showId = showId;
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


    // FUNÇÃO PARA LER O ARQUIVO CSV
    public static void lerCsv(Show[] catalago)
    {
        try
        {
            //abrindo o arquivo para leitura
            FileReader arquivo = new FileReader("tmp\\disneyplus.csv");
            BufferedReader leitor = new BufferedReader(arquivo);
            String showId, type, title;
            String line;
            String[] tmp = new String[4];
            
    

            
            // lendo os campos showId,type e title
            line = leitor.readLine();
            line = leitor.readLine();
            tmp = line.split(",", 4);

            showId = tmp[0];
            type = tmp[1];
            title = tmp[2];
            
            System.out.println(showId +"\n" + type +"\n" + title + "\n" + tmp[3]); // logs




            // Ler o campo director

            ArrayList<String> director = new ArrayList<String>();

            String[] tmp2 = new String[4]; // para guardar a string dos diretores

            tmp2 = tmp[3].split("\"", 3);

            //System.out.println("\n" + tmp2[1]); mostra os diretores no tmp2[1]



            
            

        
        }catch(FileNotFoundException e)
        {
            System.out.println("Arquivo não encontrado!");
        }catch(IOException a)
        {
            System.out.println("Erro!");
        }


        
    }


    public static void main(String[] args)
    {
        Show[] catalogo = new Show[1368];

        lerCsv(catalogo);

        
    }

    

}






/*
 * Anotações:
 * 
 * Tenho certeza que vou achar o show_id,type,title nas primeiras 3 vírgulas;
 * Depois, tratar o Director;
 * 
 * 
 * 
 * 
 */