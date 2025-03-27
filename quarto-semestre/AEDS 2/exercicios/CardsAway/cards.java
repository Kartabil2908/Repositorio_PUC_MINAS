// https://judge.beecrowd.com/en/problems/view/1110

import java.util.*;

public class cards {

    public static void mostrarSaida(ArrayList<Integer> sequenciaCartas, ArrayList<Integer> cartasDescartadas) {
        System.err.print("Discarded cards: ");
        for (int i = 0; i < cartasDescartadas.size(); i++) {
            if (i == cartasDescartadas.size() - 1) {
                System.err.print(cartasDescartadas.get(i));

            } else {
                System.err.print(cartasDescartadas.get(i) + ", ");
            }
        }

        System.out.println();

        System.err.print("Remaining card: ");
        for (int i = 0; i < sequenciaCartas.size(); i++) {
            if (i == sequenciaCartas.size() - 1) {
                System.err.print(sequenciaCartas.get(i));

            } else {
                System.err.print(sequenciaCartas.get(i) + ", ");
            }
        }
    }

    public static void cardsAway(ArrayList<Integer> sequenciaCartas, ArrayList<Integer> cartasDescartadas) {

        while (sequenciaCartas.size() > 1) {
            // Descartar a carta do topo
            int cartaDescartada = sequenciaCartas.remove(0); // Remove a carta do topo
            cartasDescartadas.add(cartaDescartada); // Adiciona a carta descartada na lista de descartadas

            // Mover a carta do topo para o fundo
            int cartaTrocada = sequenciaCartas.remove(0); // Remove o próximo do topo
            sequenciaCartas.add(cartaTrocada); // Coloca no fundo
        }

    }

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        int numCartas = 0;

        while ((numCartas = scanner.nextInt()) != 0) {
            ArrayList<Integer> sequenciaCartas = new ArrayList<>(numCartas);

            ArrayList<Integer> cartasDescartadas = new ArrayList<>();

            for (int i = 1; i <= numCartas; i++) // preenche a sequência de cartas;
            {
                sequenciaCartas.add(i);

            }

            cardsAway(sequenciaCartas, cartasDescartadas);

            mostrarSaida(sequenciaCartas, cartasDescartadas);
            System.out.println();

        }

        scanner.close();

    }
}