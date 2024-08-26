import java.util.Scanner;
import java.util.Random;


class aleatoria
{


    public static void main(String[] args)
    {
        Random gerador = new Random();
        gerador.setSeed(4);
        System.out.println((char)('a'+(Math.abs(gerador.nextInt()) % 26)));

        
    }
}
