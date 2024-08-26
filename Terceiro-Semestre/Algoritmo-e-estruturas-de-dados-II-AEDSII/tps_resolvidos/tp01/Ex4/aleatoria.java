import java.util.Scanner;
    import java.util.Random;


    class aleatoria
    {
        public static char gerarLetra(Random gerador) // gera letra aleatória com a seed 4
        {
            char letra = (char)('a'+(Math.abs(gerador.nextInt()) % 26));

            return letra;
        }
        public static void aleatoFrase(String frase,Random gerador) // gera 2 letras e concatena na terceira string se as letras forem compatíveis
        {   
            int i = 0;
            char letra1 = gerarLetra(gerador);
            char letra2 = gerarLetra(gerador) ;
            String resposta = "";
            
            while( i < frase.length())
            {
                if(frase.charAt(i) == letra1)
                {

                resposta = resposta + letra2;

                }else{resposta = resposta + frase.charAt(i);}

                i++;
            }

            System.out.println(resposta);


        }

        public static void main(String[] args)
        {
            String palavra1= "";
            Scanner scanner = new Scanner(System.in);
            Random gerador = new Random();
            gerador.setSeed(4);

            palavra1 = scanner.nextLine();

            while(!(palavra1.equals("FIM")))
            {   
                aleatoFrase(palavra1,gerador);
                palavra1 = scanner.nextLine();
            }

            scanner.close();
            
        }
    }