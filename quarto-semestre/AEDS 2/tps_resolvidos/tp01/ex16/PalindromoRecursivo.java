package ex16;

import java.util.Scanner;

public class PalindromoRecursivo 
{

    public static boolean verificarPalindromo(String frase, int inicio, int fim)
    {
        

        if (inicio >= fim) { // no caso de "osso", o início será maior que o fim
            return true;
        }

        if (frase.charAt(inicio) != frase.charAt(fim)) {
            return false;
        }

        // Chama recursivamente para o próximo
        return verificarPalindromo(frase, inicio + 1, fim - 1);
    }
    


    public static void verificarPalindromo(String frase) { // compara as letras da frase de forma que fiquem iguais "ao contrário"

    boolean statusPalavra = verificarPalindromo(frase, 0, frase.length() - 1);

        if (statusPalavra == true) {
            System.out.println("SIM");
        } else {
            System.out.println("NAO");
        }
    }

    public static void main(String[] args) {
        String frase = "";
        Scanner scanner = new Scanner(System.in);

        frase = scanner.nextLine();

        while (!(frase.equals("FIM"))) {
            verificarPalindromo(frase);
            frase = scanner.nextLine();
        }

        scanner.close();
    }

    }

    
    



