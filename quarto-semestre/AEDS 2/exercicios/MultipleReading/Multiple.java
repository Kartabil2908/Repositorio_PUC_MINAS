package MultipleReading;

import java.util.Scanner;

public class Multiple {

    public static int multipleReading(String trace, int procs)
    {
        // read -> multiple proces in a clock
        // write -> 1 clock per write


        int i = 0;
        int numR = 0;        

        while(trace.charAt(i) != '\n')
        {
            if(trace.charAt(i) == 'R')
            {
                numR = numR + 1;
            }
        }


        return numClocks;
    }

    public static void main(String[] args)
    {
        String trace;
        int procs = 0;
        int resp = 0;

        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNext())
        {
            resp = 0;

            trace = scanner.nextLine();
            procs = scanner.nextInt();

            resp = multipleReading(trace, procs);




        }

    }
    
}
