//judge.beecrowd.com/en/problems/view/1252

import java.util.*;

public class sort
{
    public static Comparator<Integer> comparador(int modulo)
    {
        return new Comparator<Integer>() {

            public int compare(Integer a, Integer b) {
                int modA = a % modulo;
                int modB = b % modulo;
                
                if (modA != modB) {
                    return Integer.compare(modA, modB);
                }
                
                if (a % 2 != 0 && b % 2 == 0) {
                    return -1;
                } else if (a % 2 == 0 && b % 2 != 0) {
                    return 1;
                } else if (a % 2 != 0 && b % 2 != 0) {
                    return Integer.compare(b, a);
                } else {
                    return Integer.compare(a, b);
                }
            }

        };
    }

    public static void sortsort(ArrayList<Integer> lista, int modulo)
    {

        Collections.sort(lista, comparador(modulo));

    }

    public static void preencherlista(ArrayList<Integer> lista, int numeroCasos, Scanner scanner)
    {
        for(int i = 0; i < numeroCasos;i++)
        {
            lista.add(scanner.nextInt());
        }
    }
    public static void main(String[] args)
    {
        Scanner scanner =  new Scanner(System.in);

        String[] entrada = new String[2]; 

        entrada = scanner.nextLine().split(" ");

        int numeroCasos = Integer.parseInt(entrada[0]);
        int modulo = Integer.parseInt(entrada[1]);

        ArrayList<Integer> lista = new ArrayList<Integer>();

        preencherlista(lista, numeroCasos, scanner);

        sortsort(lista, modulo);





       
    }
}