#include <stdio.h>
#include <stdlib.h>

#define MAX 40

typedef struct
{
    char nome[30];
    int np; //np = numero de produto
    int quantidade;
    float peso;
} produto;

typedef struct
{
    produto prod[MAX];
    int total;

} estoque;

void escreve_dados(estoque *, FILE *);
void cadastro(estoque *);
void printEstoque(int, estoque);
void removeproduto(estoque *);
void alteraquantidade(estoque *);
void alteranome(estoque *);
void alterapeso(estoque *);

int main (void)
{
    char r;
    estoque *p;
    int c = 0;
    FILE *fw;

    p = (estoque *)malloc(sizeof(estoque)*MAX);
    if (p == NULL)
    {
        // verificacao se houve erro na alocacao
        printf("ERRO: memoria insufiente");
        exit(1); // se sim, interrompe a execucao do programa
    }

    printf("Sistema de Estoque\n\n");
    printf("====================\n\n");


    do
    {

        printf("\nEscolha uma opcao que deseja\n_________________________________\n1-Cadastrar produto\n2- Remover produto\n3- Exibir produto\n4- Alterar nome de um produto\n5- Alterar peso de um produto\n6- Alterar quantidade de um produto\n7- Sair\nOpcao:");
        scanf("%d", &c);
        getchar();

        switch(c)
        {

        case 1:
            cadastro(&*p);
            escreve_dados(&*p, &*fw);
            break;

        case 2:
            removeproduto(&*p);
            break;

        case 3:
            if(p->total <= 0)
            {
                printf("\nSem produtos para exibir! Cadastre produtos primeiro!\n");
                break;
            }
            printEstoque(p->total, *p);
            break;

        case 4:
            alteranome(&*p);
            break;

        case 5:
            alterapeso(&*p);
            break;

        case 6:
            alteraquantidade(&*p);
            break;

        case 7:
            printf("\nSaindo...");
            break;

        default:
            printf("\nDigite uma opcao valida\n\n");
        }
    }
    while(c != 7);

    free(p);

    return (0);
}


void cadastro(estoque *p)
{

    char r;
    int i = p->total;
    printf("\n\nCadastro de produto\n");
    printf("\nDigite o nome do produto\n");
    scanf("%[^\n]s", p->prod[i].nome);
    getchar();

    printf("\nDigite a quantidade do produto\n");
    scanf("%d", &p->prod[i].quantidade);
    getchar();

    printf("\nDigite o peso do produto\n");
    scanf("%f", &p->prod[i].peso);
    getchar();

    (p->total)++;
    i = p->total;
    p->prod[i].np = p->total;

    printf("\nDeseja cadastrar outro produto? s/n\n");
    r = getchar();
    getchar();

    if(r == 's')
        cadastro(&*p);

    return;
}

void printEstoque(int j, estoque p)
{
    j = j-1;

    printf("\n=================================\n");
    printf("\nO nome do produto e %s\n", p.prod[j].nome);
    printf("\nO numero de produto e %i\n", p.prod[j].np);
    printf("\nHa %d produto(s)\n", p.prod[j].quantidade);
    printf("\nO peso do produto e %2.f\n", p.prod[j].peso);


    if(j <= 0)
        return;
    else
        printEstoque(j, p);

}

void alteranome(estoque *p)
{
    int j, i;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);

    if(j > p->total)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    printf("\nDigite o nome que voce deseja: ");
    scanf("%s", p->prod[j].nome);
    printf("\nSalvo com sucesso!");
    return;
}

void alteraquantidade(estoque *p)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);
    if(j > p->total)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }
    printf("\nDigite a quantidade que voce deseja: ");
    scanf("%d", &p->prod[j].quantidade);
    printf("\nSalvo com sucesso!");
}

void alterapeso(estoque *p)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);
    if(j > p->total)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }
    printf("\nDigite o peso que voce deseja: ");
    scanf("%f", &p->prod[j].peso);
    printf("\nSalvo com sucesso!");
}

void removeproduto(estoque *p)
{
    int codigo, m, j=0;
    printf("Digite o codigo do produto que deseja remover: ");
    scanf("%d", &codigo);

    for (m = 0; m < p->total; m++)
    {
        if (p->prod[m].np == codigo)
        {
            for (j = m; j < p->total - 1; j++)
            {
                p->prod[j] = p->prod[j + 1];
            }

            (p->total)--;
            printf("Produto removido com sucesso!\n");
            return;
        }
    }

    printf("Produto nao encontrado no estoque.\n");
}

void escreve_dados(estoque *p, FILE *fw) {

    fw = fopen("produtos.txt", "w");

    if (fw == NULL) {
       perror("produtos.txt");
       exit(-1);
    }

    fwrite(p->prod, sizeof(produto), MAX, fw);
    fclose(fw);
    return;
}
