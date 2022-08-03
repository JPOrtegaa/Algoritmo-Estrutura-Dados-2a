#ifndef LISTACABECACAUDA_H
#define LISTACABECACAUDA_H

struct no{
    int info;
    struct no *prox;
};

typedef struct{
    struct no *cabeca;
    struct no *cauda;
} Lista;

Lista* inicializar();

int vazia(Lista *l);

void imprimir(Lista *l);

Lista* inserirCabeca(Lista *l, int info);

Lista* inserirCauda(Lista *l, int info);

Lista* remover(Lista *l, int info);

#endif // LISTACABECACAUDA_H
