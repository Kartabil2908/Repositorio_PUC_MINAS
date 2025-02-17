/*
 * beecrowd problem -> https://judge.beecrowd.com/en/problems/view/1253
 * @author Bernardo Ladeira Borges Kartabil
 * 07/02/2025
 */

package CifraCesar;

import java.util.Scanner;

public class Cifra {

    public static StringBuilder decodificar(String palavra, int shift) {
        StringBuilder saida = new StringBuilder();

        for (int i = 0; i < palavra.length(); i++) {
            saida.append((char) ((palavra.charAt(i) - 'A' - shift + 26) % 26 + 'A'));
        }

        return saida;
    }

    public static void main(String[] args) {

        int numTestes;
        String palavra;
        int shift;

        Scanner scanner = new Scanner(System.in);

        numTestes = scanner.nextInt();
        scanner.nextLine();

        for (int i = 0; i < numTestes; i++) {
            palavra = scanner.nextLine();
            shift = scanner.nextInt();
            scanner.nextLine();

            StringBuilder saida = decodificar(palavra, shift);

            System.out.println(saida);
        }

        scanner.close();
    }
}
