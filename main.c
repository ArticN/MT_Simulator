#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "transicoes.h"

int main()
{
  // Criando variáveis principais
  char alfabeto[MAX_SIMBOLOS + 1];
  char fita[MAX_FITA];
  int num_estados;
  int num_transicoes;
  int num_palavras;
  Transicao transicoes[MAX_TRANSICOES];

  // Lê o arquivo
  FILE *arquivo_entrada = fopen("input.txt", "r");

  if (arquivo_entrada == NULL)
  {
    printf("Erro ao abrir o arquivo de entrada.\n");
    return 1;
  }

  // Pegando os primeiros dados do arquivo
  fscanf(arquivo_entrada, "%s", alfabeto);
  fscanf(arquivo_entrada, "%d", &num_estados);
  fscanf(arquivo_entrada, "%d", &num_transicoes);

  for (int i = 0; i < num_transicoes; i++)
  {
    int estado;
    int proximo_estado;
    char simbolo_lido, simbolo_escrito, direcao;

    fscanf(arquivo_entrada, "%d %c %c %c %d", &estado, &simbolo_lido, &simbolo_escrito, &direcao, &proximo_estado);

    // Trocando os elementos em branco por seu respectivo
    if (simbolo_lido == '-')
      simbolo_lido = ' ';
    if (simbolo_escrito == '-')
      simbolo_escrito = ' ';

    // Criando as transições
    transicoes[i] = (Transicao){estado, simbolo_lido, simbolo_escrito, direcao, proximo_estado};
  }

  // Pegando o número de inputs para a máquina
  fscanf(arquivo_entrada, "%d", &num_palavras);
  
  for (int i = 0; i < num_palavras; i++)
  {
    // Pegando cada fita individualmente
    fscanf(arquivo_entrada, "%s", fita);

    int tamanho_fita = strlen(fita);

    char fita_copia[tamanho_fita + 1];

    int estado_atual = 1;
    int posicao_cabeca = 0;
    bool aceito = 0;

    // Copiando para a fita de trabalho
    strcpy(fita_copia, fita);
    fita_copia[tamanho_fita] = ' ';

    while (tamanho_fita <= MAX_FITA)
    {
      // Encontrando a transição
      int indice_transicao = encontrar_transicao(transicoes, num_transicoes, estado_atual, fita_copia[posicao_cabeca]);

      // Tratando transição inexistente
      if (indice_transicao == -1)
      {
        break;
      }

      // Atualizando o estado atual
      Transicao t = transicoes[indice_transicao];
      fita_copia[posicao_cabeca] = t.simbolo_escrito;
      estado_atual = t.proximo_estado;

      // Definindo a posição da cabeça
      if (t.direcao == 'D')
      {
        posicao_cabeca++;
        if (posicao_cabeca >= MAX_FITA)
        {
          break;
        }
      }
      else if (t.direcao == 'E')
      {
        posicao_cabeca--;
        if (posicao_cabeca < 0)
        {
          posicao_cabeca = 0;
        }
      }

      // Checando o estado de aceitação
      if (estado_atual == num_estados)
      {
        aceito = true;
        break;
      }
    }

    // Printando se a fita foi aceita ou não pela MT fornecida
    printf("%d: %s %s\n", i + 1, fita, aceito ? "OK" : "not OK");
  }

  // Limpando a memória
  fclose(arquivo_entrada);
  return 0;
}