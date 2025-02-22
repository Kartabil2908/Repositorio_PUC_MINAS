package ex9;

import java.util.Scanner;

public class Anagrama {


    private static void swap(char[] arr, int i, int menor) { // swap
        char temp = arr[i];
        arr[i] = arr[menor];
        arr[menor] = temp;
    }

    public static String ordenarPalavra(String palavra) { 
        char[] array = palavra.toCharArray();
        int tamanho = palavra.length();


        for (int i = 0; i < tamanho - 1; i++) { // usei o selection sort
            int menor = i;
            for (int j = i + 1; j < tamanho; j++) { 
                if (array[menor] > array[j]) {
                    menor = j;
                }
            }
            swap(array, i, menor);
        }


        return String.valueOf(array);
    }

 
    public static void verificarAnagrama(String palavra1, String palavra2) {

        // verifica se a palavra tem o mesmo tamanho e depois ordena
        if (palavra1.length() == palavra2.length()) {
         
            palavra1 = ordenarPalavra(palavra1);
            palavra2 = ordenarPalavra(palavra2);

         
            if (palavra1.equals(palavra2)) {
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }
        } else {
            System.out.println("NAO");
        }
    }

    public static void main(String[] args) {
        String palavra1;
        String palavra2;
        Scanner scanner = new Scanner(System.in);

      
        palavra1 = scanner.nextLine();

      
        while (!palavra1.equals("FIM")) {
            palavra2 = scanner.nextLine();
            verificarAnagrama(palavra1, palavra2);

        
            palavra1 = scanner.nextLine();
        }

        scanner.close();
    }
}
