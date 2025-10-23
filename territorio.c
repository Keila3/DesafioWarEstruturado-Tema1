#include "territorio.h"
#include <stdlib.h>
#include <time.h>
#include <string.h> 



// CADASTRO DOS TERRITORIOS
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    int i = 0;

    //CADASTRO DOS DADOS 
    for (i = 0; i < qtd; i++){
 //Nome
    printf("Digite o nome do Territorio %d:", i + 1);
    scanf("%29s", mapa[i].nome);
    int c = getchar(); while (c != '\n' && c != EOF) c = getchar(); // Limpa o buffer do teclado
 // Cor
    printf("Digite a cor do exercito do Territorio %d:", i + 1);
    scanf("%9s", mapa[i].cor);
    c = getchar(); while (c != '\n' && c != EOF) c = getchar(); // Limpa o buffer do teclado
 //Tropas
    printf("Adicione suas tropas %d:", i + 1);
    scanf("%d", &mapa[i].tropas);
    c = getchar(); while (c != '\n' && c != EOF) c = getchar(); // Limpa o buffer do teclado
    }
 }

 // EXIBIÇAO DOS DADOS
 void exibirTerritorios(Territorio *mapa, int qtd){
    int i = 0;

    printf("\n=== LISTA DE TERRITÓRIOS ===\n");

    for ( i = 0; i < qtd; i++)
    {
        printf("%d:\n Nome: %s\n Cor: %s\n Tropas: %d\n\n",
            i + 1,
            mapa[i].nome,
            mapa[i].cor,
            mapa[i].tropas
        );
        
    }
 }

// FUNÇÃO DE ATAQUE
void atacar(Territorio* atacante, Territorio* defensor){
    int dado_ataque = rand() % 6 + 1;
    int dado_defesa = rand() % 6 + 1;

    printf("Resultados dos Dados: Ataque: %d | Defesa: %d\n", dado_ataque, dado_defesa);
 
    // Verifica o resultado do ataque 
    // Se o atacante vencer
    if (dado_ataque > dado_defesa) {
        int transferidas = atacante->tropas / 2;
        if (transferidas < 1) transferidas = 1;

        atacante->tropas -= transferidas;
        defensor->tropas += transferidas; 
        strcpy(defensor->cor, atacante->cor);

        printf("O Territorio %s foi conquistado! %d tropas transferidas.\n", defensor->nome, transferidas);
    } else { // Se o defensor vencer
        if (atacante->tropas > 1){
            atacante->tropas -= 1;
        }
        printf("O Territorio %s defendeu o ataque!\n", defensor->nome);
    }
}

    
// LIBERAÇÃO DA MEMÓRIA
 void liberarMemoria(Territorio *mapa){
    free(mapa);
    
}
