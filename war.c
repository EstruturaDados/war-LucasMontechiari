#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// DEFININDO CONSTANTE GLOBAL
#define TAM_STRING 100

// ESTRUTURA DOS TERRITÓRIOS
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territory;

// FUNÇÃO PARA CADASTRAR TERRITÓRIOS
void cadastrarTerritorios(Territory* mapa, int quantidade) {

    for (int i = 0; i < quantidade; i++) {

        printf("\n=== CADASTRO DO TERRITÓRIO %d ===\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();

        printf("Território cadastrado com sucesso!\n");
    }
}

// FUNÇÃO PARA EXIBIR O MAPA
void exibirMapa(Territory* mapa, int quantidade) {

    printf("\n=====================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=====================================\n");

    for (int i = 0; i < quantidade; i++) {

        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n=====================================\n");
}

// FUNÇÃO DE ATAQUE
void atacar(Territory* origem, Territory* destino) {

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n========== BATALHA ==========\n");
    printf("Atacante rolou: %d\n", dadoAtaque);
    printf("Defensor rolou: %d\n", dadoDefesa);

    // EMPATE FAVORECE O ATACANTE
    if (dadoAtaque >= dadoDefesa) {

        destino->tropas--;

        printf("\nO atacante venceu!\n");
        printf("%s perdeu 1 tropa.\n", destino->nome);

        // CONQUISTA DO TERRITÓRIO
        if (destino->tropas <= 0) {

            printf("\n%s foi conquistado!\n", destino->nome);

            strcpy(destino->cor, origem->cor);

            destino->tropas = 1;

            origem->tropas--;
        }

    } else {

        origem->tropas--;

        printf("\nO defensor venceu!\n");
        printf("%s perdeu 1 tropa.\n", origem->nome);
    }

    printf("==============================\n");
}

// FUNÇÃO PRINCIPAL
int main() {

    srand(time(NULL));

    int quantidade;

    printf("=====================================\n");
    printf("      WAR ESTRUTURADO - BATALHA\n");
    printf("=====================================\n");

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &quantidade);
    getchar();

    // ALOCAÇÃO DINÂMICA
    Territory* mapa = calloc(quantidade, sizeof(Territory));

    // VERIFICAÇÃO DE ERRO
    if (mapa == NULL) {

        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // CADASTRO
    cadastrarTerritorios(mapa, quantidade);

    int atacante;
    int defensor;

    // LOOP DO JOGO
    while (1) {

        exibirMapa(mapa, quantidade);

        printf("\n=== FASE DE ATAQUE ===\n");

        printf("Escolha o território atacante (1 a %d | 0 para sair): ", quantidade);
        scanf("%d", &atacante);

        // SAIR DO JOGO
        if (atacante == 0) {

            printf("\nEncerrando jogo...\n");
            break;
        }

        printf("Escolha o território defensor (1 a %d): ", quantidade);
        scanf("%d", &defensor);

        // VALIDAÇÃO DE ÍNDICES
        if (atacante < 1 || atacante > quantidade ||
            defensor < 1 || defensor > quantidade) {

            printf("\nTerritório inválido.\n");
            continue;
        }

        // NÃO PODE ATACAR O PRÓPRIO TERRITÓRIO
        if (atacante == defensor) {

            printf("\nVocê não pode atacar o próprio território.\n");
            continue;
        }

        // NÃO PODE ATACAR TERRITÓRIO DA MESMA COR
        if (strcmp(mapa[atacante - 1].cor,
                   mapa[defensor - 1].cor) == 0) {

            printf("\nVocê não pode atacar um território aliado.\n");
            continue;
        }

        // TERRITÓRIO PRECISA TER MAIS DE 1 TROPA
        if (mapa[atacante - 1].tropas <= 1) {

            printf("\nTropas insuficientes para atacar.\n");
            continue;
        }

        // REALIZA ATAQUE
        atacar(&mapa[atacante - 1],
                &mapa[defensor - 1]);
    }

    // LIBERA MEMÓRIA
    free(mapa);

    return 0;
}
 