import java.util.Scanner;

public class Palindromo {

    public static void verificarPalindromo(String frase) { // compara as letras da frase de forma que fiquem iguais "ao contrário"

        boolean statusPalavra = false;
        int tamanho = frase.length();

        for (int i = 0; i < tamanho; i++) {
            char letraComparada = frase.charAt(tamanho - i - 1); 

            if (frase.charAt(i) == letraComparada) { // aqui a comparação é feita
                statusPalavra = true;
            } else {
                statusPalavra = false;
                i = tamanho;
            }
        }

        if (statusPalavra == true) {
            System.out.println("SIM");
        } else {
            System.out.println("NAO");
        }
    }

    public static void main(String[] args) {
        String frase = "";
        Scanner scanner = new Scanner(System.in);

        frase = scanner.nextLine();

        while (!(frase.equals("FIM"))) {
            verificarPalindromo(frase);
            frase = scanner.nextLine();
        }

        scanner.close();
    }
}