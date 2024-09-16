#include <stdio.h>
#include <string.h>

#define MAX_SIMBOLOS 30
#define MAX_ESTADOS 50
#define MAX_TRANSICOES 100
#define MAX_FITA 100


typedef struct {
  int estado_atual;
  char simbolo_lido;
  char simbolo_escrito;
  char direcao; 
  int proximo_estado;
} Transicao;


int encontrar_transicao(Transicao *transicoes, int num_transicoes, int estado, char simbolo) {
  for (int i = 0; i < num_transicoes; i++) {
    if (transicoes[i].estado_atual == estado &&
        transicoes[i].simbolo_lido == simbolo) {
      return i;
    }
  }
  return -1;
}

int main() {
  char alfabeto[MAX_SIMBOLOS + 1]; 
  int num_estados;
  int num_transicoes;
  Transicao transicoes[MAX_TRANSICOES]; 
  char fita[MAX_FITA];                  
  int num_palavras;                     
  
  FILE *arquivo_entrada = fopen("input.txt", "r");
  if (arquivo_entrada == NULL) {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 1;
  }
  
  fscanf(arquivo_entrada, "%s", alfabeto);
  
  fscanf(arquivo_entrada, "%d", &num_estados);

  fscanf(arquivo_entrada, "%d", &num_transicoes);

  for (int i = 0; i < num_transicoes; i++) {
    int estado;
    char simbolo_lido, simbolo_escrito, direcao;
    int proximo_estado;
    fscanf(arquivo_entrada, "%d %c %c %c %d", &estado, &simbolo_lido, &simbolo_escrito, &direcao, &proximo_estado);
    
    if (simbolo_lido == '-')
      simbolo_lido = ' ';
    if (simbolo_escrito == '-')
      simbolo_escrito = ' ';

    transicoes[i] = (Transicao){estado, simbolo_lido, simbolo_escrito, direcao, proximo_estado};
  }
  
  fscanf(arquivo_entrada, "%d", &num_palavras);
  for (int i = 0; i < num_palavras; i++) {
    fscanf(arquivo_entrada, "%s", fita); 
    
    int tamanho_fita = strlen(fita);
    for (int j = tamanho_fita; j < MAX_FITA; j++) {
      fita[j] = ' '; 
    }
    fita[MAX_FITA - 1] = '\0'; 
    
    int estado_atual = 1;   
    int posicao_cabeca = 0; 
    int aceito = 0;
    int passos = 0;
    
    while (passos < MAX_FITA) {
      passos++; 

      int indice_transicao = encontrar_transicao(
          transicoes, num_transicoes, estado_atual, fita[posicao_cabeca]);
      if (indice_transicao == -1) {
        break; 
      }
      
      Transicao t = transicoes[indice_transicao];
      fita[posicao_cabeca] = t.simbolo_escrito; 
      estado_atual = t.proximo_estado;          

      if (t.direcao == 'D') {
        posicao_cabeca++;
        if (posicao_cabeca >= MAX_FITA) {
          break; 
        }
      } else if (t.direcao == 'E') {
        posicao_cabeca--;
        if (posicao_cabeca < 0) {
          posicao_cabeca = 0; 
        }
      }

      if (estado_atual == num_estados) {
        aceito = 1;
        break;
      }
    }

    printf("%d: %s %s\n", i + 1, fita, aceito ? "OK" : "not OK");
  }

  fclose(arquivo_entrada);
  return 0;
}
