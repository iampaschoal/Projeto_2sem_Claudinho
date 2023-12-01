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

typedef struct no
{
    struct no *esq;
    struct no *dir;
    produto dado;
    int total;
} Node;

void escreve_dados(Node *, FILE *);
void cadastro(Node **);
void removeproduto(Node **);
void alteraquantidade(Node **);
void alteranome(Node **);
void alterapeso(Node **);
void cria(Node **t);
int insere(Node **t, produto dado);
void preOrdem(Node *t);
void emOrdem(Node *t);
void emDesordem(Node *t);
void posOrdem(Node *t);

int main (void)
{
    char r;
    Node *p;
    int c = 0;
    FILE *fw;

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
            cadastro(&p);
            escreve_dados(p, &fw);
            break;

        case 2:
            removeproduto(&p);
            break;

        case 3:
            if(p->total <= 0)
            {
                printf("\nSem produtos para exibir! Cadastre produtos primeiro!\n");
                break;
            }

            break;

        case 4:
            alteranome(&p);
            break;

        case 5:
            alterapeso(&p);
            break;

        case 6:
            alteraquantidade(&p);
            break;

        case 7:
            printf("\nSaindo...");
            break;

        default:
            printf("\nDigite uma opcao valida\n\n");
        }
    }
    while(c != 7);

    return (0);
}

int insere(Node **t, produto dado)
{
    if (*t == NULL)
    {
        *t = (Node *)malloc(sizeof(Node));
        if (*t == NULL)
        {
            printf("Erro ao inserir\n");
            return 0;
        }
        (*t)->dado = dado;
        (*t)->esq = NULL;
        (*t)->dir = NULL;
        return 1;
    }
    if (dado.np < (*t)->dado.np)
        return insere(&(*t)->esq, dado);

    return insere(&(*t)->dir, dado);
}

void cadastro(Node **p)
{

    char r;
    int i = (*p)->total;
    printf("\n\nCadastro de produto\n");
    printf("\nDigite o nome do produto\n");
    scanf("%[^\n]s", &(*p)->dado.nome);
    getchar();

    printf("\nDigite a quantidade do produto\n");
    scanf("%d", &(*p)->dado.quantidade);
    getchar();

    printf("\nDigite o peso do produto\n");
    scanf("%f", &(*p)->dado.peso);
    getchar();

    ((*p)->total)++;
    i = (*p)->total;
    (*p)->dado.np = (*p)->total;

    printf("\nDeseja cadastrar outro produto? s/n\n");
    r = getchar();
    getchar();

    if(r == 's')
        cadastro(&p);

    return;
}

void alteranome(Node **p)
{
    int j, i;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);

    if(j > (*p)->total)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    if()

    printf("\nDigite o nome que voce deseja: ");
    scanf("%s", (*p)->dado.nome);
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
