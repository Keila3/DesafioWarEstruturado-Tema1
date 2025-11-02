#include "missao.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


const int TOTAL_MISSOES = 5;

// Array de missões disponíveis
const char* missoesDisponiveis[] = {
    "Conquistar 2 territórios diferentes",
    "Ter 20 ou mais tropas no total.",
    "Ter mais tropas em um território do que qualquer outro território do inimigo",
    "Vencer duas batalhas seguidas.",
    "Dominar mais de 75% dos territórios."
};


void atribuirMissao(char* destino, const char* missoesDisponiveis[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes; // Seleciona uma missão aleatória
    strcpy(destino, missoesDisponiveis[indiceSorteado]); // Copia a missão para o destino
}
void exibirMissao(const char* missao) {
    printf("Sua missão atual é: %s\n", missao); // Exibe a missão atual
}
int verificarMissao(const char* missao, Territorio* mapa, int qtd, const char* corJogador, int vitoriasSeguidas) {
    if (strstr(missao, "2 territórios diferentes")) {
        int ContadorTerritorios = 0;
        for (int i = 0; i < qtd; i++) {
            // VERIFICA SE A COR DO TERRITÓRIO É IGUAL À COR DO JOGADOR
            if (strcmp(mapa[i].cor, corJogador) == 0) { 
                ContadorTerritorios++;
            }
        }
        
        // Retorna 1 (Verdadeiro) se o jogador tiver 2 ou mais
        return ContadorTerritorios >= 2; 
    }
    
    else if (strstr(missao, "Ter 20 ou mais tropas no total.")) {
        int totalTropas = 0;
        // Soma o número de tropas em todos os territórios do jogador
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                totalTropas += mapa[i].tropas;
            }
        }
        // Retorna 1 (Verdadeiro) se o total de tropas for 20 ou mais
        return totalTropas >= 20;
        
    }
    else if (strstr(missao, "mais tropas em um território do que qualquer outro território do inimigo")){
        int maxTropasJogador = 0;
        int maxTropasInimigo = 0;

        // Encontra o máximo de tropas em um território do jogador
        for(int i = 0; i< qtd; i ++){
            if (strcmp (mapa[i].cor, corJogador) == 0){
                if (mapa[i].tropas > maxTropasJogador){
                    maxTropasJogador = mapa[i].tropas;
                }
            }
            else {
                if (mapa[i].tropas > maxTropasInimigo){
                    maxTropasInimigo = mapa[i].tropas;
                }
            }
        }
        // Retorna 1 (Verdadeiro) se o jogador tiver mais tropas em um território do que o inimigo
        return maxTropasJogador > maxTropasInimigo;
    }
    else if (strstr(missao, "Vencer duas batalhas seguidas.")) {
        // Retorna 1 (Verdadeiro) se o jogador tiver vencido duas batalhas seguidas
        return vitoriasSeguidas >= 2;
    }
    else if (strstr(missao, "Dominar mais de 75% dos territórios.")) {
        int contadorTerritoriosJogador = 0;
        
        // Conta o número total de territórios dominados pelo jogador
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contadorTerritoriosJogador++;
            }
        }
        // Retorna 1 (Verdadeiro) se o jogador dominar mais de 75% dos territórios
        return ((double)contadorTerritoriosJogador / (double)qtd) > 0.75;
    }
    return 0; 
}   