package ex19;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class ComparativoOrdenacao {

    static class MetricasOrdenacao {
        public long totalComparacoes = 0;
        public long totalMovimentacoes = 0;
        public long tempoExecucaoMillis = 0;
    }

    public static void main(String[] args) {
        int[] tamanhosDeEntrada = {100, 1000, 10000, 100000};

        try (BufferedWriter writer = new BufferedWriter(new FileWriter("resultado_comparacao_ordenacao.txt"))) {
            for (int tamanho : tamanhosDeEntrada) {
                writer.write("=== Vetor com " + tamanho + " elementos ===\n");
                System.out.println("\n=== Vetor com " + tamanho + " elementos ===");

                int[] vetorOriginal = gerarVetorAleatorio(tamanho);

                testarSelectionSort(vetorOriginal, writer);
                testarInsertionSort(vetorOriginal, writer);
                testarBubbleSort(vetorOriginal, writer);
                testarQuickSort(vetorOriginal, writer);

                writer.write("\n");
            }

            System.out.println("\nResultados salvos em: resultado_ordenacao.txt");
        } catch (IOException e) {
            System.err.println("Erro ao escrever no arquivo: " + e.getMessage());
        }
    }

    public static int[] gerarVetorAleatorio(int tamanho) {
        Random gerador = new Random();
        int[] vetor = new int[tamanho];
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = gerador.nextInt();
        }
        return vetor;
    }

    public static void testarSelectionSort(int[] vetorOriginal, BufferedWriter writer) throws IOException {
        int[] vetor = vetorOriginal.clone();
        MetricasOrdenacao metricas = new MetricasOrdenacao();
        ordenarPorSelecao(vetor, metricas);
        exibirResultados("Selection Sort", metricas, writer);
    }

    public static void testarInsertionSort(int[] vetorOriginal, BufferedWriter writer) throws IOException {
        int[] vetor = vetorOriginal.clone();
        MetricasOrdenacao metricas = new MetricasOrdenacao();
        ordenarPorInsercao(vetor, metricas);
        exibirResultados("Insertion Sort", metricas, writer);
    }

    public static void testarBubbleSort(int[] vetorOriginal, BufferedWriter writer) throws IOException {
        int[] vetor = vetorOriginal.clone();
        MetricasOrdenacao metricas = new MetricasOrdenacao();
        ordenarPorBolha(vetor, metricas);
        exibirResultados("Bubble Sort", metricas, writer);
    }

    public static void testarQuickSort(int[] vetorOriginal, BufferedWriter writer) throws IOException {
        int[] vetor = vetorOriginal.clone();
        MetricasOrdenacao metricas = new MetricasOrdenacao();
        ordenarPorQuickSort(vetor, metricas);
        exibirResultados("Quicksort", metricas, writer);
    }

    public static void exibirResultados(String nomeAlgoritmo, MetricasOrdenacao metricas, BufferedWriter writer) throws IOException {
        String resultado = String.format(
                "%-15s => Tempo: %6d ms | Comparações: %10d | Movimentações: %10d\n",
                nomeAlgoritmo, metricas.tempoExecucaoMillis, metricas.totalComparacoes, metricas.totalMovimentacoes
        );

        System.out.print(resultado);
        writer.write(resultado);
    }

    // ---------- Algoritmos ----------

    public static void ordenarPorSelecao(int[] vetor, MetricasOrdenacao metricas) {
        long inicio = System.currentTimeMillis();
        int n = vetor.length;

        for (int i = 0; i < n - 1; i++) {
            int indiceMenor = i;
            for (int j = i + 1; j < n; j++) {
                metricas.totalComparacoes++;
                if (vetor[j] < vetor[indiceMenor]) {
                    indiceMenor = j;
                }
            }
            if (i != indiceMenor) {
                trocar(vetor, i, indiceMenor, metricas);
            }
        }

        metricas.tempoExecucaoMillis = System.currentTimeMillis() - inicio;
    }

    public static void ordenarPorInsercao(int[] vetor, MetricasOrdenacao metricas) {
        long inicio = System.currentTimeMillis();
        int n = vetor.length;

        for (int i = 1; i < n; i++) {
            int atual = vetor[i];
            int j = i - 1;

            while (j >= 0) {
                metricas.totalComparacoes++;
                if (vetor[j] > atual) {
                    vetor[j + 1] = vetor[j];
                    metricas.totalMovimentacoes++;
                    j--;
                } else {
                    break;
                }
            }

            vetor[j + 1] = atual;
            metricas.totalMovimentacoes++;
        }

        metricas.tempoExecucaoMillis = System.currentTimeMillis() - inicio;
    }

    public static void ordenarPorBolha(int[] vetor, MetricasOrdenacao metricas) {
        long inicio = System.currentTimeMillis();
        int n = vetor.length;

        for (int i = 0; i < n - 1; i++) {
            boolean houveTroca = false;
            for (int j = 0; j < n - i - 1; j++) {
                metricas.totalComparacoes++;
                if (vetor[j] > vetor[j + 1]) {
                    trocar(vetor, j, j + 1, metricas);
                    houveTroca = true;
                }
            }
            if (!houveTroca) break;
        }

        metricas.tempoExecucaoMillis = System.currentTimeMillis() - inicio;
    }

    public static void ordenarPorQuickSort(int[] vetor, MetricasOrdenacao metricas) {
        long inicio = System.currentTimeMillis();
        quickSortRecursivo(vetor, 0, vetor.length - 1, metricas);
        metricas.tempoExecucaoMillis = System.currentTimeMillis() - inicio;
    }

    public static void quickSortRecursivo(int[] vetor, int inicio, int fim, MetricasOrdenacao metricas) {
        if (inicio < fim) {
            int indicePivo = particionar(vetor, inicio, fim, metricas);
            quickSortRecursivo(vetor, inicio, indicePivo - 1, metricas);
            quickSortRecursivo(vetor, indicePivo + 1, fim, metricas);
        }
    }

    public static int particionar(int[] vetor, int inicio, int fim, MetricasOrdenacao metricas) {
        int pivo = vetor[fim];
        int i = inicio - 1;

        for (int j = inicio; j < fim; j++) {
            metricas.totalComparacoes++;
            if (vetor[j] < pivo) {
                i++;
                trocar(vetor, i, j, metricas);
            }
        }

        trocar(vetor, i + 1, fim, metricas);
        return i + 1;
    }

    public static void trocar(int[] vetor, int i, int j, MetricasOrdenacao metricas) {
        if (i != j) {
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            metricas.totalMovimentacoes += 3;
        }
    }
}
