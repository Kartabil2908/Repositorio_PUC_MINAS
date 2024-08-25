package Ex3; // Tirar isso quando colocar no verde, pois está dando problema

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;

public class Cesar 
{

    
    private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in, Charset.forName("ISO-8859-1")));
    private static String charset = "ISO-8859-1"; 
    
    public static void println(int x){
        try {
           PrintStream out = new PrintStream(System.out, true, charset);
           out.println(x);
        }catch(UnsupportedEncodingException e){ System.out.println("Erro: charset invalido"); }
     }
  
     public static void println(float x){
        try {
           PrintStream out = new PrintStream(System.out, true, charset);
           out.println(x);
        }catch(UnsupportedEncodingException e){ System.out.println("Erro: charset invalido"); }
     }
     
     public static void println(double x){
        try {
           PrintStream out = new PrintStream(System.out, true, charset);
           out.println(x);
        }catch(UnsupportedEncodingException e){ System.out.println("Erro: charset invalido"); }
     }
  
     public static void println(String x){
        try {
           PrintStream out = new PrintStream(System.out, true, charset);
           out.println(x);
        }catch(UnsupportedEncodingException e){ System.out.println("Erro: charset invalido"); }
     }
  
     public static void println(boolean x){
        try {
           PrintStream out = new PrintStream(System.out, true, charset);
           out.println(x);
        }catch(UnsupportedEncodingException e){ System.out.println("Erro: charset invalido"); }
     }
  
     public static void println(char x){
        try {
           PrintStream out = new PrintStream(System.out, true, charset);
           out.println(x);
        }catch(UnsupportedEncodingException e){ System.out.println("Erro: charset invalido"); }
     }
  



     public static String readLine(){
      String s = "";
      char tmp;
      try{
         do{
            tmp = (char)in.read();
            if(tmp != '\n' && tmp != 13){
               s += tmp;
            }
         }while(tmp != '\n');
      }catch(IOException ioe){
         System.out.println("lerPalavra: " + ioe.getMessage());
      }
      return s;
   }

   public static String readLine(String str){
      try {
         PrintStream out = new PrintStream(System.out, true, charset);
         out.print(str);
      }catch(UnsupportedEncodingException e){ System.out.println("Erro: charset invalido"); }
      return readLine();
   }


    void cifraCesar(String palavra) 
    {
        String palavra2 = "";
        int tamanho1 = palavra.length();
        
        for (int i = 0; i < tamanho1; i++)
        {
            char letra = (char)(palavra.charAt(i) + 3);



            palavra2 += letra;
        }

        // Use MyIO para imprimir o resultado
       println(palavra2);
    }

    public static void main(String[] args)
    {
        Cesar cesar = new Cesar();
        String palavra = ""; 

        palavra = readLine(); 
        
        while(!(palavra.equals("FIM")))
        {
    
            cesar.cifraCesar(palavra);
            palavra = readLine(); 
        }
    }
}

