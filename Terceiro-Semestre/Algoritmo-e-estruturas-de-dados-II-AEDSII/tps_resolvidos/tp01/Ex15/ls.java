package Ex15;

import java.util.Scanner;

public class ls {

    public static boolean palavraVogal(String palavra) {
        return palavraVogal(palavra, 0); // chama a outra função que tem o index como parâmentro
    }

    private static boolean palavraVogal(String palavra, int index) {
        if (index >= palavra.length()) {
            return true;
        }
        char c = palavra.charAt(index);
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' &&
            c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
            return false;
        }
        return palavraVogal(palavra, index + 1); // chama a função + 1 posicao
    }

    public static boolean palavraConsoante(String palavra) {
        return palavraConsoante(palavra, 0);
    }

    private static boolean palavraConsoante(String palavra, int index) {
        if (index >= palavra.length()) {
            return true;
        }
        char c = palavra.charAt(index);
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                return false;
            }
        } else {
            return false;
        }
        return palavraConsoante(palavra, index + 1);
    }

    public static boolean palavraInt(String palavra) {
        boolean condicao;
        try {
            Integer.parseInt(palavra);
            condicao = true;
        } catch (NumberFormatException e) {
            condicao = false;
        }
        return condicao;
    }

    public static boolean palavraDouble(String palavra) {
        boolean condicao;
        try {
            String formattedPalavra = palavra.replace(',', '.'); // troca vírgula por ponto
            Double.parseDouble(formattedPalavra);
            condicao = true;
        } catch (NumberFormatException e) {
            condicao = false;
        }
        return condicao;
    }

    public static void verificarTodasCondicoes(String palavra) { // testa todas as condições
        String vogal;
        if (palavraVogal(palavra)) {
            vogal = "SIM";
        } else {
            vogal = "NAO";
        }

        String consoante;
        if (palavraConsoante(palavra)) {
            consoante = "SIM";
        } else {
            consoante = "NAO";
        }

        String inteiro;
        if (palavraInt(palavra)) {
            inteiro = "SIM";
        } else {
            inteiro = "NAO";
        }

        String real;
        if (palavraDouble(palavra)) {
            real = "SIM";
        } else {
            real = "NAO";
        }

        System.out.println(vogal + " " + consoante + " " + inteiro + " " + real);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String palavra;

        while (!(palavra = scanner.nextLine()).equals("")) {
            verificarTodasCondicoes(palavra);
        }

        scanner.close();
    }
}