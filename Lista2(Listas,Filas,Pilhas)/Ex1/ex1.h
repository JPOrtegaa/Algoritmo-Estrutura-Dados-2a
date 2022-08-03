#ifndef EX1_H
#define EX1_H

typedef struct no{
    int info;
    struct no *prox;
}Lista;

int vazia(Lista *l);

Lista* inserirCabeca(Lista *l, int info);

Lista* inserirCauda(Lista *l, int info);

Lista* inserirOrdenado(Lista *l, int info);

Lista* remover(Lista *l, int info);

Lista* removerRecursivo(Lista *l, int info, Lista *p, Lista *ant);

Lista* removerTodos(Lista *l, int info);

void imprimir(Lista *l);

void imprimirRecursivo(Lista *l);

Lista* inverter(Lista *l);

Lista* inverterRecursivo(Lista *l, Lista *ant, Lista *atual, Lista *prox);

Lista* concatenar(Lista *l1, Lista *l2);

Lista* concatenarRecursivo(Lista *l1, Lista *l2, Lista *aux);

Lista* concatenarAoFinal(Lista *l1, Lista *l2);

Lista* intercalar(Lista *l1, Lista *l2);

Lista* intercalarRecursivo(Lista *l1, Lista *l2, Lista *aux, int i);

int contaOcorrencias(Lista *l, int x);

Lista* eliminaRepetidos(Lista *l);

Lista* pares(Lista *l);

#endif // EX1_H
