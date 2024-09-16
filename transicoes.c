#include "transicoes.h"

int encontrar_transicao(Transicao *transicoes, int num_transicoes, int estado, char simbolo) {
    for (int i = 0; i < num_transicoes; i++) {
        if (transicoes[i].estado_atual == estado &&
            transicoes[i].simbolo_lido == simbolo) {
            return i;
        }
    }
    return -1;
}