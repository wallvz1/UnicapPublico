// Eu mostrei no vídeo o código que eu havia criado no repositório privado que tenho, criei esse aqui para poder anexar o link para o senhor na atividade.

#include <stdio.h>

const int TAM_MAX = 50;

void inserirOrdenado(int vetor[], int *tam, int valor) {
    if (*tam >= TAM_MAX) {
        printf("O vetor atingiu a capacidade máxima.\n");
        return;
    }

    int i, j;
    for (i = 0; i < *tam; i++) {
        if (vetor[i] > valor) {
            break;
        }
    }

    for (j = *tam; j > i; j--) {
        vetor[j] = vetor[j - 1];
    }

    vetor[i] = valor;
    (*tam)++;
}

int buscaBinaria(int vetor[], int tam, int valor) {
    int inicio = 0, fim = tam - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (vetor[meio] == valor)
            return meio;
        else if (vetor[meio] < valor)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void removerElemento(int vetor[], int *tam, int valor) {
    int pos = buscaBinaria(vetor, *tam, valor);
    if (pos == -1) {
        printf("Valor não encontrado.\n");
        return;
    }

    for (int i = pos; i < *tam - 1; i++) {
        vetor[i] = vetor[i + 1];
    }

    (*tam)--;
}

void imprimirVetor(int vetor[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int vetor[TAM_MAX], tam, valor, opcao;

    do {
        printf("Digite o tamanho inicial do vetor (entre 3 e 50): ");
        scanf("%d", &tam);
    } while (tam < 3 || tam > TAM_MAX);

    printf("Digite %d valores inteiros:\n", tam);
    int elementosInseridos = 0;  
    for (int i = 0; i < tam; i++) {
        scanf("%d", &valor);
        inserirOrdenado(vetor, &elementosInseridos, valor);  
    }
    
    int pos;
    do {
        printf("\nMenu:\n");
        printf("1. Imprimir vetor\n");
        printf("2. Consultar posição de um elemento\n");
        printf("3. Remover um elemento\n");
        printf("4. Inserir um elemento\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimirVetor(vetor, tam);
                break;
            case 2:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                pos = buscaBinaria(vetor, tam, valor);
                if (pos != -1)
                    printf("Posição: %d\n", pos);
                else
                    printf("Valor não encontrado.\n");
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                removerElemento(vetor, &tam, valor);
                break;
            case 4:
                if (tam >= TAM_MAX) {
                    printf("Erro: vetor cheio.\n");
                } else {
                    printf("Digite o valor a ser inserido: ");
                    scanf("%d", &valor);
                    inserirOrdenado(vetor, &tam, valor);
                }
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}