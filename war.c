#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 50
#define MAX_TERRITORIOS 5

#define MISSAO_DESTRUIR 1
#define MISSAO_CONQUISTAR 2

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territory;

typedef struct {
    int tipoMissao;
    char alvo[TAM_STRING];
} Mission;

// ============================
// FUNÇÃO PARA CADASTRAR MAPA
// ============================

void cadastrarTerritorios(Territory* mapa, int quantidade) {

    char cores[5][20] = {
        "Verde",
        "Azul",
        "Vermelho",
        "Amarelo",
        "Preto"
    };

    char nomes[5][20] = {
        "America",
        "Africa",
        "Asia",
        "Oceania",
        "Europa"
    };

    int tropas[5] = {5, 4, 2, 2, 3};

    for (int i = 0; i < quantidade; i++) {

        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);

        mapa[i].tropas = tropas[i];
    }
}

// ============================
// MOSTRAR MAPA
// ============================

void mostrarMapa(const Territory* mapa, int quantidade) {

    printf("\n=========== MAPA ===========\n");

    for (int i = 0; i < quantidade; i++) {

        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// ============================
// MENU
// ============================

int mostrarMenu() {

    int opcao;

    printf("\n=========== MENU ===========\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");

    printf("Escolha: ");
    scanf("%d", &opcao);

    return opcao;
}

// ============================
// GERAR MISSÃO
// ============================

Mission gerarMissao() {

    Mission missao;

    char cores[5][20] = {
        "Verde",
        "Azul",
        "Vermelho",
        "Amarelo",
        "Preto"
    };

    int opcaoMissao = rand() % 2 + 1;

    missao.tipoMissao = opcaoMissao;

    if (missao.tipoMissao == MISSAO_DESTRUIR) {

        int indiceCor = rand() % 5;

        strcpy(missao.alvo, cores[indiceCor]);
    }

    return missao;
}

// ============================
// MOSTRAR MISSÃO
// ============================

void mostrarMissao(const Mission* missao) {

    printf("\n=========== MISSÃO ===========\n");

    if (missao->tipoMissao == MISSAO_DESTRUIR) {

        printf("Destruir o exército %s\n", missao->alvo);

    } else if (missao->tipoMissao == MISSAO_CONQUISTAR) {

        printf("Conquistar 3 territórios\n");
    }
}

// ============================
// ATAQUE
// ============================

void atacar(Territory* mapa, int quantidade) {

    int atacante;
    int defensor;

    printf("\n=========== ATAQUE ===========\n");

    printf("Escolha o território atacante (1 a %d): ", quantidade);
    scanf("%d", &atacante);

    printf("Escolha o território defensor (1 a %d): ", quantidade);
    scanf("%d", &defensor);

    atacante--;
    defensor--;

    // VALIDAÇÃO

    if (atacante < 0 || atacante >= quantidade ||
        defensor < 0 || defensor >= quantidade) {

        printf("Território inválido!\n");
        return;
    }

    if (atacante == defensor) {

        printf("Não é possível atacar o mesmo território!\n");
        return;
    }

    printf("\n%s atacou %s\n",
           mapa[atacante].nome,
           mapa[defensor].nome);

    // SISTEMA DE BATALHA

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("Dado ataque: %d\n", dadoAtaque);
    printf("Dado defesa: %d\n", dadoDefesa);

    if (dadoAtaque > dadoDefesa) {

        printf("Ataque venceu!\n");

        mapa[defensor].tropas--;

        if (mapa[defensor].tropas <= 0) {

            printf("%s foi conquistado!\n", mapa[defensor].nome);

            strcpy(mapa[defensor].cor, mapa[atacante].cor);

            mapa[defensor].tropas = 1;
        }

    } else {

        printf("Defesa venceu!\n");

        mapa[atacante].tropas--;

        if (mapa[atacante].tropas < 1) {
            mapa[atacante].tropas = 1;
        }
    }
}

// ============================
// VERIFICAR MISSÃO
// ============================

int verificarMissao(
    const Territory* mapa,
    int quantidade,
    const Mission* missao
) {

    // MISSÃO DESTRUIR

    if (missao->tipoMissao == MISSAO_DESTRUIR) {

        int encontrou = 0;

        for (int i = 0; i < quantidade; i++) {

            if (strcmp(mapa[i].cor, missao->alvo) == 0) {
                encontrou = 1;
            }
        }

        if (!encontrou) {

            printf("\nMISSÃO CONCLUÍDA!\n");
            return 1;
        }
    }

    // MISSÃO CONQUISTAR

    else if (missao->tipoMissao == MISSAO_CONQUISTAR) {

        int contador = 0;

        for (int i = 0; i < quantidade; i++) {

            if (mapa[i].tropas > 0) {
                contador++;
            }
        }

        if (contador >= 3) {

            printf("\nMISSÃO CONCLUÍDA!\n");
            return 1;
        }
    }

    printf("\nMissão ainda não concluída.\n");

    return 0;
}

// ============================
// MAIN
// ============================

int main() {

    Territory mapa[MAX_TERRITORIOS];

    Mission missao;

    int opcao;

    srand(time(NULL));

    cadastrarTerritorios(mapa, MAX_TERRITORIOS);

    missao = gerarMissao();

    do {

        mostrarMapa(mapa, MAX_TERRITORIOS);

        opcao = mostrarMenu();

        switch(opcao) {

            case 1:

                atacar(mapa, MAX_TERRITORIOS);

                break;

            case 2:

                mostrarMissao(&missao);

                verificarMissao(
                    mapa,
                    MAX_TERRITORIOS,
                    &missao
                );

                break;

            case 0:

                printf("\nSaindo do jogo...\n");

                break;

            default:

                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}