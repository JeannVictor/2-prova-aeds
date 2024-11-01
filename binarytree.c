#include <stdlib.h>
#include <stdio.h>

typedef struct no no;
struct no
{
    int valor;
    no *dir;
    no *esq;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Versão recursiva!
no *insere(no *raiz, no *n)
{
    if (raiz == NULL) // Verifica se a árvore binaria possui algo.
    {
        return n; // Como não tem, o novo nó é raiz.
    }
    if (raiz->valor > n->valor) // É verificado se o novo nó é maior ou menor que a raiz.
    {
        raiz->esq = (insere(raiz->esq, n)); // Sendo menor, o novo nó é adicionado a esquerda.
                                            // É necessaria a recursividade pois caso a raiz esq possua outros filhos
        // é  necessario verificar onde exatamente ele se encaixaria.
    }
    else // Sendo maior.
    {
        raiz->dir = (insere(raiz->dir, n)); // Sendo menor, o novo nó é adicionado a direita.
                                            // É necessaria a recursividade pois caso a raiz dir possua outros filhos
        // é  necessario verificar onde exatamente ele se encaixaria.
    }
    return raiz; //  Retorna o endereço do nó para o nível superior, onde ele será apontado pelo seu pai
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BUSCAS

// Versão Recursiva da Busca!
no *buscaR(no *raiz, int k)
{
    if (raiz == NULL || raiz->valor == k) // Se a árvore não existir,não há nada para buscar! Se a raiz for o numero buscado.
    {
        return raiz; // Em ambos os casos do if,se retorna a raiz.
    }
    if (raiz->valor > k) // Se o valor da raiz for maior que o do nó procurado.
    {
        return buscaR(raiz->esq, k); // É feita a recursividade no lado esquerdo da raiz.
    }
    else
    {
        return buscaR(raiz->dir, k); // É feita a recursividade no lado esquerdo da raiz.
    }
}

// Versão Interativa da Busca!
no *buscaI(no *raiz, int k)
{
    // Faz um loop para rodar enquanto existir uma árvore e enquanto o nó buscado não for encontrado.
    while (raiz != NULL && raiz->valor != k)
    {
        if (k > raiz->valor) // Se K é maior que a raíz.
        {
            raiz = raiz->dir; // A raíz recebe o seu galho a direita.
        }
        else
        {
            raiz = raiz->esq; // A raíz recebe o seu galho a direita.
        }
    }
    return raiz; // Retorna onde K está ou NULL.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REMOÇÃO
no *buscaPaiR(no *raiz, no *n)
{
    // Verifica se existe uma árvore, se a busca for a raíz ela não tem pai.
    if (raiz == NULL || raiz == n)
    {
        return NULL; // Ou não tem arvore ou a busca é a raíz que não tem pai.
    }
    // Verifica se o o lado esquerdo ou direito da raiz é o valor buscado.
    if (raiz->esq == n || raiz->dir == n)
    {
        return raiz; // Se for, o pai dele é a raíz.
    }
    if (n->valor > raiz->valor) // Se o nó buscado for maior que a raíz.
    {
        return buscaPaiR(raiz->dir, n); // É feita a recursividade no lado direito da raíz.
    }
    else
    {
        return buscaPaiR(raiz->esq, n); // É feita a recursividade no lado esquerdo da raíz.
    }
}
no *buscaPaiI(no *raiz, no *n)
{
    while (raiz != NULL && raiz != n)
    {
        // Verifica se o o lado esquerdo ou direito da raiz é o valor buscado.
        if (raiz->esq == n || raiz->dir == n)
        {
            return raiz; // Se for, o pai dele é a raíz.
        }
        if (n->valor > raiz->valor) // Verifica se o novo nó é maior que a raíz.
        {
            raiz = raiz->dir; // A raíz recebe o seu nó a direita.
        }
        else
        {
            raiz = raiz->esq; // A raíz recebe o seu nó a esquerda.
        }
    }
    return NULL;
}
no *removeraiz(no *raiz)
{
    no *p, *q;
    if (raiz->esq == NULL) // Se o lado esquerdo da raiz não ter nada.
    {
        q = raiz->dir; // Q irá receber a primeiro nó da direita.
        free(raiz);    // Irá liberar mémoria.
        return (q);    // E assim a raíz sera removida,e as mudanças da árvore seram feitas.
    }

    p = raiz;
    q = raiz->esq;
    // Esse Loop serve para procurar o nó mais a direita do lado esquerdo(o de maior valor).
    while (q->dir != NULL) // Enquanto o lado direito de Q for diferente de NULL.
    {
        p = q;      // A raiz agora é o seu nó a esquerda.
        q = q->dir; // E o nó a esquerda agora é o nó dele mesmo á direita.
    }

    if (p != raiz) // Se p não é a raíz.
    {
        p->dir = q->esq;    //
        q->esq = raiz->esq; //
    }
    q->dir = raiz->dir;
    free(raiz); // Libera mémoria da raiz.
    return q;   // Q agora é a nova raíz da árvore.
}

no *removeNo(no *raiz, int k)
{
    no *n = buscaI(raiz, k); // Verifica se o nó existe.
    if (n)                   // Se existir.
    {
        no *pai = buscaPaiI(raiz, n); // Descobre qual é o nó pai.
        if (pai)                      // caso tenha nó pai
        {
            if (pai->dir == n) // O nó a ser removido é filho a direita.
                pai->dir = removeraiz(n);
            else // O nó a ser removido é filho a esquerda.
                pai->esq = removeraiz(n);
        }
        else
        {
            raiz = removeraiz(n); // Não possui pai, logo, é o próprio nó raiz.
        }
    }
    return raiz;
}

void imprimePreOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor); // Imprime a raiz
        imprimePreOrdem(raiz->esq); // Recursão no lado esquerdo
        imprimePreOrdem(raiz->dir); // Recursão no lado direito
    }
}

int main()
{
    int a = 0, x;
    no *raiz = NULL, *n;

    while (a >= 0)
    {
        scanf("%d", &a);

        switch (a)
        {
        case 1:
            n = malloc(sizeof(no));
            n->dir = NULL;
            n->esq = NULL;
            printf("Digite o no que deseja adicionar.\n");
            scanf("%d", &n->valor);
            raiz = insere(raiz, n);
            printf("O no foi adicionado com sucesso!\n");
            break;

        case 2:
            printf("Qual no voce deseja remover?\n");
            scanf("%d", &x);

            // Primeiro verifica se o elemento existe
            no *elemento = buscaI(raiz, x);
            if (elemento == NULL)
            {
                printf("Elemento nao encontrado!\n\n");
            }
            else
            {
                raiz = removeNo(raiz, x);
                if (raiz == NULL)
                {
                    printf("Elemento removido. Arvore ficou vazia!\n\n");
                }
                else
                {
                    printf("Elemento removido com sucesso!\n\n");
                }
            }
            break;
        }
    }
    imprimePreOrdem(raiz);
    return 0;
}
