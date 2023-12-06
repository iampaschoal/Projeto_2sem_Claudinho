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
} Node;

void liberaMemoria(Node *);
void liberaArvore(Node **p);
Node * procuraProd(int *, Node **);
void escreve_dados(Node *, FILE *);
void cadastro(Node **, int *);
void removeproduto(Node **);
void alteraquantidade(Node **p, int* total);
void alteranome(Node **);
void alterapeso(Node **, int* );
int insere(Node **, produto );
void preOrdem(Node *);
void cria(Node **);
Node* encontrarMinimo(Node* no);
Node* apagarNo(Node* raiz, int codigo);

int main (void)
{
    char r;
    Node *p;
    int c = 0;
    FILE *fw;
    int *total;

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
            cadastro(&p, total);

            break;

        case 2:
            removeproduto(&p);
            break;

        case 3:
            if(total <= 0)
            {
                printf("\nSem produtos para exibir! Cadastre produtos primeiro!\n");
                break;
            }
            preOrdem(p);
            break;

        case 4:
            alteranome(&p);
            break;

        case 5:
            alterapeso(&p, total);
            break;

        case 6:
            alteraquantidade(&p, total);
            break;

        case 7:
            printf("\nSaindo...");
            break;

        default:
            printf("\nDigite uma opcao valida\n\n");
        }
    }
    while(c != 7);

    liberaArvore(&p);

    return (0);
}

void cria(Node **t)
{
    *t = NULL;
}

int insere(Node **t, produto dado)
{
    if (*t == NULL)
    {
        cria(t);
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

    if (dado.np % 2 == 1)
        return insere(&(*t)->esq, dado);

    return insere(&(*t)->dir, dado);
}

void cadastro(Node **p, int *total)
{

    char r;
    produto t;

    printf("\n\nCadastro de produto\n");
    printf("\nDigite o nome do produto\n");
    scanf("%[^\n]s", &t.nome);
    getchar();

    printf("\nDigite a quantidade do produto\n");
    scanf("%d", &t.quantidade);
    getchar();

    printf("\nDigite o peso do produto\n");
    scanf("%f", &t.peso);
    getchar();


    printf("\nDeseja cadastrar outro produto? s/n\n");
    r = getchar();
    getchar();

    if(r == 's')
        cadastro(&(*p), total);

    return;
}

void preOrdem(Node *t)
{
    if (t != NULL)
    {
        printf("%s ", t->dado.nome);
        printf("%i ", t->dado.np);
        printf("%f ", t->dado.peso);
        printf("%i ", t->dado.quantidade);
        preOrdem(t->esq);
        preOrdem(t->dir);
    }
}



void alteranome(Node **p)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);

    Node *produto = procuraProd(&j, p);

    if (produto->dado.np == -1)
    {
        printf("\nProduto nao cadastrado!!\n");
        return;
    }

    printf("\nDigite o nome que voce deseja: ");
    scanf("%29[^\n]", produto->dado.nome);
    printf("\nSalvo com sucesso!\n");
}

void alteraquantidade(Node **p, int* total)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);
    if (j > *total)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }
    printf("\nDigite a quantidade que voce deseja: ");
    scanf("%d", &(*p)->dado.quantidade);
    printf("\nSalvo com sucesso!");
}

void alterapeso(Node **p, int *total)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);
    if(j > *total)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }
    printf("\nDigite o peso que voce deseja: ");
    scanf("%f", &(*p)->dado.peso);
    printf("\nSalvo com sucesso!");
}

Node* encontrarMinimo(Node* no) {
    while (no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

Node* apagarNo(Node* raiz, int codigo) {
    if (raiz == NULL) {
        printf("Produto não encontrado.\n");
        return raiz;
    }

    if (codigo < raiz->dado.np) {
        raiz->esq = apagarNo(raiz->esq, codigo);
    } else if (codigo > raiz->dado.np) {
        raiz->dir = apagarNo(raiz->dir, codigo);
    } else {
        // Caso 1: Nó sem filhos ou com apenas um filho
        if (raiz->esq == NULL) {
            Node* temp = raiz->dir;
            free(raiz);
            printf("Produto removido com sucesso!\n");
            return temp;
        } else if (raiz->dir == NULL) {
            Node* temp = raiz->esq;
            free(raiz);
            printf("Produto removido com sucesso!\n");
            return temp;
        }

        // Caso 2: Nó com dois filhos
        Node* temp = encontrarMinimo(raiz->dir); // Encontrar o nó sucessor (menor valor na subárvore direita)

        // Copiar os dados do sucessor para este nó
        raiz->dado = temp->dado;

        // Apagar o sucessor
        raiz->dir = apagarNo(raiz->dir, temp->dado.np);
    }

    return raiz;
}

// Função para remover um produto
void removeproduto(Node **p)
{
    if (*p == NULL)
    {
        printf("\nEstoque vazio. Nada para remover.\n");
        return;
    }

    int j;
    printf("\nDigite o numero de produto do produto que voce deseja remover: ");
    scanf("%d", &j);

    *p = apagarNo(*p, j);
}



Node * procuraProd(int *i, Node **t)
{
    if ((*t) != NULL)
    {
        if((*t)->dado.np == *i)
            return (*t);

        procuraProd(i, &(*t)->esq);
        procuraProd(i, &(*t)->dir);
    }
    printf("Produto nao encontrado no estoque.\n");
    *i = -1;
    return (*t);
}

void liberaMemoria(Node *raiz) {
    if (raiz != NULL) {
        liberaMemoria(raiz->esq);
        liberaMemoria(raiz->dir);
        free(raiz);
    }
}

void liberaArvore(Node **p) {
    liberaMemoria(*p);
    *p = NULL;
}

/*void escreve_dados(Node *p, FILE *fw) {

    fw = fopen("produtos.txt", "w");

    if (fw == NULL) {
       perror("produtos.txt");
       exit(-1);
    }

    fwrite(p->dado.nome, sizeof(produto), MAX, fw);
    fwrite(p->dado.np, sizeof(produto), MAX, fw);
    fwrite(p->dado.peso, sizeof(produto), MAX, fw);
    fwrite(p->dado.quantidade, sizeof(produto), MAX, fw);
    fclose(fw);
    return;
}
*/
