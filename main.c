#include "territorio.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "missao.h"


static int read_int(const char *prompt) {
    char buf[128];
    int val;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return -1;
        if (sscanf(buf, "%d", &val) == 1) return val;
        printf("Entrada inválida. Tente novamente.\n");
    }
}

int main(){
    printf("==== BATALHA DE TERRITÓRIOS ====\n\n");

    srand(time(NULL)); // Inicializa a semente para números aleatórios
    
    // Declarações e inicialização para os 2 jogadores
    char corJogador1[] = "Vermelho";
    char corJogador2[] = "Azul";

    // Contador de vitórias seguidas
    int vitoriasSeguidasJogador1 = 0;
    int vitoriasSeguidasJogador2 = 0;

    // Ponteiro para a missão
    char *missaoJogador1 = NULL;
    char *missaoJogador2 = NULL;

    // Cadastro dos territórios
    int qtd = read_int("Quantidade de territorios a serem cadastrados: ");
    if (qtd <= 0) {
        printf("Quantidade inválida.\n");
        return 1;
    }

    Territorio *territorios = (Territorio*) malloc(qtd * sizeof(Territorio)); // Aloca memória para os territórios
    if (territorios == NULL) {
        printf("Erro ao alocar memória para territórios!\n");
        return 1; 
    }

    // Aloca memória para as missões
    missaoJogador1 = (char*) malloc(100 * sizeof(char));
    missaoJogador2 = (char*) malloc(100 * sizeof(char));

    // Checagem de erro das missões
    if (missaoJogador1 == NULL || missaoJogador2 == NULL) {
        printf("Erro ao alocar memória para as missões!\n");
        
        // Libera o que foi alocado (territórios)
        if (territorios != NULL){
            free(territorios); // Aqui usamos free, assumindo que liberarMemoria chama free
        }
        // Libera as missões que por ventura tenham sido alocadas antes da falha
        if (missaoJogador1 != NULL) free(missaoJogador1);
        if (missaoJogador2 != NULL) free(missaoJogador2); 
        
        return 1;
    }
    cadastrarTerritorios(territorios, qtd); // Chama a função para cadastrar os territórios
   
    printf("\n--- MISSÃO JOGADOR 1 ---\n");
    atribuirMissao(missaoJogador1, missoesDisponiveis, TOTAL_MISSOES); // Atribui uma missão ao jogador 1
    exibirMissao(missaoJogador1); // Exibe a missão do jogador 1

    printf("\n--- MISSÃO JOGADOR 2 ---\n");
    atribuirMissao(missaoJogador2, missoesDisponiveis, TOTAL_MISSOES); // Atribui uma missão ao jogador 2
    exibirMissao(missaoJogador2); // Exibe a missão do jogador 2

    exibirTerritorios(territorios, qtd); // Chama a função para exibir os territórios
    
    int jogoAtivo = 1; // Flag para controlar o loop do jogo
    do {
    int ataque = read_int("Escolha o número do território atacante: ");
    int defesa  = read_int("Escolha o número do território defensor: ");

    // Ajusta os índices para base zero
    ataque -= 1;
    defesa -= 1;

    // Validações de entrada
    while (ataque < 0  || ataque >=qtd  || defesa < 0  || defesa>= qtd || 
    strcmp(territorios[ataque].cor, territorios[defesa].cor) == 0  || 
    territorios[ataque].tropas <= 1)
    {
       if (ataque < 0 || ataque >= qtd || defesa < 0 || defesa >= qtd) {
        printf("Número de território inválido! Digite novamente.\n");
       }
       else if(strcmp(territorios[ataque].cor, territorios[defesa].cor) == 0) {
            printf("Ataque não permitido: territorio da mesma cor.\n");
        }
        else if (territorios[ataque].tropas <= 1) {
            printf("O território atacante precisa ter mais de 1 tropa.\n");
        }

        
      ataque = read_int("Digite o número do território atacante: ");
      defesa = read_int("Digite o número do território defensor: ");

        // Ajusta os índices para base zero
        ataque -= 1; 
        defesa -= 1;
    
    }

    // Inicia o ataque
    
        printf("Iniciando o ataque do território %s contra o território %s...\n",
            territorios[ataque].nome,
            territorios[defesa].nome
        );
        // Armazena a cor original do defensor para verificar conquistas
        const char* corAtacante = territorios[ataque].cor;
        char corOriginalDefensor[50];
        strncpy(corOriginalDefensor, territorios[defesa].cor, 49);
        corOriginalDefensor[49] = '\0'; // Garante a terminação da string

    atacar(&territorios[ataque], &territorios[defesa]); // Chama a função de ataque entre territórios
    exibirTerritorios(territorios, qtd); // Chama a função para exibir os territórios
    
    // Verifica se houve conquista para atualizar vitórias seguidas
if (strcmp(territorios[defesa].cor , corOriginalDefensor) !=0){
    if (strcmp(corAtacante, corJogador1) ==0){
        vitoriasSeguidasJogador1++;
        vitoriasSeguidasJogador2 =0;
    } else {
        vitoriasSeguidasJogador2++;
        vitoriasSeguidasJogador1 =0;
    }
}

// Verifica se algum jogador cumpriu sua missão
if (verificarMissao(missaoJogador1, territorios, qtd, corJogador1, vitoriasSeguidasJogador1)) {
    printf("Jogador 1 cumpriu sua missão e venceu o jogo!\n");
    jogoAtivo = 0;
    continue;
}
if (verificarMissao(missaoJogador2, territorios, qtd, corJogador2, vitoriasSeguidasJogador2)) {
    printf("Jogador 2 cumpriu sua missão e venceu o jogo!\n");
    jogoAtivo = 0;
    continue;
}
} while (jogoAtivo); // Loop infinito para repetir o jogo

    liberarMemoria(territorios); // Chama a função para liberar a memória alocada
    
    free(missaoJogador1); // Libera a memória da missão do jogador 1
    free(missaoJogador2); // Libera a memória da missão do jogador 2

    printf("\nJogo encerrado. Obrigado por jogar!\n");

    return 0;
}


