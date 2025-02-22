package ex4;

import java.util.Random;
import java.util.Scanner;

public class Aleatorio {

   
    public static void trocarLetras(String Entrada) {
        Random gerador = new Random();

      
        gerador.setSeed(4);

        
        char letra1 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));
        char letra2 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));

       
        char[] fraseEntrada = Entrada.toCharArray();

     
        for (int i = 0; i < fraseEntrada.length; i++) {
            if (fraseEntrada[i] == letra1) {
                fraseEntrada[i] = letra2;
            }
        }


        System.out.println(new String(fraseEntrada));
    }

    public static void main(String[] args) {
        String fraseEntrada;

        
        Scanner scanner = new Scanner(System.in);

    
        fraseEntrada = scanner.nextLine();

        while (!fraseEntrada.equals("FIM")) {
            trocarLetras(fraseEntrada);  
            fraseEntrada = scanner.nextLine();
        }

        scanner.close();
    }
}
