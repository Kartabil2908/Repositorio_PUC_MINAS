
int memoriaULA[100] = {0};

// Contador de programa (PC), inicia em 4
int contadorPrograma = 4;

int operandoX, operandoY, resultado;

const int pinosLED[4] = {13, 12, 11, 10};


String ultimaInstrucao = "-";

// Memoria para armazenar as instrucoes como strings
String memoriaTexto[100];

void setup()
{
    Serial.begin(9600);
    for (int i = 0; i < 4; i++)
    {
        pinMode(pinosLED[i], OUTPUT);
    }
}

// Funcao que executa operacoes da ULA
int processarInstrucao(int operandoX, int operandoY, char operacao)
{
    switch (operacao)
    {
    case '0': return 0; // Retorna zero
    case '1': return 15; // Retorna 1111 em binario
    case '2': return operandoX; // Copia X
    case '3': return operandoY; // Copia Y
    case '4': return ~operandoX & 0xF; // NOT X
    case '5': return ~operandoY & 0xF; // NOT Y
    case '6': return operandoX & (~operandoY & 0xF); // X AND NOT Y
    case '7': return (~operandoX & 0xF) & operandoY; // NOT X AND Y
    case '8': return operandoX ^ operandoY; // X XOR Y
    case '9': return ~(operandoX ^ operandoY) & 0xF; // NOT (X XOR Y)
    case 'A': return ~(~operandoX ^ ~operandoY) & 0xF;
    case 'B': return operandoX & operandoY; // X AND Y
    case 'C': return ~(operandoX & operandoY) & 0xF; // NOT (X AND Y)
    case 'D': return ~(operandoX | operandoY) & 0xF; // NOT (X OR Y)
    case 'E': return operandoX | operandoY; // X OR Y
    case 'F': return ~(~operandoX | ~operandoY); // NOT (NOT X OR NOT Y)
    default: return 0;
    }
}

// Funcao para imprimir o dump da memoria
void imprimirDumpMemoria()
{
    Serial.println("\n===== DUMP DE MEMORIA =====");
    Serial.println("Endereco | Conteudo");
    Serial.println("----------------------");
    for (int i = 4; i < contadorPrograma; i++)
    {
        Serial.print(" 0x"); Serial.print(i, HEX);
        Serial.print("    |  "); Serial.println(memoriaTexto[i]);
    }
    Serial.println("==========================");
  	delay(4000);
}


void loop()
{
    if (Serial.available())
    {
        // Le entrada do usuario
        String entradaUsuario = Serial.readStringUntil('\n');
        entradaUsuario.trim();

        int indice = 0;
        while (indice < entradaUsuario.length())
        {
            int proximoEspaco = entradaUsuario.indexOf(' ', indice);
            if (proximoEspaco == -1)
                proximoEspaco = entradaUsuario.length();

            // Extrai a instrucao
            String instrucaoAtual = entradaUsuario.substring(indice, proximoEspaco);
            if (instrucaoAtual.length() == 3)
            {
                // Converte caracteres para valores inteiros
                operandoX = strtol(instrucaoAtual.substring(0, 1).c_str(), NULL, 16);
                operandoY = strtol(instrucaoAtual.substring(1, 2).c_str(), NULL, 16);
                char operacao = instrucaoAtual.charAt(2);

                // Processa a instrucao na ULA
                resultado = processarInstrucao(operandoX, operandoY, operacao);
                memoriaTexto[contadorPrograma] = instrucaoAtual; // Armazena a instrucao na memoria
                contadorPrograma++;

                // Atualiza os LEDs para representar o resultado
                for (int i = 0; i < 4; i++)
                {
                    digitalWrite(pinosLED[i], (resultado >> (3 - i)) & 1);
                }

                // Exibe os dados no monitor serial
                Serial.print("PC: "); Serial.print(contadorPrograma, HEX);
                Serial.print(" | X: "); Serial.print(operandoX, HEX);
                Serial.print(" | Y: "); Serial.print(operandoY, HEX);
                Serial.print(" | W: "); Serial.print(resultado, HEX);
                Serial.print(" | Ant: "); Serial.print(ultimaInstrucao);
                Serial.print(" | Atual: "); Serial.println(instrucaoAtual);
                
                // Atualiza a ultima instrucao
                ultimaInstrucao = instrucaoAtual;
                delay(2000);

                // Imprime o estado da memoria
                imprimirDumpMemoria();
            }
            indice = proximoEspaco + 1; // Avanca para a proxima instrucao
        }
    }
}
