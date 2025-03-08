package ex20;

import java.util.Scanner;

public class IsRecursivo {

    public static boolean isVogal(String palavra, int index) {

        // se o índice chegar no final, quer dizer que a palavra só tem vogais
        if (index >= palavra.length()) {
            return true;
        }

        char c = Character.toLowerCase(palavra.charAt(index));

        // vai retornar false para sair da cadeia de recursão
        if (!Character.isLetter(c) || (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')) {
            return false;
        }


        // vai entrar na cadeia de recursão
        return isVogal(palavra, index + 1);
    }

    // apliquei a mesma lógica nos outros

    public static boolean isConsoante(String palavra, int index) {

        if (index >= palavra.length()) {
            return true;
        }

        char c = Character.toLowerCase(palavra.charAt(index));

        if (!Character.isLetter(c) || !(c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')) {
            return false;
        }
        return isConsoante(palavra, index + 1);
    }



    public static boolean isNumeroInt(String palavra, int index) {

        if (index >= palavra.length()) {
            return true;
        }

        char c = palavra.charAt(index);

        if (!Character.isDigit(c)) {
            return false;
        }

        return isNumeroInt(palavra, index + 1);
    }

    public static boolean isNumeroReal(String palavra, int index, boolean temPontoOuVirgula, boolean temDigito) {

        if (index >= palavra.length()) {

            return temDigito && temPontoOuVirgula;
        }

        char c = palavra.charAt(index);

        if (Character.isDigit(c)) {

            return isNumeroReal(palavra, index + 1, temPontoOuVirgula, true);

        } else if ((c == '.' || c == ',') && !temPontoOuVirgula) {

            return isNumeroReal(palavra, index + 1, true, temDigito);

        } else {

            return false;
        }
    }

    public static void main(String[] args) {

        String palavra;
        Scanner scanner = new Scanner(System.in);

        palavra = scanner.nextLine();

        while (!palavra.equals("FIM")) {
            
            if (isVogal(palavra, 0)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }

            if (isConsoante(palavra, 0)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }

            if (isNumeroInt(palavra, 0)) {
                System.out.print("SIM ");
            } else {
                System.out.print("NAO ");
            }

            if (isNumeroReal(palavra, 0, false, false)) {
                System.out.print("SIM");
            } else {
                System.out.print("NAO");
            }

            System.out.println();

            palavra = scanner.nextLine();
        }

        scanner.close();
    }
}