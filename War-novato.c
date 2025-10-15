#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5

typedef struct {
    char nome [30];
    char cor [10];
    int tropas;
} Territorio;

int main(){
   int i = 0;
    Territorio territorios[MAX_TERRITORIOS];

    //CADASTRO DOS DADOS 
    for  (i = 0; i < MAX_TERRITORIOS; i++){
        //Nome
        printf("Digite o nome do Territorio %d: ", i + 1);
        scanf("%s", territorios[i].nome);
        // Cor
        printf("Digite a cor do exercito do Territorio %d: ", i + 1); 
        scanf("%s", territorios[i].cor);
        //Tropas
        printf("Adicione suas tropas %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);

    }

    //EXIBIÇAO DOS DADOS
    printf("\n*** TERRITORIO ***\n");
    for ( i = 0; i < MAX_TERRITORIOS; i++)
    {
        printf("%d:\n Nome: %s\n Cor: %s\n Tropas: %d\n\n",
            i + 1,
            territorios[i].nome,
            territorios[i].cor,
            territorios[i].tropas
        );
        
      

    }
    
        

    


        return 0;
}


