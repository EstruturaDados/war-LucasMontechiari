#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFININDO CONSTANTES GLOBAIS
#define TAM_STRING 100

//DEFININDO A ESTRUTURA (STRUCT)
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
    int territories[5];
} Territory;

//FUNÇÃO PRINCIPAL
int main() {
    printf("=============================================================\n");
    printf("Vamos cadastrar os 5 territórios iniciais para o nosso mundo!\n");
    printf("=============================================================\n");

    Territory territory[5];
    for (int i = 0; i < 5; i++) {

        printf("Digite o nome do território %d: ", i + 1);
        fgets(territory[i].nome, TAM_STRING, stdin);
        territory[i].nome[strcspn(territory[i].nome, "\n")] = '\0'; // Remover a nova linha

        printf("Digite a cor do território %d: ", i + 1);
        fgets(territory[i].cor, TAM_STRING, stdin);
        territory[i].cor[strcspn(territory[i].cor, "\n")] = '\0'; // Remover a nova linha

        printf("Digite o número de tropas no território %d: ", i + 1);
        scanf("%d", &territory[i].tropas);
        getchar(); // Limpar o buffer de entrada

        printf("\nTerritório %d cadastrado com sucesso!\n\n", i + 1);
    }
    //EXIBINDO O MAPA DO MUNDO
    printf("==================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL   \n");
    printf("==================================\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territory[i].nome);
        printf("Cor: %s\n", territory[i].cor);
        printf("Número de tropas: %d\n", territory[i].tropas);
        printf("----------------------------------\n");
    }
    
    return 0;
}

