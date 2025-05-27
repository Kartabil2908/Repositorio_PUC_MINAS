import java.util.*;




class Pessoa
{
    public int horas;
    public int minutos;
    public int minutosRestantes;

    public Pessoa(int h, int m, int c)
    {
        this.horas = h;
        this.minutos = m;
        this.minutosRestantes = c;
    }



}

public class FilaSus
{
    public ArrayList<Pessoa> data;
    public int numCritico;

    
    public FilaSus(int numPessoas)
    {
        this.data = new ArrayList<Pessoa>(numPessoas);
        int numCritico = 0;
    }

    public FilaSus()
    {
        this.data = new ArrayList<Pessoa>();
        int numCritico = 0;
    }


    void extrair_horario()
    {
        
    }


    public static void main(String[] args)
    {
        int numPessoas = 0;
        int H = 0, M = 0, C = 0;
        String horario = "";

        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNext())
        {
            numPessoas = scanner.nextInt();

            horario = scanner.nextLine();

            extrair_horario(H,M,C);
            

        }
    }


}