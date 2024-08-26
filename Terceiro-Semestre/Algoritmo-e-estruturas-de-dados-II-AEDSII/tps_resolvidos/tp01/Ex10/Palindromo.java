package Ex10;

import java.util.Scanner;

class Palindromo {
    public static void VerificarPalindromo(String palavra) {
        if (isPalindromo(palavra, 0, palavra.length() - 1)) {
            System.out.println("SIM");
        } else {
            System.out.println("NAO");
        }
    }

    private static boolean isPalindromo(String palavra, int esquerda, int direita) { // Tive como base a busca binária, ele verifica se é palíndromo e vai mudando as posições "esquerda + 1" e "direita - 1"
        if (esquerda >= direita) {
            return true;
        }

        if (palavra.charAt(esquerda) != palavra.charAt(direita)) {
            return false;
        }

        return isPalindromo(palavra, esquerda + 1, direita - 1);
    }

    public static void main(String[] args) {
        Scanner leitura = new Scanner(System.in);

        String palavra;

        palavra = leitura.nextLine();

        while (!(palavra.equals("FIM"))) {
            VerificarPalindromo(palavra);
            palavra = leitura.nextLine();
        }

        leitura.close();
    }
}
