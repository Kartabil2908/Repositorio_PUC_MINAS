// https://judge.beecrowd.com/en/problems/view/1069

import java.util.Scanner;

public class Diamonds {

    public static int cavar(String expressao) {
        int numDiamantes = 0; // número de diamantes
        int pilha = 0; // numero de "<" abertos

        for (int i = 0; i < expressao.length(); i++) {
            if (expressao.charAt(i) == '<') {
                pilha++;
            } else if (expressao.charAt(i) == '>' && pilha != 0) {
                numDiamantes++;
                pilha--;
            }
        }

        return numDiamantes;
    }

    public static void main(String[] args) {
        int numCasos = 0;
        int diamantes = 0;

        Scanner scanner = new Scanner(System.in);

        numCasos = scanner.nextInt();
        scanner.nextLine(); // Consome a linha em branco deixada pelo nextInt()

        for (int i = 0; i < numCasos; i++) {
            String expressao = scanner.nextLine();

            diamantes = cavar(expressao);
            System.out.println(diamantes);
        }

        scanner.close(); // Fechando o scanner
    }
}
