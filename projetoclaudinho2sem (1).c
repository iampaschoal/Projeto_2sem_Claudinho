/* 
Participantes:
    Cesar Henrique Policarpo de Melo
    Pedro Henrique Franco Moreira Amaral
    Lucas Caiaffa Paschoalini
*/

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

//cadastro
void cadastro(Node **, int *);
int insere(Node **, produto , int*);

//remocao de produtos e alteracao de dados
void removeproduto(Node **);
void alteraquantidade(Node **, int* );
void alteranome(Node **);
void alterapeso(Node **, int* );
Node* apagarNo(Node* , int );

//backup e restauracao
void restauracao(Node **, int* );
void backup(Node *);
void escreve_dados(Node *, FILE *);

//funcoes auxiliares 
void liberaMemoria(Node *);
void liberaArvore(Node **);
int encontraTotal(Node* );
Node * procuraProd(int , Node **);
void preOrdem(Node *);
void cria(Node **);
Node* encontrarMinimo(Node* );

int main (void)
{
    char r;
    Node *p;
    int c = 0;
    int total = 0;

    printf("Sistema de Estoque\n\n");
    printf("====================\n\n");


    do
    {

        printf("\nEscolha uma opcao que deseja\n_________________________________\n1-Cadastrar produto\n2- Remover produto\n3- Exibir produto\n4- Alterar nome de um produto\n5- Alterar peso de um produto\n6- Alterar quantidade de um produto\n7- Fazer backup\n8- Carregar dados salvos\n9- Sair\nOpcao:");
        scanf("%d", &c);
        getchar();

        switch(c)
        {

        case 1:
            cadastro(&p, &total);

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
            alterapeso(&p, &total);
            break;

        case 6:
            alteraquantidade(&p, &total);
            break;

        case 7:
            printf("\nSalvando...");
            backup(p);
            break;

        case 8:
            printf("\nCarregando dados...");
            restauracao(&p, &total);
            break;

        case 9:
            printf("\nSaindo...");
            break;


        default:
            printf("\nDigite uma opcao valida\n\n");
        }
    }
    while(c != 9);

    liberaArvore(&p);

    return (0);
}

void cria(Node **t)
{
    *t = NULL;
}

int insere(Node **t, produto dado, int *total)
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
        *total = *total + 1;
        (*t)->dado = dado;
        (*t)->esq = NULL;
        (*t)->dir = NULL;

        return 1;
    }

    if (dado.np % 2 == 1)
        return insere(&(*t)->esq, dado, total);

    return insere(&(*t)->dir, dado, total);
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

    printf("\nDigite o numero do produto\n");
    scanf("%i", &t.np);
    getchar();

    insere(&(*p), t, total);

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
        printf("\nNome do produto: %s\n", t->dado.nome);
        printf("Numero de produto: %i\n", t->dado.np);
        printf("Peso do produto: %f\n", t->dado.peso);
        printf("Quantidade do produto: %i\n", t->dado.quantidade);
        preOrdem(t->esq);
        preOrdem(t->dir);
    }
}

void alteranome(Node **p)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);
    getchar();

    (*p) = procuraProd(j, p);

    printf("\nDigite o nome que voce deseja: ");
    scanf("%29[^\n]", (*p)->dado.nome);
    printf("\nSalvo com sucesso!\n");
}

void alteraquantidade(Node **p, int* total)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);
    getchar();

    (*p) = procuraProd(j, p);

    printf("\nDigite a quantidade que voce deseja: ");
    scanf("%d", &(*p)->dado.quantidade);
    printf("\nSalvo com sucesso!");
}

void alterapeso(Node **p, int *total)
{
    int j;
    printf("\nDigite o numero de produto do produto que voce deseja alterar: ");
    scanf("%d", &j);

    (*p) = procuraProd(j, p);

    printf("\nDigite o peso que voce deseja: ");
    scanf("%f", &(*p)->dado.peso);
    printf("\nSalvo com sucesso!");
}

Node* encontrarMinimo(Node* no)
{
    while (no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

int encontraTotal(Node* p)
{
    int aux = 0;
    if(p != NULL)
    {
        if(p->dado.np > aux)
                aux = p->dado.np;

        encontraTotal(p->esq);
        encontraTotal(p->dir);
    }
    return aux;
}

Node* apagarNo(Node* raiz, int codigo)
{

    if (raiz == NULL) {
        printf("Produto não encontrado.\n");
        return raiz;
    }

    if (codigo < raiz->dado.np) {
        raiz->esq = apagarNo(raiz->esq, codigo);
    } else if (codigo > raiz->dado.np){
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



 Node * procuraProd(int i, Node **t)
{
    if ((*t) != NULL)
    {
        if((*t)->dado.np == i)
            return (*t);

        procuraProd(i, &(*t)->esq);
        procuraProd(i, &(*t)->dir);
    }
    printf("Produto nao encontrado no estoque.\n");
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

void backup(Node *p) {
    FILE *backupFile = fopen("backup.txt", "wt");

    if (backupFile == NULL) {
        perror("backup.txt");
        return;
    }

    escreve_dados(p, backupFile);  // Use a função escreve_dados para escrever os dados no arquivo

    fclose(backupFile);
    printf("Backup realizado com sucesso!\n");
}

void restauracao(Node **p, int *total) {

    produto temp;
    *total = 0;
    FILE *backupFile = fopen("backup.txt", "rt");

    if (backupFile == NULL) {
        perror("backup.txt");
        return;
    }

    liberaArvore(p);  // Libera a árvore atual antes de restaurar os dados

    cria(p);  // Recria a árvore

    while (fscanf(backupFile, "%29s %d %f %d", &temp.nome, &temp.np, &temp.peso, &temp.quantidade) == 4) {
        insere(p, temp, total);  // Insere os dados na árvore
    }
    fclose(backupFile);
    printf("Restauração concluída com sucesso!\n");
}

void escreve_dados(Node *p, FILE *fw)
{
    if (p != NULL)
    {
        fprintf(fw,"%29s %d %f %d", p->dado.nome, p->dado.np, p->dado.peso, p->dado.quantidade);
        escreve_dados(p->esq, fw);
        escreve_dados(p->dir, fw);
    }
}
