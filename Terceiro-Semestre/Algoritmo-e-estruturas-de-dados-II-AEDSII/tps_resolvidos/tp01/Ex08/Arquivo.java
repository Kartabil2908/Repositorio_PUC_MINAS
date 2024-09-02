package Ex08;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class Arquivo {

    public static void gravarNoArquivo(String caminho) {
        try (RandomAccessFile arquivo = new RandomAccessFile(caminho, "rw");
             Scanner scanner = new Scanner(System.in)) {

            String linha;
            while (scanner.hasNextLine()) {
                linha = scanner.nextLine();
                arquivo.writeBytes(linha + "\n");
            }

        } catch (IOException e) {
            System.out.println("Houve um erro ao tentar gravar no arquivo.");
            e.printStackTrace();
        }
    }

    public static void lerArquivoDeTrasPraFrente(String caminho) {
        try (RandomAccessFile arquivo = new RandomAccessFile(caminho, "r")) {
            long tamanho = arquivo.length();
            StringBuilder linhaAtual = new StringBuilder();

            for (long posicao = tamanho - 1; posicao >= 0; posicao--) {
                arquivo.seek(posicao);
                char caractere = (char) arquivo.readByte();

                if (caractere == '\n') {
                    if (linhaAtual.length() > 0) {
                        String linha = linhaAtual.reverse().toString();
                        linha = formatarNumero(linha);
                        System.out.println(linha);
                        linhaAtual.setLength(0);
                    }
                } else {
                    linhaAtual.append(caractere);
                }
            }

            if (linhaAtual.length() > 0) {
                String linha = linhaAtual.reverse().toString();
                linha = formatarNumero(linha);
                System.out.println(linha);
            }

        } catch (IOException e) {
            System.out.println("Houve um problema ao ler o arquivo.");
            e.printStackTrace();
        }
    }

    private static String formatarNumero(String linha) {
        if (linha.startsWith(".")) {
            linha = "0" + linha;
        }

        int pontoIndex = linha.indexOf('.');
        if (pontoIndex != -1) {
            // Remove zeros no final da parte decimal
            String parteDecimal = linha.substring(pontoIndex + 1).replaceAll("0+$", "");
            linha = linha.substring(0, pontoIndex + 1) + parteDecimal;

            // Remove o ponto se a parte decimal estiver vazia
            if (linha.endsWith(".")) {
                linha = linha.substring(0, linha.length() - 1);
            }
        }

        return linha;
    }

    public static void main(String[] args) {
        String caminho = "arquivo.txt";
        gravarNoArquivo(caminho);
        lerArquivoDeTrasPraFrente(caminho);
    }
}
