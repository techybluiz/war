#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 20

typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

void cadastrarTerritorio(Territorio *t, int *total) {
    if (*total >= MAX_TERRITORIOS) {
        printf("Limite de territórios atingido!\n");
        return;
    }

    Territorio novo;

    printf("Nome do território: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Cor do dono: ");
    fgets(novo.cor, 15, stdin);
    novo.cor[strcspn(novo.cor, "\n")] = 0;

    printf("Quantidade de tropas: ");
    scanf("%d", &novo.troplas);
    getchar();

    t[*total] = novo;
    (*total)++;

    printf("Território cadastrado com sucesso!\n");
}


void mostrarTerritorios(Territorio *t, int total) {
    printf("\n--- LISTA DE TERRITORIOS ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].troplas);
    }
    printf("------------------------------\n");
}

void atacar(Territorio *t, int total) {
    if (total < 2) {
        printf("Cadastre pelo menos 2 territorios!\n");
        return;
    }

    int atq, def;
    printf("Escolha o território ATACANTE (número): ");
    scanf("%d", &atq);
    printf("Escolha o território DEFENSOR (número): ");
    scanf("%d", &def);
    getchar();

    atq--; def--;

    if (atq < 0 || atq >= total || def < 0 || def >= total) {
        printf("Território inválido!\n");
        return;
    }

    if (t[atq].troplas < 1) {
        printf("O atacante não tem tropas suficientes!\n");
        return;
    }

    // ALLOCAÇÃO DINÂMICA PARA ROLAR DADOS
    int *dadosAtq = malloc(sizeof(int));
    int *dadosDef = malloc(sizeof(int));

    if (!dadosAtq || !dadosDef) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    srand(time(NULL));
    *dadosAtq = (rand() % 6) + 1;
    *dadosDef = (rand() % 6) + 1;

    printf("\nDado atacante: %d", *dadosAtq);
    printf("\nDado defensor: %d\n", *dadosDef);

    if (*dadosAtq > *dadosDef) {
        printf("Ataque bem-sucedido! O defensor perde uma tropa.\n");
        t[def].troplas--;
    } else {
        printf("Defesa bem-sucedida! O atacante perde uma tropa.\n");
        t[atq].troplas--;
    }

    free(dadosAtq);
    free(dadosDef);
}

void verificarMissao(Territorio *t, int total) {
    char *missao = malloc(100 * sizeof(char));
    if (!missao) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    strcpy(missao, "Conquistar 10 tropas somadas entre todos os territórios.");

    printf("\nMISSÃO ATUAL:\n%s\n", missao);

    int soma = 0;
    for (int i = 0; i < total; i++)
        soma += t[i].troplas;

    if (soma >= 10)
        printf("🏆 Missão concluída! Você domina o mapa!\n");
    else
        printf("Missão ainda não concluída. Tropas atuais: %d\n", soma);

    free(missao);
}

int main() {
    Territorio territorios[MAX_TERRITORIOS];
    int total = 0;

    int opc;

    do {
        printf("\n===== MENU WAR =====\n");
        printf("1 - Cadastrar Território\n");
        printf("2 - Mostrar Territórios\n");
        printf("3 - Atacar Território\n");
        printf("4 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
        case 1:
            cadastrarTerritorio(territorios, &total);
            break;
        case 2:
            mostrarTerritorios(territorios, total);
            break;
        case 3:
            atacar(territorios, total);
            break;
        case 4:
            verificarMissao(territorios, total);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (opc != 0);

    return 0;
}
