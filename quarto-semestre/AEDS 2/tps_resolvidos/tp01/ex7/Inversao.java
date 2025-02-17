package ex7;

import java.util.Scanner;

public class Inversao {
    public static String inverterString(String entrada) {
        char[] entradaArray = entrada.toCharArray();
        int esquerda = 0;
        int direita = entrada.length() - 1;
        char temp;

        while (esquerda < direita) {

            // faz um swap
            temp = entradaArray[esquerda];
            entradaArray[esquerda] = entradaArray[direita];
            entradaArray[direita] = temp;

            // atualiza as posições
            esquerda++;
            direita--;
        }

        return new String(entradaArray);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String entrada = scanner.nextLine();

        while (!entrada.equals("FIM")) {
            String saida = inverterString(entrada);
            System.out.println(saida);
            entrada = scanner.nextLine(); 
        }

        scanner.close(); 
    }
}
