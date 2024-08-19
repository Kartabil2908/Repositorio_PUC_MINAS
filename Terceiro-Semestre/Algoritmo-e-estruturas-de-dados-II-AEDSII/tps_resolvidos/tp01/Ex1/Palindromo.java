import java.util.Scanner;

class Palindromo
{
    public static void VerificarPalindromo(String palavra)
    {
        int palavraTamanho = palavra.length() - 1;

        String palavra2 = "";

        for(int i = palavraTamanho; i >= 0; i --)
        {
            palavra2 = palavra2 + palavra.charAt(i);
        }
        
        if(palavra2.equals(palavra))
        {
            System.out.println("SIM");
        }else{System.out.println("NAO");}



    }

    public static void main(String[] args)
    {
     
        Scanner leitura = new Scanner(System.in);
        
        String palavra ;

        palavra = leitura.nextLine();
        
        while(!(palavra.equals("FIM")))
        {
            VerificarPalindromo(palavra);
            palavra = leitura.nextLine();
        }

        leitura.close();
        
    }
}




