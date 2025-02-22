package ex12;

import java.util.Scanner;

public class ValidacaoSenha {

    public static boolean validarSenha(String senha) {

        boolean temMaiuscula = false;
        boolean temMinuscula = false;
        boolean temNumero = false;
        boolean temCaractereEspecial = false;
        boolean tamanhoCerto = true;
        boolean resp = false;

        // Verifica se a senha tem pelo menos 8 caracteres
        if (senha.length() < 8) {

            tamanhoCerto = false;

        } else {

            // verificações
            for (int i = 0; i < senha.length(); i++) {
                char c = senha.charAt(i); 

                if (Character.isUpperCase(c)) {
                    temMaiuscula = true;
                } else if (Character.isLowerCase(c)) {
                    temMinuscula = true;
                } else if (Character.isDigit(c)) {
                    temNumero = true;
                } else if (!Character.isLetterOrDigit(c)) {
                    temCaractereEspecial = true;
                }
            }

        }

        // retorna true se tudo for verdadeiro
        if (temMaiuscula && temMinuscula && temNumero && temCaractereEspecial && tamanhoCerto) {
            resp = true;
        } else {
            resp = false;
        }

        return resp;
    }

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        String senha = scanner.nextLine();

        while (!senha.equals("FIM")) {

            if (validarSenha(senha)) {
                System.out.println("SIM");
            } else {
                System.out.println("NÃO");
            }

            senha = scanner.nextLine();
            
        }

        scanner.close();
    }
}