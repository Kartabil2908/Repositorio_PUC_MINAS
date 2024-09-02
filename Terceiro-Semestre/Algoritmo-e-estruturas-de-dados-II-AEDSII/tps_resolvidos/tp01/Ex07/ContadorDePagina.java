
package Ex07;



import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ContadorDePagina {

    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

       
        Pattern padraoBr = Pattern.compile("<br>");
        Pattern padraoTable = Pattern.compile("<table>");

        boolean continuar = true; 

        while (continuar) {
            String linha = entrada.nextLine();

            if (linha.equals("FIM")) {
                continuar = false;
            } else {
              
                String[] partes = linha.split(" ");
                if (partes.length >= 2) {
                    String enderecoWeb = partes[0];
                    StringBuilder nomePagina = new StringBuilder();
                    for (int i = 1; i < partes.length; i++) {
                        nomePagina.append(partes[i]).append(" ");
                    }

                 
                    if (nomePagina.length() > 0) {
                        nomePagina.setLength(nomePagina.length() - 1);
                    }

                   
                    String textoCompleto = (enderecoWeb + " " + nomePagina).toLowerCase();

                    
                    int[] contagemVogais = new int[22]; 
                    int contagemConsoantes = 0;
                    int contagemBr = 0;
                    int contagemTable = 0;

                 
                    for (char c : textoCompleto.toCharArray()) {
                        switch (c) {
                            case 'a': contagemVogais[0]++; break;
                            case 'e': contagemVogais[1]++; break;
                            case 'i': contagemVogais[2]++; break;
                            case 'o': contagemVogais[3]++; break;
                            case 'u': contagemVogais[4]++; break;
                            case 'á': contagemVogais[5]++; break;
                            case 'é': contagemVogais[6]++; break;
                            case 'í': contagemVogais[7]++; break;
                            case 'ó': contagemVogais[8]++; break;
                            case 'ú': contagemVogais[9]++; break;
                            case 'à': contagemVogais[10]++; break;
                            case 'è': contagemVogais[11]++; break;
                            case 'ì': contagemVogais[12]++; break;
                            case 'ò': contagemVogais[13]++; break;
                            case 'ù': contagemVogais[14]++; break;
                            case 'ã': contagemVogais[15]++; break;
                            case 'õ': contagemVogais[16]++; break;
                            case 'â': contagemVogais[17]++; break;
                            case 'ê': contagemVogais[18]++; break;
                            case 'î': contagemVogais[19]++; break;
                            case 'ô': contagemVogais[20]++; break;
                            case 'û': contagemVogais[21]++; break;
                            default:
                                if (Character.isLetter(c)) {
                                    contagemConsoantes++;
                                }
                        }
                    }

                  
                    Matcher matcherBr = padraoBr.matcher(textoCompleto);
                    while (matcherBr.find()) {
                        contagemBr++;
                    }

                    Matcher matcherTable = padraoTable.matcher(textoCompleto);
                    while (matcherTable.find()) {
                        contagemTable++;
                    }

           
                    System.out.printf("a(%d) e(%d) i(%d) o(%d) u(%d) á(%d) é(%d) í(%d) ó(%d) ú(%d) à(%d) è(%d) ì(%d) ò(%d) ù(%d) ã(%d) õ(%d) â(%d) ê(%d) î(%d) ô(%d) û(%d) consoante(%d) <br>(%d) <table>(%d) nomepágina(%d)%n",
                            contagemVogais[0], contagemVogais[1], contagemVogais[2], contagemVogais[3], contagemVogais[4],
                            contagemVogais[5], contagemVogais[6], contagemVogais[7], contagemVogais[8], contagemVogais[9],
                            contagemVogais[10], contagemVogais[11], contagemVogais[12], contagemVogais[13], contagemVogais[14],
                            contagemVogais[15], contagemVogais[16], contagemVogais[17], contagemVogais[18], contagemVogais[19],
                            contagemVogais[20], contagemVogais[21], contagemConsoantes, contagemBr, contagemTable, nomePagina.length());
                } else {
                    System.out.println("O link não está funcionando");
                }
            }
        }

        entrada.close();
    }
}
