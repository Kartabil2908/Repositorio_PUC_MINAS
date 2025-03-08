package ex18;

import java.util.Scanner;

public class CifraRecursiva {

    public static String cifraCodificar(String frase) {
        return cifraCodificarRecursiva(frase, 0);
    }

   
    private static String cifraCodificarRecursiva(String frase, int index) {
        // Caso base: quando o índice atinge o final da frase, retorna uma string vazia
        if (index >= frase.length()) {
            return "";
        }

        char caractere = frase.charAt(index);
        String resultado;

        if (isLetraNaoAcentuada(caractere) || caractere == ' ' || isSimbolo(caractere) || isNumero(caractere)) {

            char cifrado = (char) (caractere + 3); // Desloca o caractere em 3 posições
            resultado = String.valueOf(cifrado);

        } else {
            resultado = String.valueOf(caractere);
        }

        
        return resultado + cifraCodificarRecursiva(frase, index + 1);
    }

    private static boolean isLetraNaoAcentuada(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    // verifica se um caractere é um símbolo
    private static boolean isSimbolo(char c) {
        String simbolos = "!@#$%^&*()_+-=[]{}|;:'\",.<>/?`~ ";
        return simbolos.indexOf(c) != -1;
    }

    private static boolean isNumero(char c) {
        String simbolos = "0123456789";
        return simbolos.indexOf(c) != -1;
    }

    public static void main(String[] args) {
        
        Scanner scanner = new Scanner(System.in, "UTF-8");
        String frase;

        frase = scanner.nextLine();

        while (!frase.equals("FIM")) {
            String resp = cifraCodificar(frase);
            System.out.println(resp);
            frase = scanner.nextLine();
        }

        scanner.close();
    }
}
