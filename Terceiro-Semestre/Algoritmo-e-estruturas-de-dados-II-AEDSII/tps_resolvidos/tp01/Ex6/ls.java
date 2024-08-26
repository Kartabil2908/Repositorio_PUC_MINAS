package Ex6; // da problema no verde

import java.util.Scanner;

public class ls {
    public static boolean palavraVogal(String palavra) {
        int i = 0;
        boolean condicao = true;

        while (i < palavra.length()) { // verifica as vogais
            if (!(palavra.charAt(i) == 'a' || palavra.charAt(i) == 'e' || palavra.charAt(i) == 'i'
                    || palavra.charAt(i) == 'o' || palavra.charAt(i) == 'u' || palavra.charAt(i) == 'A'
                    || palavra.charAt(i) == 'E' || palavra.charAt(i) == 'I' || palavra.charAt(i) == 'O'
                    || palavra.charAt(i) == 'U')) {
                condicao = false;
                break;
            }
            i++;
        }
        return condicao;
    }

    public static boolean palavraConsoante(String palavra) { // verifica as consoantes
        boolean condicao = true;
        int i = 0;

        while (i < palavra.length() && condicao) {
            char c = palavra.charAt(i);
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                    condicao = false;
                }
            } else {
                condicao = false;
            }
            i++;
        }
        return condicao;
    }

    public static boolean palavraInt(String palavra) {
        boolean condicao;

        try {
            Integer.parseInt(palavra);
            condicao = true;
        } catch (NumberFormatException a) {
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
        } catch (NumberFormatException a) {
            condicao = false;
        }

        return condicao;
    }

    public static void verificarTodasCondicoes(String palavra) { // testa todas as condições
        String vogal = "NAO";
        String consoante = "NAO";
        String inteiro = "NAO";
        String real = "NAO";

        if (palavraVogal(palavra)) {
            vogal = "SIM";
        }
        if (palavraConsoante(palavra)) {
            consoante = "SIM";
        }
        if (palavraInt(palavra)) {
            inteiro = "SIM";
        }
        if (palavraDouble(palavra)) {
            real = "SIM";
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
