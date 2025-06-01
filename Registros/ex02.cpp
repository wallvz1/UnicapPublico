#include <stdio.h>
#include <string.h>

#define TAM 40

struct Produto {
    int codigo;
    char descricao[50];
    float valorUnitario;
    int estoque;
};

void cadastrarProduto(struct Produto produtos[], int *quantidade) {
    if (*quantidade >= TAM) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    printf("Codigo: ");
    scanf("%d", &produtos[*quantidade].codigo);
    getchar(); 

    printf("Descricao: ");
    fgets(produtos[*quantidade].descricao, sizeof(produtos[*quantidade].descricao), stdin);

    // Remover o \n do final da string, se existir
    size_t len = strlen(produtos[*quantidade].descricao);
    if (len > 0 && produtos[*quantidade].descricao[len - 1] == '\n') {
        produtos[*quantidade].descricao[len - 1] = '\0';
    }

    printf("Valor unitario: ");
    scanf("%f", &produtos[*quantidade].valorUnitario);

    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[*quantidade].estoque);

    (*quantidade)++;
    printf("Produto cadastrado com sucesso!\n");
}


void alterarValor(struct Produto produtos[], int quantidade, int codigo) {
    int i;
    for (i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Valor atual: %.2f\n", produtos[i].valorUnitario);
            printf("Novo valor: ");
            scanf("%f", &produtos[i].valorUnitario);
            printf("Valor atualizado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

float obterValor(struct Produto produtos[], int quantidade, int codigo) {
    int i;
    for (i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].valorUnitario;
        }
    }
    return -1; 
}

int obterEstoque(struct Produto produtos[], int quantidade, int codigo) {
    int i;
    for (i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].estoque;
        }
    }
    return -1;
}

void venderProduto(struct Produto produtos[], int quantidade, int codigo, int qtdDesejada) {
    int i;
    for (i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            if (produtos[i].estoque == 0) {
                printf("Produto sem estoque.\n");
                return;
            } else if (qtdDesejada <= produtos[i].estoque) {
                produtos[i].estoque -= qtdDesejada;
                float total = qtdDesejada * produtos[i].valorUnitario;
                printf("Venda realizada! Valor a pagar: R$ %.2f\n", total);
                return;
            } else {
                char opcao;
                printf("Estoque insuficiente. Deseja comprar %d unidades (estoque atual)? (s/n): ", produtos[i].estoque);
                getchar(); 
                scanf("%c", &opcao);
                if (opcao == 's' || opcao == 'S') {
                    float total = produtos[i].estoque * produtos[i].valorUnitario;
                    produtos[i].estoque = 0;
                    printf("Venda parcial realizada! Valor a pagar: R$ %.2f\n", total);
                } else {
                    printf("Venda cancelada.\n");
                }
                return;
            }
        }
    }
    printf("Produto nao encontrado.\n");
}

void atualizarEstoque(struct Produto produtos[], int quantidade, int codigo) {
    int i, novaQtd;
    for (i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Estoque atual: %d\n", produtos[i].estoque);
            printf("Nova quantidade: ");
            scanf("%d", &novaQtd);
            produtos[i].estoque = novaQtd;
            printf("Estoque atualizado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void exibirTodos(struct Produto produtos[], int quantidade) {
    printf("\nLista de produtos:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Codigo: %d - %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

void exibirZerados(struct Produto produtos[], int quantidade) {
    printf("\nProdutos com estoque zerado:\n");
    int achou = 0;
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].estoque == 0) {
            printf("Codigo: %d - %s\n", produtos[i].codigo, produtos[i].descricao);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhum produto com estoque zerado.\n");
    }
}

int main() {
    struct Produto produtos[TAM];
    int quantidade = 0;
    int opcao, codigo, qtd;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Alterar valor unitario\n");
        printf("3 - Consultar valor unitario\n");
        printf("4 - Consultar estoque\n");
        printf("5 - Vender produto\n");
        printf("6 - Atualizar estoque\n");
        printf("7 - Exibir todos os produtos\n");
        printf("8 - Exibir produtos com estoque zerado\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &quantidade);
                break;
            case 2:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                alterarValor(produtos, quantidade, codigo);
                break;
            case 3:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                float valor;
                valor = obterValor(produtos, quantidade, codigo);
                if (valor >= 0)
                    printf("Valor unitario: R$ %.2f\n", valor);
                else
                    printf("Produto nao encontrado.\n");
                break;
            case 4:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                int estoque;
                estoque = obterEstoque(produtos, quantidade, codigo);
                if (estoque >= 0)
                    printf("Quantidade em estoque: %d\n", estoque);
                else
                    printf("Produto nao encontrado.\n");
                break;
            case 5:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                printf("Quantidade desejada: ");
                scanf("%d", &qtd);
                venderProduto(produtos, quantidade, codigo, qtd);
                break;
            case 6:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                atualizarEstoque(produtos, quantidade, codigo);
                break;
            case 7:
                exibirTodos(produtos, quantidade);
                break;
            case 8:
                exibirZerados(produtos, quantidade);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
