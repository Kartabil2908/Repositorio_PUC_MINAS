package ex11;

import java.util.Scanner;

public class Substring {
    
    public static int comprimentoSubstring(String palavra) {

        int comprimentoMaximo = 0;
        int inicioDaSub = 0;
        
        
        int[] contadorDeLetras = new int[256]; // Tamanho suficiente para caracteres ASCII
        
        for (int fimDaSub = 0; fimDaSub < palavra.length(); fimDaSub++) {
            
            char letraAtual = palavra.charAt(fimDaSub);
            
            // Se o caractere já apareceu, mova o inicioDaSub para a direita
            while (contadorDeLetras[letraAtual] > 0) {
                contadorDeLetras[palavra.charAt(inicioDaSub)]--;
                inicioDaSub++;
            }
            
            // Marcar a letra atual
            contadorDeLetras[letraAtual]++;
            
            // Atualiza o comprimento máximo
            comprimentoMaximo = Math.max(comprimentoMaximo, fimDaSub - inicioDaSub + 1);
        }
        
        return comprimentoMaximo;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
    
        String linha = scanner.nextLine();

        while (!linha.equals("FIM")) {
            System.out.println(comprimentoSubstring(linha));
            linha = scanner.nextLine();
        }
        
        scanner.close();
    }
}
