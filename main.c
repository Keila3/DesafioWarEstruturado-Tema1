#include "territorio.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

    // Cadastro dos territórios
    int qtd = read_int("Quantidade de territorios a serem cadastrados: ");
    if (qtd <= 0) {
        printf("Quantidade inválida.\n");
        return 1;
    }

    Territorio *territorios = (Territorio*)  malloc(qtd * sizeof(Territorio)); // Aloca memória para os territórios
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1; 
    }
    cadastrarTerritorios(territorios, qtd); // Chama a função para cadastrar os territórios
   
    exibirTerritorios(territorios, qtd); // Chama a função para exibir os territórios
    
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

        
        printf("Digite o número do território atacante: ");
        scanf("%d", &ataque);
        printf("Digite o número do território defensor: ");
        scanf("%d", &defesa);

        // Ajusta os índices para base zero
        ataque -= 1; 
        defesa -= 1;
    
    }

    // Inicia o ataque
    
        printf("Iniciando o ataque do território %s contra o território %s...\n",
            territorios[ataque].nome,
            territorios[defesa].nome
        );
            
    atacar(&territorios[ataque], &territorios[defesa]); // Chama a função de ataque entre territórios
    exibirTerritorios(territorios, qtd); // Chama a função para exibir os territórios
    
    

    liberarMemoria(territorios); // Chama a função para liberar a memória alocada
    
    printf("\nJogo encerrado. Obrigado por jogar!\n");

    return 0;
}


