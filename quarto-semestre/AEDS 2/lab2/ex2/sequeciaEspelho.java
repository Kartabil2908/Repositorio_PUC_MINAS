import java.util.*;


public class sequeciaEspelho {


    public static void espelhar(int num1, int num2, int[] espelho) {
        int j = 0;

        // Preencher a primeira parte da sequência
        for (int i = num1; i <= num2; i++) {
            espelho[j] = i;
            j++;
        }

        // Preencher a segunda parte da sequência (espelhada)
        for (int i = num2; i >= num1; i--) {
            espelho[j] = i;
            j++;
        }

        

    }

    

    public static void main(String[] args)
    {
        int num1 = 0, num2 = 0;

        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNext())
        {
            num1 = scanner.nextInt();
            num2 = scanner.nextInt();

            int r = (num2 - num1)*2 + 2;

            int[] espelho = new int[r];

            espelhar(num1,num2,espelho);

            for (int num : espelho)
            {
                System.out.print(num);
            }

            System.out.println();
            
            
        }
    }
}


/*
 * formula do número de digitos do espelho:
 * 
 * r = b - a;
 * 
 * espelho = r*2 + 2
 * 
 * 
 * 
 */
