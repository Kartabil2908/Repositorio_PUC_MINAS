import java.util.Scanner;

public class Algebra {


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String input = scanner.nextLine().trim();
            if (input.equals("FIM")) {
                break;
            }

            if (!input.isEmpty()) {
                try {
                    System.out.println(avaliarExpressao(input) ? "SIM" : "NÃO");
                } catch (Exception e) {
                    System.out.println("Erro ao avaliar a expressão: " + input);
                }
            }
        }

        scanner.close();
    }

    public static boolean avaliarExpressao(String expressao) {
        String[] partes = expressao.split(" ");
        if (partes.length < 3) {
            throw new IllegalArgumentException("Entrada inválida. Certifique-se de que a entrada tem o formato correto.");
        } else {
            int numeroDeVariaveis = Integer.parseInt(partes[0]);
            boolean[] valores = new boolean[numeroDeVariaveis];
            if (partes.length < numeroDeVariaveis + 2) {
                throw new IllegalArgumentException("Número de valores não corresponde ao esperado.");
            } else {
                for (int i = 0; i < numeroDeVariaveis; ++i) {
                    valores[i] = partes[i + 1].equals("1");
                }

                String expressaoBooleana = partes[numeroDeVariaveis + 1];

                for (int i = 0; i < numeroDeVariaveis; ++i) {
                    expressaoBooleana = expressaoBooleana.replaceAll("x" + i, valores[i] ? "true" : "false");
                }

                return avaliar(expressaoBooleana);
            }
        }
    }

    public static boolean avaliar(String expressao) {
        expressao = expressao.replaceAll("NOT", "!");
        expressao = expressao.replaceAll("AND", "&&");
        expressao = expressao.replaceAll("OR", "||");
        return Boolean.parseBoolean(expressao);
    }
}
