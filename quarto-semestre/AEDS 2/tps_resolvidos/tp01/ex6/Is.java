package ex6;

import java.util.Scanner;

public class Is {

    public static void isVogal(String palavra) { // verifica se são letras e vogais
        palavra.toLowerCase();
        boolean resp = false;

        for (int i = 0; i < palavra.length(); i++) {
            char c = palavra.charAt(i);

            if (!Character.isLetter(c) || c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
                resp = false;
                i = palavra.length();

            } else {

                resp = true;
            }
        }

        if (resp == true) {
            System.out.print("SIM");

        } else {
            System.out.print("NAO");
        }

    }

    public static void isConsoante(String palavra) // igual o método isVogal, porém negado '!'
    {
        palavra.toLowerCase();
        boolean resp = false;

        for (int i = 0; i < palavra.length(); i++) {
            char c = palavra.charAt(i);

            if (!Character.isLetter(c) || !(c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')) {
                resp = false;
                i = palavra.length();

            } else {

                resp = true;
            }
        }

        if (resp == true) {
            System.out.print("SIM");

        } else {
            System.out.print("NAO");
        }

    }

    public static void isNumeroInt(String palavra) { // verifica se é um número inteiro

        boolean resp = false;

        for (int i = 0; i < palavra.length(); i++) {
            char c = palavra.charAt(i);

            if (Character.isDigit(c)) {
                resp = true;

            } else {

                resp = false;
                i = palavra.length();
            }
        }

        if (resp == true) {
            System.out.print("SIM");

        } else {
            System.out.print("NAO");
        }

    }

    public static void isNumeroReal(String palavra) {

        boolean temPontoOuVirgula = false;
        boolean temDigito = false;
        boolean ehNumero = true;

        for (int i = 0; i < palavra.length() && ehNumero; i++) {

            char c = palavra.charAt(i);

            if (Character.isDigit(c)) {
                temDigito = true;
            } else if ((c == '.' || c == ',') && !temPontoOuVirgula) {
                temPontoOuVirgula = true;
            } else {
                ehNumero = false;
            }
        }

        if (ehNumero && temPontoOuVirgula && temDigito) {
            System.out.print("SIM");
        } else {
            System.out.print("NAO");
        }
    }

    public static void main(String[] args) {

        String palavra;
        Scanner scanner = new Scanner(System.in);

        palavra = scanner.nextLine();

        while (!palavra.equals("FIM")) {

            isVogal(palavra);
            System.out.print(" ");
            isConsoante(palavra);
            System.out.print(" ");
            isNumeroInt(palavra);
            System.out.print(" ");
            isNumeroReal(palavra);
            System.out.println();

            palavra = scanner.nextLine();

        }

        scanner.close();
    }
}
