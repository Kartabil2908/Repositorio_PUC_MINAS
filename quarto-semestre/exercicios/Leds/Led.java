/*

Problem:
1168 - LED
Answer:
Accepted
Language:
Java 19 (OpenJDK 19.0.2) [+2s] {beta}
Runtime:
0.439s
File size:
1.86 KB
Memory:
-
Submission:
2/5/25, 1:49:29 PM
 */

import java.util.Scanner;

public class Led {

    public static void contarLeds(Scanner scanner) {
        String palavra = "";

        int numLeds = 0;

        palavra = scanner.nextLine();

        // percorrer a palavra encontrando os caracteres numéricos

        for (int i = 0; i < palavra.length(); i++) {
            switch (palavra.charAt(i)) {

                case '0':
                    numLeds = numLeds + 6;
                    break;

                case '1':
                    numLeds = numLeds + 2;
                    break;

                case '2':
                    numLeds = numLeds + 5;
                    break;

                case '3':
                    numLeds = numLeds + 5;
                    break;

                case '4':
                    numLeds = numLeds + 4;
                    break;

                case '5':
                    numLeds = numLeds + 5;
                    break;

                case '6':
                    numLeds = numLeds + 6;
                    break;

                case '7':
                    numLeds = numLeds + 3;
                    break;

                case '8':
                    numLeds = numLeds + 7;
                    break;

                case '9':
                    numLeds = numLeds + 6;
                    break;

            }

        }

        // printar a quantidade de Leds na tela

        System.out.println(numLeds + " leds");
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);

        // primeira linha = digitar o número de testes que o programa vai fazer

        int testes = 0;

        testes = scanner.nextInt();
        scanner.nextLine();

        for (int i = 0; i < testes; i++) {
            contarLeds(scanner);
        }
    }

}