#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TERRITORIO_H 
#define TERRITORIO_H 

#define MAX_TERRITORIOS 5

typedef struct {
    char nome [30];
    char cor [10];
    int tropas;
} Territorio; // Estrutura que representa um território

// Declaração das funções
void cadastrarTerritorios(Territorio *mapa, int qtd); // Função de cadastro dos territórios
void exibirTerritorios(Territorio *mapa, int qtd); // Função de exibição dos territórios
void atacar(Territorio* atacante, Territorio* defensor); // Função de ataque entre territórios
void liberarMemoria(Territorio *mapa); // Função de liberação de memória
#endif