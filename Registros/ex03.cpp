#include <stdio.h>
#include <string.h>

#define TAM 100

struct Conta {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[20];
    float saldo;
};

int buscarConta(struct Conta contas[], int qtd, int numero) {
    if (qtd == 0) return -1;
    for (int i = 0; i < qtd; i++) {
        if (contas[i].numero == numero)
            return i;
    }
    return -2;
}

void cadastrarConta(struct Conta contas[], int *qtd, int numero) {
    if (*qtd >= TAM) {
        printf("Limite de contas atingido!\n");
        return;
    }
    int pos = buscarConta(contas, *qtd, numero);
    if (pos >= 0) {
        printf("Conta ja cadastrada!\n");
        return;
    }

    contas[*qtd].numero = numero;

    getchar(); 
    printf("Nome: ");
    fgets(contas[*qtd].nome, 50, stdin);
    contas[*qtd].nome[strcspn(contas[*qtd].nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(contas[*qtd].cpf, 15, stdin);
    contas[*qtd].cpf[strcspn(contas[*qtd].cpf, "\n")] = '\0';

    printf("Telefone: ");
    fgets(contas[*qtd].telefone, 20, stdin);
    contas[*qtd].telefone[strcspn(contas[*qtd].telefone, "\n")] = '\0';

    printf("Saldo inicial: ");
    scanf("%f", &contas[*qtd].saldo);

    (*qtd)++;
    printf("Conta cadastrada com sucesso!\n");
}

void consultarSaldo(struct Conta contas[], int qtd, int numero) {
    int pos = buscarConta(contas, qtd, numero);
    if (pos >= 0) {
        printf("Saldo da conta %d: R$ %.2f\n", numero, contas[pos].saldo);
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void depositar(struct Conta contas[], int qtd, int numero) {
    int pos = buscarConta(contas, qtd, numero);
    if (pos >= 0) {
        float valor;
        printf("Valor do deposito: ");
        scanf("%f", &valor);
        contas[pos].saldo += valor;
        printf("Deposito realizado. Novo saldo: R$ %.2f\n", contas[pos].saldo);
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void sacar(struct Conta contas[], int qtd, int numero) {
    int pos = buscarConta(contas, qtd, numero);
    if (pos >= 0) {
        float valor;
        printf("Valor do saque: ");
        scanf("%f", &valor);
        if (valor <= contas[pos].saldo) {
            contas[pos].saldo -= valor;
            printf("Saque realizado. Novo saldo: R$ %.2f\n", contas[pos].saldo);
        } else {
            printf("Saldo insuficiente.\n");
        }
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void exibirContas(struct Conta contas[], int qtd) {
    if (qtd == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("Conta: %d | Nome: %s | Telefone: %s\n",
               contas[i].numero, contas[i].nome, contas[i].telefone);
    }
}

int main() {
    struct Conta contasCorrente[TAM];
    struct Conta contasPoupanca[TAM];
    int qtdCorrente = 0, qtdPoupanca = 0;
    int opcao, tipo, numero;

    do {
        printf("\n===== MENU BANCO DINHEIRO CERTO =====\n");
        printf("1 - Cadastrar nova conta\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Depositar\n");
        printf("4 - Sacar\n");
        printf("5 - Exibir contas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            printf("Tipo de conta (1 - Corrente | 2 - Poupanca): ");
            scanf("%d", &tipo);
        }

        switch (opcao) {
            case 1:
                printf("Numero da nova conta: ");
                scanf("%d", &numero);
                if (tipo == 1)
                    cadastrarConta(contasCorrente, &qtdCorrente, numero);
                else
                    cadastrarConta(contasPoupanca, &qtdPoupanca, numero);
                break;

            case 2:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                if (tipo == 1)
                    consultarSaldo(contasCorrente, qtdCorrente, numero);
                else
                    consultarSaldo(contasPoupanca, qtdPoupanca, numero);
                break;

            case 3:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                if (tipo == 1)
                    depositar(contasCorrente, qtdCorrente, numero);
                else
                    depositar(contasPoupanca, qtdPoupanca, numero);
                break;

            case 4:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                if (tipo == 1)
                    sacar(contasCorrente, qtdCorrente, numero);
                else
                    sacar(contasPoupanca, qtdPoupanca, numero);
                break;

            case 5:
                if (tipo == 1)
                    exibirContas(contasCorrente, qtdCorrente);
                else
                    exibirContas(contasPoupanca, qtdPoupanca);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
