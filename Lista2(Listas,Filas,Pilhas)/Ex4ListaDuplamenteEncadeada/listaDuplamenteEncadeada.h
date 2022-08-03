#ifndef LISTADUPLAMENTEENCADEADA_H
#define LISTADUPLAMENTEENCADEADA_H

typedef struct no{
    int info;
    struct no *prox;
    struct no *ant;
} Lista;

int vazia(Lista *l);

Lista* inserirCabeca(Lista *l, int info);

Lista* inserirCauda(Lista *l, int info);

Lista* remover(Lista *l, int info);

Lista* removerRecursivo(Lista *l, int info, Lista *aux);

void imprimir(Lista *l);

void imprimirRecursivo(Lista *l);

Lista* inverter(Lista *l);

Lista* inverterRecursivo(Lista *l);

Lista* concatenar(Lista *l1, Lista *l2);

Lista* concatenarRecursivo(Lista *l1, Lista *l2);

Lista* intercalar(Lista *l1, Lista *l2);

Lista* intercalarRecursivo(Lista *l1, Lista *l2);

#endif // LISTADUPLAMENTEENCADEADA_H
