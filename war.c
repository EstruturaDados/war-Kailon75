#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ==========================================================
   STRUCT TERRITÓRIO
========================================================== */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ==========================================================
   PROTÓTIPOS DAS FUNÇÕES
========================================================== */
void cadastrarTerritorios(Territorio* mapa, int total);
void exibirMapa(Territorio* mapa, int total);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int total);
void liberarMemoria(Territorio* mapa, char* missaoJog1);
void verMissao(char* missao);

/* ==========================================================
   FUNÇÃO: Cadastro de territórios
========================================================== */
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/* ==========================================================
   FUNÇÃO: Exibir mapa
========================================================== */
void exibirMapa(Territorio* mapa, int total) {
    printf("\n======= MAPA ATUAL =======\n");
    for (int i = 0; i < total; i++) {
        printf("\nTerritório %d:\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
    printf("===========================\n");
}

/* ==========================================================
   FUNÇÃO: Simulação de ataque
========================================================== */
void atacar(Territorio* atacante, Territorio* defensor) {

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nErro: não é possível atacar um território da mesma cor!\n");
        return;
    }

    printf("\n--- Batalha: %s (ATACANTE) vs %s (DEFENSOR) ---\n",
           atacante->nome, defensor->nome);

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoA);
    printf("Dado do defensor: %d\n", dadoD);

    if (dadoA > dadoD) {
        printf("\nO atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("\nO defensor resistiu. Atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

/* ==========================================================
   FUNÇÃO: Atribuir missão aleatória
========================================================== */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

/* ==========================================================
   FUNÇÃO: Mostrar missão sob demanda (menu)
========================================================== */
void verMissao(char* missao) {
    printf("\n🎯 SUA MISSÃO: %s\n", missao);
}

/* ==========================================================
   FUNÇÃO: Verificar missão cumprida
========================================================== */
int verificarMissao(char* missao, Territorio* mapa, int total) {
    
    // Missão: Controlar todos os territórios da cor azul
    if (strcmp(missao, "Controlar todos os territorios da cor azul") == 0) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "azul") != 0)
                return 0;
        }
        return 1;
    }

    // Missão: Ter um território com mais de 15 tropas
    if (strcmp(missao, "Ter um territorio com mais de 15 tropas") == 0) {
        for (int i = 0; i < total; i++) {
            if (mapa[i].tropas > 15)
                return 1;
        }
        return 0;
    }

    // Missão: Conquistar um território vermelho
    if (strcmp(missao, "Conquistar um territorio vermelho") == 0) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0)
                return 1;
        }
        return 0;
    }

    return 0;
}

/* ==========================================================
   FUNÇÃO: Liberar memória
========================================================== */
void liberarMemoria(Territorio* mapa, char* missaoJog1) {
    free(mapa);
    free(missaoJog1);
}

/* ==========================================================
   MAIN
========================================================== */
int main() {

    srand(time(NULL));

    int total;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &total);

    Territorio* mapa = (Territorio*) calloc(total, sizeof(Territorio));

    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);

    /* ----------------------- MISSÕES ---------------------- */
    char* missoes[] = {
        "Controlar todos os territorios da cor azul",
        "Ter um territorio com mais de 15 tropas",
        "Conquistar um territorio vermelho"
    };
    int totalMissoes = 3;

    char* missaoJog1 = (char*) malloc(120);

    atribuirMissao(missaoJog1, missoes, totalMissoes);

    printf("\nMissão sorteada para o Jogador 1!\n");
    printf("(Use o menu para consultar.)\n");

    /* ----------------------- MENU -------------------------- */
    int opcao = -1;
    int atacante, defensor;

    while (opcao != 0) {

        printf("\n========= MENU =========\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Realizar ataque\n");
        printf("3 - Ver minha missão\n");
        printf("0 - Sair do jogo\n");
        printf("========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            exibirMapa(mapa, total);
            break;

        case 2:
            printf("\nTerritório ATACANTE (0 a %d): ", total - 1);
            scanf("%d", &atacante);

            printf("Território DEFENSOR (0 a %d): ", total - 1);
            scanf("%d", &defensor);

            atacar(&mapa[atacante], &mapa[defensor]);

            if (verificarMissao(missaoJog1, mapa, total)) {
                printf("\n🎉 PARABÉNS! VOCÊ CUMPRIU SUA MISSÃO!\n");
                opcao = 0;
            }
            break;

        case 3:
            verMissao(missaoJog1);
            break;

        case 0:
            printf("\nEncerrando o jogo...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }
    }

    liberarMemoria(mapa, missaoJog1);
    return 0;
}
