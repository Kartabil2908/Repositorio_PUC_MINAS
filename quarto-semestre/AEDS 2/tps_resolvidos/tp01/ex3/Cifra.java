import java.util.Scanner;

public class Cifra {

    public static String cifraCodificar(String frase) {
        StringBuilder resp = new StringBuilder();

        for (int i = 0; i < frase.length(); i++) {

            char caractere = frase.charAt(i);

            if (isLetraNaoAcentuada(caractere) || caractere == ' ' || isSimbolo(caractere) || isNumero(caractere)) {

                char cifrado = (char) (caractere + 3); // Desloca o caractere em 3 posições
                resp.append(cifrado);
            } else {

                resp.append(caractere);
            }
        }

        return resp.toString();
    }

    // verifica se um caractere é uma letra não acentuada (a-z ou A-Z)
    private static boolean isLetraNaoAcentuada(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    // verifica se um caractere é um símbolo
    private static boolean isSimbolo(char c) {

        String simbolos = "!@#$%^&*()_+-=[]{}|;:'\",.<>/?`~ ";
        return simbolos.indexOf(c) != -1;
    }

     // verifica se um caractere é um número
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