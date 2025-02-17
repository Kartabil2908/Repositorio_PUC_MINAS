import java.util.Scanner;

public class Cifra {

    public static String cifraCodificar(String frase) {
        StringBuilder resp = new StringBuilder();

        for (int i = 0; i < frase.length(); i++) {
            char cifrado = (char) (frase.charAt(i) + 3); // Aplica a cifra de César (desloca 3 posições)
            resp.append(cifrado);
        }

        return resp.toString(); // Retorna uma String em vez de StringBuilder
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String frase;

        frase = scanner.nextLine();

        while (!frase.equals("FIM")) {
            String resp = cifraCodificar(frase);
            System.out.println(resp);
            frase = scanner.nextLine();
        }

        scanner.close();
    }
}