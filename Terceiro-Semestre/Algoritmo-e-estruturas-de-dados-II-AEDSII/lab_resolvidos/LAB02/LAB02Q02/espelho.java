package LAB02Q02;
import java.util.Scanner;

public class espelho
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        int condicao = 1;

        while (condicao == 1) 
        {
            String linha = scanner.nextLine();

            if (linha.isEmpty()) 
            {
                condicao = 0;
                
            }

            Scanner linhaScanner = new Scanner(linha);

            if (linhaScanner.hasNextInt())
            {
                int inicio = linhaScanner.nextInt();

                if (linhaScanner.hasNextInt())
                {
                    int fim = linhaScanner.nextInt();

                    linhaScanner.close(); 

                    String crescente = "";

                    for (int i = inicio; i <= fim; i++)
                    {
                        crescente = crescente + i;
                    }

                    System.out.print(crescente);

                    for (int i = crescente.length() - 1; i >= 0; i--)
                    {
                        System.out.print(crescente.charAt(i));
                    }

                    System.out.println();
                }
            }

            linhaScanner.close(); 
        }

        scanner.close(); 
    }
}
