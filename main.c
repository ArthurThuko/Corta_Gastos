#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_NOME "banco_dados.txt"

typedef struct Gasto
{
    char nome[25];
    float valor;
} Gasto;

typedef struct No
{
    Gasto gasto;
    struct No *anterior;
    struct No *proximo;
} No;

No *criarNo(Gasto gasto)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->gasto = gasto;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
};

void inserirGasto(No **inicio, Gasto gasto)
{
    No *novo = criarNo(gasto);

    if (*inicio == NULL)
    {
        *inicio = novo;
        return;
    }

    No *atual = *inicio;

    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }

    atual->proximo = novo;
    novo->anterior = atual;
}

void exibirGastos(No *inicio)
{
    while (inicio != NULL)
    {
        printf("- %s: R$ %.2f\n", inicio->gasto.nome, inicio->gasto.valor);
        inicio = inicio->proximo;
    }
}

void excluirGasto(No **inicio, char nome[25])
{
    No *atual = *inicio;

    while (atual != NULL)
    {
        if (strcmp(atual->gasto.nome, nome) == 0)
        {
            if (atual->anterior == NULL && atual->proximo == NULL)
            {
                *inicio = NULL;
            }

            if (atual->anterior == NULL)
            {
                *inicio = atual->proximo;
                (*inicio)->anterior = NULL;
            }
            else if (atual->proximo == NULL)
            {
                atual->anterior->proximo = atual->proximo;
            }
            else
            {
                atual->anterior->proximo = atual->proximo;
                atual->proximo->anterior = atual->anterior;
            }

            free(atual);
            return;
        }

        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Nome do Gasto NAO encontrado!\n");
        return;
    }
}

void modificarGasto(No **inicio, Gasto gastomod, char nome[25])
{
    No *atual = *inicio;

    while (atual != NULL)
    {
        if (strcmp(atual->gasto.nome, nome) == 0)
        {
            strcpy(atual->gasto.nome, gastomod.nome);
            atual->gasto.valor = gastomod.valor;
            break;
        }

        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Nome do Gasto NAO encontrado!\n");
        return;
    }
    return;
}

void mostrarDados(No *inicio)
{
    double total = 0, media = 0;
    int quant = 0;

    while (inicio != NULL)
    {
        total += inicio->gasto.valor;
        quant++;

        inicio = inicio->proximo;
    }

    media = total / quant;

    printf("\nQuantidade de Gastos: %d\nSoma total dos Gastos: %.2f\nMedia dos Gastos: %.2f\n", quant, total, media);
}

void procurarGasto(No *inicio, char nome[25])
{
    double soma = 0;

    while (inicio != NULL)
    {
        if (strcmp(inicio->gasto.nome, nome) == 0)
        {
            soma += inicio->gasto.valor;
        }

        inicio = inicio->proximo;
    }

    printf("\nSoma total dos gasto sobre %s: %.2f\n", nome, soma);
}

void salvarGastos(No *inicio)
{
    FILE *arquivo = fopen(ARQUIVO_NOME, "w");

    while (inicio != NULL)
    {
        fprintf(arquivo, "%s\n%.2f\n", inicio->gasto.nome, inicio->gasto.valor);
        inicio = inicio->proximo;
    }

    fclose(arquivo);
}

void carregarGastos(No **inicio)
{
    FILE *arquivo = fopen(ARQUIVO_NOME, "r");

    if (arquivo == NULL)
    {
        return;
    }

    Gasto g;
    char linha[25];

    while (fgets(g.nome, sizeof(g.nome), arquivo) != NULL)
    {
        g.nome[strcspn(g.nome, "\n")] = '\0';

        if (fgets(linha, sizeof(linha), arquivo) != NULL)
        {
            g.valor = strtof(linha, NULL);
            inserirGasto(inicio, g);
        }
    }

    fclose(arquivo);
}

int main()
{
    int escolha;
    No *lista = NULL;
    Gasto gasto;
    char nome[25];

    printf("Seja Bem-Vindo ao Corta_Gastos\n");
    carregarGastos(&lista);

    do
    {
        printf("\n1 - Listar gastos\n2 - Incluir um novo gasto\n3 - Excluir um gasto\n4 - Modificar um gasto\n5 - Mostrar dados estatisticos\n6 - Procurar gasto especifico\n7 - Limpar Terminal\n0 - Encerrar aplicacao\n");

        printf("\nDigite sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            printf("Aplicacao encerrada!\n");

            salvarGastos(lista);

            break;
        case 1:
            printf("Listar Gastos!\n");

            exibirGastos(lista);

            break;
        case 2:
            printf("Incluir um novo gasto\n");

            printf("\nDigite o nome do gasto: ");
            scanf(" %25[^\n]", gasto.nome);

            printf("\nDigite o valor do gasto: ");
            scanf("%f", &gasto.valor);

            inserirGasto(&lista, gasto);

            break;
        case 3:
            printf("Excluir um gasto\n");

            printf("\nDigite o nome do gasto para ser excluido: ");
            scanf(" %25[^\n]", nome);

            excluirGasto(&lista, nome);

            break;
        case 4:
            printf("Modificar um gasto\n");

            printf("\nDigite o nome do gasto a ser modificado: ");
            scanf(" %25[^\n]", nome);

            printf("\nDigite o nome modificado: ");
            scanf(" %25[^\n]", gasto.nome);

            printf("\nDigite o valor modificado: ");
            scanf("%f", &gasto.valor);

            modificarGasto(&lista, gasto, nome);

            break;
        case 5:
            printf("Mostrar Dados estatisticos\n");

            mostrarDados(lista);

            break;
        case 6:
            printf("Procurar gastos especificos\n");

            printf("\nDigite o nome do gasto para ser procurado: ");
            scanf(" %25[^\n]", nome);

            procurarGasto(lista, nome);

            break;

        case 7:
            printf("Limpar o terminal\n");

            system("cls");

            break;
        default:
            printf("Escolha Inválida\n");
            break;
        }

    } while (escolha != 0);

    return 0;
}
