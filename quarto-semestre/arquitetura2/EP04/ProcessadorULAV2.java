import java.io.*;

public class ProcessadorULAV2 {
    
    // Função para retornar a expressão correspondente ao mnemônico
    public static char expressao(String mnemonico) {
        switch (mnemonico) {
            case "zeroL": return '0';      // Zero lógico
            case "umL": return '1';     // Um lógico
            case "copiaA": return '2';   // A copiaA
            case "copiaB": return '3';    // B copiaB
            case "nA": return '4';     // A negado
            case "nB": return '5';       // B negado
            case "AenB": return '6';     // A E B negado
            case "nAeB": return '7';    // A negado E B
            case "AxB": return '8';      // A XOR B
            case "nAxnB": return '9';    // A negado XOR B negado
            case "nAxnBn": return 'A';   // (A negado XOR B negado) negado
            case "AeB": return 'B';      // A E B
            case "AeBn": return 'C';    // A E B negado
            case "AoBn": return 'D';      // (A ou B) negado
            case "AoB": return 'E';     // A OU B
            case "nAonBn": return 'F';       // (A negado OU B negado) negado
            default: return 'X';         // Caso desconhecido
        }
    }

    public static String converterParaHex(String valor) {
        switch (valor) {
            case "10": return "A";
            case "11": return "B";
            case "12": return "C";
            case "13": return "D";
            case "14": return "E";
            case "15": return "F";
            default: return valor; // Retorna o próprio valor se não estiver no intervalo
        }
    }

    public static void main(String[] args) {
        // Variáveis para armazenar os valores de X, Y e W, além de A e B
        String x = "0", y = "0", w = "0", A = "0", B = "0";

        try {
            // Leitura do arquivo de entrada
            BufferedReader arquivo = new BufferedReader(new FileReader("TESTEULA.ULA"));
            BufferedWriter arquivoHex = new BufferedWriter(new FileWriter("testeula.hex"));

            String linha;
            // Lê cada linha do arquivo
            while ((linha = arquivo.readLine()) != null) {
                // Verifica se a linha contém X, Y ou W e atribui à variável correspondente
                if (linha.startsWith("A=")) {
                    x = linha.substring(2).replace(";", "");
                } else if (linha.startsWith("B=")) {
                    y = linha.substring(2).replace(";", "");
                } else if (linha.startsWith("W=")) {
                    String mnemonico = linha.substring(2).replace(";", "");


                    // Define A e B como valores baseados em X e Y
                    A = converterParaHex(x);
                    B = converterParaHex(y);

                    // Resolve a expressão de acordo com o mnemônico
                    w = String.valueOf(expressao(mnemonico));

                    // Escreve o resultado no arquivo hexadecimal
                    arquivoHex.write(A + B + w);
                    arquivoHex.newLine();
                }
            }

            // Fecha os arquivos
            arquivo.close();
            arquivoHex.close();
        } catch (IOException e) {
            System.err.println("Erro ao processar o arquivo: " + e.getMessage());
        }
    }
}
