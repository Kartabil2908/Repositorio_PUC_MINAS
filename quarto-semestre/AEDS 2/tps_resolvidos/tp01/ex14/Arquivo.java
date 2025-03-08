import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class Arquivo {

    public static void main(String[] args) {
        try {
           
            RandomAccessFile arquivo = new RandomAccessFile("valores.txt", "rw");

            
            Scanner scanner = new Scanner(System.in);
            int n = scanner.nextInt();  
            scanner.nextLine();

            // Leitura dos números reais e gravação no arquivo
            for (int i = 0; i < n; i++) {
               
                String valorStr = scanner.nextLine().replace(",", "."); // Substitui vírgula por ponto porque tava dando erro no scanner
                double valor = Double.parseDouble(valorStr);  
                arquivo.writeDouble(valor); 
            }

            arquivo.close();
            scanner.close();

            arquivo = new RandomAccessFile("valores.txt", "r");

            // Mover o ponteiro para o final do arquivo
            long posicao = arquivo.length();


            // Leitura do arquivo de trás para frente
            for (int i = 0; i < n; i++) {

                // Mover o ponteiro para o valor anterior
                posicao -= 8;  // Cada valor double ocupa 8 bytes
                arquivo.seek(posicao);

    
                double valor = arquivo.readDouble();

                // Se a parte decimal for 0, exibe o valor como inteiro
                if (valor == (int) valor) {
                    System.out.println((int) valor); 
                } else {
                    System.out.println(valor); 
                }
            }

            arquivo.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
