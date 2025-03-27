import java.util.*;


public class sort {


    public static ArrayList<Integer> sortEvenOdd(ArrayList<Integer> numerosPares,ArrayList<Integer> numerosImpares, int numCasos)
    {
       numerosPares.sort(null);
       numerosImpares.sort(Collections.reverseOrder());

       ArrayList<Integer> resultado = new ArrayList<>(2*numCasos);

       for(int i = 0; i < numerosPares.size(); i++)
       {
            resultado.add(numerosPares.get(i));

       }

       for(int i = 0; i < numerosImpares.size(); i++)
       {
            resultado.add(numerosImpares.get(i));
            
       }

       return resultado;

    }

    public static void main(String[] args)
    {
        int numCasos = 0;
        int numero; 

        Scanner scanner = new Scanner(System.in);

        numCasos = scanner.nextInt();

        
        ArrayList<Integer> numerosPares = new ArrayList<>(numCasos);
        ArrayList<Integer> numerosImpares = new ArrayList<>(numCasos);
    
        
        for(int i = 0; i < numCasos; i++)
        {
            numero = scanner.nextInt();

            if(numero%2 == 0)
            {
                numerosPares.add(numero);
            }
            else{numerosImpares.add(numero);}
        }

        
        ArrayList<Integer> resultado = new ArrayList<>(2*numCasos);

        resultado = sortEvenOdd(numerosPares,numerosImpares, numCasos);

        for(int i = 0; i < resultado.size(); i++)
        {
            System.out.println(resultado.get(i));
        }


    }
    
}