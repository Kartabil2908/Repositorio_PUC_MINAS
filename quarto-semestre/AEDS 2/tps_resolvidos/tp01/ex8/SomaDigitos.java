package ex8;

import java.util.Scanner;

public class SomaDigitos {
    public static int somarDigitos(int num) {
        if (num == 0) {
            return 0;
        }
        return (num % 10) + somarDigitos(num / 10);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        String s;
        
        s = scanner.nextLine();

        while (!s.equals("FIM")) {

            int num = Integer.parseInt(s); 
            int soma = somarDigitos(num); 

            System.out.println(soma);
            
            s = scanner.nextLine();
        }

        scanner.close();
    }
}
