import java.util.Scanner;

class LAB01Q02
{
    public static boolean VerificarLetraMaiscula(char letra)
    {
        return(letra >= 'A' && letra <= 'Z' ); // retorna verdadeiro se letra for maiúscula
    }

    public static boolean VerificarFim(String palavra)
    {
        return(palavra.length() == 3 && palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M');
    }

    public static int ContarLetrasMaiusculas(String palavra, int index) // lê de de trás pra frente
    {

        int letra = 0;

        if (index < 0)
        {
            return 0;
        }else
        {
            if (VerificarLetraMaiscula(palavra.charAt(index))) {
                letra = 1;
            }

            return letra + ContarLetrasMaiusculas(palavra, index - 1);
        }
        
    }

    public static void main(String[] args)
    {
        Scanner leitura = new Scanner(System.in);
        String palavra;
        int letraMaiuscula;

        do
        {
            palavra = leitura.nextLine();

            if (!VerificarFim(palavra)) // verifica se a palavra é FIM
            {
                letraMaiuscula = ContarLetrasMaiusculas(palavra,palavra.length() - 1);
                System.out.println(letraMaiuscula);
            }

        } while (!VerificarFim(palavra));

        leitura.close();
    }
}