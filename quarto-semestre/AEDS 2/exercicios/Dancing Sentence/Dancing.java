import java.util.Scanner;

public class Dancing {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int flag = 1;

        while (flag == 1) {
            String frase = scanner.nextLine();

            // Se a frase estiver vazia, encerra o loop
            if (frase.isEmpty()) {
                flag = 0;
                continue;  // Pula o resto da iteração e vai para a próxima
            }

            StringBuilder fraseSaida = new StringBuilder();

            int letraStatus = 1; // começa com maiúscula

            for (int i = 0; i < frase.length(); i++) {
                if (frase.charAt(i) == ' ') {
                    fraseSaida.append(' ');  // Mantém os espaços
                } else if (letraStatus == 1) {
                    fraseSaida.append(Character.toUpperCase(frase.charAt(i)));
                    letraStatus = 0;  // Alterna para minúscula
                } else if (letraStatus == 0) {
                    fraseSaida.append(Character.toLowerCase(frase.charAt(i)));
                    letraStatus = 1;  // Alterna para maiúscula
                }
            }

            System.out.println(fraseSaida);
        }

        scanner.close();
    }

}
