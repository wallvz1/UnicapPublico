#include <stdio.h>
#include <string.h>
const int TAM = 26;

struct Estado {
    char nome[30];
    int veiculos;
    int acidentes;
};

void coletarDados(struct Estado estados[]) {
    int i;
    for (i = 0; i < TAM; i++) {
        printf("Estado %d:\n", i + 1);
        printf("Nome do estado: ");
        getchar();
        fgets(estados[i].nome, sizeof(estados[i].nome), stdin);
        printf("Numero de veiculos (2007): ");
        scanf("%d", &estados[i].veiculos);
        printf("Numero de acidentes de transito (2007): ");
        scanf("%d", &estados[i].acidentes);
        printf("\n");
    }
}

void maiorMenorAcidente(struct Estado estados[], int *indiceMaior, int *indiceMenor) {
    int i;
    *indiceMaior = 0;
    *indiceMenor = 0;
    for (i = 1; i < TAM; i++) {
        if (estados[i].acidentes > estados[*indiceMaior].acidentes) {
            *indiceMaior = i;
        }
        if (estados[i].acidentes < estados[*indiceMenor].acidentes) {
            *indiceMenor = i;
        }
    }
}

float percentualAcidentes(struct Estado estados[], int indice) {
    if (estados[indice].veiculos == 0) return 0.0;
    return ((float)estados[indice].acidentes / estados[indice].veiculos) * 100;
}

float mediaAcidentes(struct Estado estados[]) {
    int i, total = 0;
    for (i = 0; i < TAM; i++) {
        total += estados[i].acidentes;
    }
    return (float)total / TAM;
}

void estadosAcimaMedia(struct Estado estados[], float media) {
    int i;
    printf("\nEstados com acidentes acima da media nacional:\n");
    for (i = 0; i < TAM; i++) {
        if (estados[i].acidentes > media) {
            printf("%s com %d acidentes\n", estados[i].nome, estados[i].acidentes);
        }
    }
}

int main() {
    struct Estado estados[TAM];
    int i, indiceMaior, indiceMenor;

    coletarDados(estados);

    maiorMenorAcidente(estados, &indiceMaior, &indiceMenor);
    printf("\nMaior numero de acidentes: %d em %s\n", estados[indiceMaior].acidentes, estados[indiceMaior].nome);
    printf("Menor numero de acidentes: %d em %s\n", estados[indiceMenor].acidentes, estados[indiceMenor].nome);

    printf("\nPercentual de veiculos envolvidos em acidentes por estado:\n");
    for (i = 0; i < TAM; i++) {
        float percentual = percentualAcidentes(estados, i);
        printf("%s: %.2f%%\n", estados[i].nome, percentual);
    }

    float media = mediaAcidentes(estados);
    printf("\nMedia de acidentes no pais: %.2f\n", media);

    estadosAcimaMedia(estados, media);

    return 0;
}