import java.util.Scanner;

class LAB01Q01
{
    public static boolean VerificarLetraMaiscula(char letra)
    {
        return(letra >= 'A' && letra <= 'Z' ); // retorna verdadeiro se letra for maiúscula
    }

    public static boolean VerificarFim(String palavra)
    {
        return(palavra.length() == 3 && palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M');
    }

    public static int ContarLetrasMaiusculas(String palavra)
    {
        int tamanho = palavra.length();
        int letra = 0;

        for(int i = 0; i < tamanho; i++)
        {
            if(VerificarLetraMaiscula(palavra.charAt(i)))
            {
                letra++;
            }
        }

        return(letra);
    }

    public static void main(String[] args)
    {
        Scanner leitura = new Scanner(System.in);
        String palavra;
        int letraMaiuscula;

        do
        {
            palavra = leitura.nextLine();

            if (!VerificarFim(palavra))
            {
                letraMaiuscula = ContarLetrasMaiusculas(palavra);
                System.out.println(letraMaiuscula);
            }

        } while (!VerificarFim(palavra));

        leitura.close();
    }
}