#ifndef MISSAO_H
#define MISSAO_H
#include "territorio.h"


// Declaração das funções relacionadas às missões
void atribuirMissao(char* destino, const char* missoesDisponiveis[], int totalMissoes); // Função para atribuir uma missão ao jogador
void exibirMissao(const char *missao); // Função para exibir a missão atual do jogador
int verificarMissao(const char* missao, Territorio* mapa, int qtd, const char* corJogador, int vitoriasSeguidas); // Função para verificar se a missão foi cumprida

extern const int TOTAL_MISSOES; // Declaração da constante do total de missões
extern const char* missoesDisponiveis[]; // Declaração do array de

#endif // MISSAO_H