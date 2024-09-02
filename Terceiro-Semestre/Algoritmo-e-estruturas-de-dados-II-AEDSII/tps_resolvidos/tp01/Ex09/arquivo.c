#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024


void gravarArquivo(const char *caminhoArquivo)
{
    FILE *arquivo = fopen(caminhoArquivo, "w");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, sizeof(linha), stdin))
    {
       
        linha[strcspn(linha, "\n")] = '\0';
        fprintf(arquivo, "%s\n", linha);
    }

    fclose(arquivo);
}


void formatarNumero(char *texto)
{
    if (texto[0] == '.')
    {
        memmove(texto + 1, texto, strlen(texto) + 1);
        texto[0] = '0';
    }

    char *pontoDecimal = strchr(texto, '.');
    if (pontoDecimal)
    {
        char *finalParteDecimal = pontoDecimal + strlen(pontoDecimal) - 1;
        while (finalParteDecimal > pontoDecimal && *finalParteDecimal == '0')
        {
            finalParteDecimal--;
        }
        *(finalParteDecimal + 1) = '\0';

        if (*(finalParteDecimal + 1) == '\0' && pontoDecimal[1] == '\0')
        {
            *pontoDecimal = '\0';
        }
    }
}


void lerArquivoReverso(const char *caminhoArquivo)
{
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    char linha[MAX_LINE_LENGTH];
    char buffer[MAX_LINE_LENGTH];
    size_t bufferIndex = 0;

    for (long posicao = tamanho - 1; posicao >= 0; posicao--)
    {
        fseek(arquivo, posicao, SEEK_SET);
        int caractere = fgetc(arquivo);

        if (caractere == '\n' || posicao == 0)
        {
            if (bufferIndex > 0)
            {
                
                if (posicao != 0)
                {
                    buffer[bufferIndex] = '\0';
                    for (size_t i = 0; i < bufferIndex; i++)
                    {
                        linha[i] = buffer[bufferIndex - 1 - i];
                    }
                    linha[bufferIndex] = '\0';
                    formatarNumero(linha);
                    printf("%s\n", linha);
                }
                bufferIndex = 0;
            }
        }
        else
        {
            buffer[bufferIndex++] = (char)caractere;
        }
    }

    fclose(arquivo);
}

int main()
{
    const char *caminhoArquivo = "arquivo.txt";

    gravarArquivo(caminhoArquivo);

    lerArquivoReverso(caminhoArquivo);
    return 0;
}
