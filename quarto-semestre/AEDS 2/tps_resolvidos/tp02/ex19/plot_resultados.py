import matplotlib.pyplot as plt

# Inicializa dicionários para armazenar os dados
tempos = {}
comparacoes = {}
movimentacoes = {}

# Algoritmos que vamos plotar
algoritmos = ["Selection Sort", "Insertion Sort", "Bubble Sort", "Quicksort"]

# Tamanhos de entrada
tamanhos = []

# Leitura do arquivo
with open("resultado_comparacao_ordenacao.txt", "r") as arquivo:
    linhas = arquivo.readlines()
    tamanho_atual = None

    for linha in linhas:
        linha = linha.strip()
        if linha.startswith("==="):
            tamanho_atual = int(linha.split()[3])
            tamanhos.append(tamanho_atual)
            for alg in algoritmos:
                tempos.setdefault(alg, []).append(0)
                comparacoes.setdefault(alg, []).append(0)
                movimentacoes.setdefault(alg, []).append(0)

        else:
            for alg in algoritmos:
                if linha.startswith(alg):
                    partes = linha.split("|")
                    tempo = int(partes[0].split(":")[1].replace("ms", "").strip())
                    comp = int(partes[1].split(":")[1].strip())
                    mov = int(partes[2].split(":")[1].strip())

                    tempos[alg][-1] = tempo
                    comparacoes[alg][-1] = comp
                    movimentacoes[alg][-1] = mov

# Função para plotar gráficos
def plotar_grafico(dados, titulo, ylabel, nome_arquivo):
    plt.figure(figsize=(10, 6))
    for alg in algoritmos:
        plt.plot(tamanhos, dados[alg], marker='o', label=alg)

    plt.title(titulo)
    plt.xlabel("Tamanho do vetor")
    plt.ylabel(ylabel)
    plt.legend()
    plt.grid(True)
    plt.savefig(nome_arquivo)
    plt.close()

# Gerar gráficos
plotar_grafico(tempos, "Tempo de Execução (ms)", "Tempo (ms)", "tempo_execucao.png")
plotar_grafico(comparacoes, "Número de Comparações", "Comparações", "comparacoes.png")
plotar_grafico(movimentacoes, "Número de Movimentações", "Movimentações", "movimentacoes.png")

print("Gráficos gerados: tempo_execucao2.png, comparacoes2.png, movimentacoes2.png")
