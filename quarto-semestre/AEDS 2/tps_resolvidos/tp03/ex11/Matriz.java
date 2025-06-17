import java.util.Scanner;

class Matriz {
    int[][] dados;
    int linhas;
    int colunas;

    // Construtor
    Matriz(int l, int c) {
        linhas = l;
        colunas = c;
        dados = new int[linhas][colunas];
    }

    // Lê os dados da matriz
    void ler(Scanner sc) {
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                dados[i][j] = sc.nextInt();
            }
        }
    }

    // Mostra a diagonal principal
    void mostrarDiagonalPrincipal() {
        int tam = Math.min(linhas, colunas);
        for (int i = 0; i < tam; i++) {
            System.out.print(dados[i][i] + " ");
        }
        System.out.println();
    }

    // Mostra a diagonal secundária
    void mostrarDiagonalSecundaria() {
        int tam = Math.min(linhas, colunas);
        for (int i = 0; i < tam; i++) {
            System.out.print(dados[i][colunas - 1 - i] + " ");
        }
        System.out.println();
    }

    // Soma duas matrizes
    Matriz soma(Matriz outra) {
        Matriz resultado = new Matriz(linhas, colunas);
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                resultado.dados[i][j] = this.dados[i][j] + outra.dados[i][j];
            }
        }
        return resultado;
    }

    // Multiplica duas matrizes
    Matriz multiplicacao(Matriz outra) {
        Matriz resultado = new Matriz(this.linhas, outra.colunas);
        for (int i = 0; i < this.linhas; i++) {
            for (int j = 0; j < outra.colunas; j++) {
                for (int k = 0; k < this.colunas; k++) {
                    resultado.dados[i][j] += this.dados[i][k] * outra.dados[k][j];
                }
            }
        }
        return resultado;
    }

    // Mostra a matriz
    void mostrar() {
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                System.out.print(dados[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int casos = sc.nextInt();

        for (int t = 0; t < casos; t++) {
            // Lê primeira matriz
            int l1 = sc.nextInt();
            int c1 = sc.nextInt();
            Matriz m1 = new Matriz(l1, c1);
            m1.ler(sc);

            // Lê segunda matriz
            int l2 = sc.nextInt();
            int c2 = sc.nextInt();
            Matriz m2 = new Matriz(l2, c2);
            m2.ler(sc);

            // Mostra diagonais da primeira matriz
            m1.mostrarDiagonalPrincipal();
            m1.mostrarDiagonalSecundaria();

            // Soma (se possível)
            if (l1 == l2 && c1 == c2) {
                Matriz soma = m1.soma(m2);
                soma.mostrar();
            } else {
                System.out.println("Soma não pode ser feita.");
            }

            // Multiplicação (se possível)
            if (c1 == l2) {
                Matriz mult = m1.multiplicacao(m2);
                mult.mostrar();
            } else {
                System.out.println("Multiplicação não pode ser feita.");
            }
        }

        sc.close();
    }
}
