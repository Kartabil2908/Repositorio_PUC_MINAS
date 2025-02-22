package ex10;

import java.util.Scanner;

public class ContagemPalavras 
{
    public static int contarPalavras(String frase)
    {
        int contadorEspaços = 0;
        int numPalavras;

        for(int i = 0; i < frase.length(); i++)
        {
            if(frase.charAt(i) == ' ')
            {
                contadorEspaços++;
            }
        }

        numPalavras = contadorEspaços + 1;

        return numPalavras;
    }

    public static void main(String[] args)
    {
        String frase;
        int numPalavras;

        Scanner scanner = new Scanner(System.in);

        frase = scanner.nextLine();

        while(!frase.equals("FIM"))
        {
            numPalavras = contarPalavras(frase);
            System.out.println(numPalavras);
            frase = scanner.nextLine();

        }

        scanner.close();
    }
    
}
