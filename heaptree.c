#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Funções auxuliares.

int HTAM = 1000;
// Retorna o pai.
int pai(int i)
{
    return (i - 1) / 2; // Tendo posição i,o pai dele esta na (i-1)/2.
}

// Retorna o filho a esquerda.
int fesq(int i)
{
    return (2 * i) + 1; // Tendo posição i,o filho esq dele esta na (2*i)+1
}

// Retorna o filho a direita.
int fdir(int i)
{
    return (2 * i) + 2; // Tendo posição i,o filho dir dele esta na (2*i)+2
}

void swap(int *filho, int *pai)
{
    int tmp = *filho; // Váriavel temporaria para guardar valor de filho.
    *filho = *pai;    // Filho recebe o valor do pai.
    *pai = tmp;       // Pai recebe o valor do filho.
}

void insereheap(int *n, int h[HTAM], int k)
{
    if (*n == HTAM) // Verifica se a heap possui espaço.
    {
        printf("Overflow, não foi possivel inserir o valor.\n");
        return;
    }
    // Insere o valor na última posição da heap.
    (*n)++;           // Adicionando um valor, a última posição do vetor passa pra seguinte.
    int i = (*n) - 1; // I é o indice onde ocorre a inserção ( a última posição da heap).
    h[i] = k;         // valor é inserido na posição correta.

    // ajusta caso necessario (pai não é menor que o filho, == min heap).
    while (i != 0 && h[pai(i)] > h[i]) // enquanto não chegar na raiz do heap e o pai for maior q o filho.
    {
        swap(&h[i], &h[pai(i)]); // troca pai c/filho.
        i = pai(i);              // repete função com pai.
    }
}

void minimizar(int i, int n, int h[HTAM])
{
    int e = fesq(i); // guarda posição do filho esquerdo de i.
    int d = fdir(i); // guarda posição do filho direito de i.
    int min = i;     // o valor minimo é iniciado como i, ele será comparado com seus filhos.

    if (e < n && h[e] < h[i])
        min = e; // o minimo é o esquerdo.
    if (d < n && h[d] < h[min])
        min = d;  // o minimo é o direito.
    if (min != i) // se algum filho tiver sido menor que o pai(quebrando a propiedade de min-heap).
    {
        swap(&h[i], &h[min]); // troca o pai com minimo.
        minimizar(min, n, h); // chama a função de minimização com o pai(agora filho).
    }
}

int removemin(int *n, int h[HTAM])
{
    if (*n <= 0)        // verifica se a heap tem algo.
        return INT_MAX; // age como uma mensagem de erro.

    if (*n == 1) // se só houver uma posição na heap.
    {
        (*n)--;      // a última muda para a anterior
        return h[0]; // retorna raiz
    }

    // se tiver mais de um valor,são realizados.
    int raiz = h[0];     // raiz é o valor h[0], que devera ser retornado.
    h[0] = h[(*n) - 1];  // o último valor do heap é enviado a raíz.
    (*n)--;              // a última posição muda para a anterior.
    minimizar(0, *n, h); // a função de correção é chamada,partindo da raiz.
    return raiz;         // retorna o valor mínimo.
}

// Função para imprimir a árvore heap
void imprimeheap(int n, int h[HTAM])
{
    printf("Heap atual: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", h[i]);
    }
    printf("\n");
}

int main()
{
    int h[HTAM];
    int n = 0; // Tamanho atual do heap
    int opcao, valor;

    while (1)
    {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar elemento\n");
        printf("2 - Remover elemento minimo\n");
        printf("3 - Sair e mostrar a arvore heap\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            insereheap(&n, h, valor);
            break;
        case 2:
            valor = removemin(&n, h);
            if (valor == INT_MAX)
            {
                printf("Heap esta vazio.\n");
            }
            else
            {
                printf("Elemento removido: %d\n", valor);
            }
            break;
        case 3:
            printf("Saindo...\n");
            imprimeheap(n, h);
            return 0;
        default:
            printf("Opção invalida. Tente novamente.\n");
        }
    }
    return 0;
}
