#ifndef TRANSICOES_H
#define TRANSICOES_H

#define MAX_SIMBOLOS 30
#define MAX_ESTADOS 50
#define MAX_TRANSICOES 100
#define MAX_FITA 100

// Estrutura para representar uma transição
typedef struct {
    int estado_atual;     // Estado atual da transição
    char simbolo_lido;    // Símbolo lido da fita
    char simbolo_escrito; // Símbolo a ser escrito na fita
    char direcao;         // Direção de movimento ('D' para direita, 'E' para esquerda)
    int proximo_estado;   // Próximo estado após a transição
} Transicao;

/**
 * Encontra o índice da transição correspondente ao estado e símbolo fornecidos.
 *
 * @param transicoes Array de transições
 * @param num_transicoes Número total de transições
 * @param estado Estado atual da máquina
 * @param simbolo Símbolo lido da fita
 * @return O índice da transição encontrada, ou -1 se não encontrada
 */
int encontrar_transicao(Transicao *transicoes, int num_transicoes, int estado, char simbolo);

#endif