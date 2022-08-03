#ifndef FILA_H
#define FILA_H

struct no{
    int info;
    struct no *prox;
};

typedef struct{
    int n; // numero de elementos!!
    struct no *prim;
    struct no *ultimo;
} Fila;

Fila* inicializar();

int vazia(Fila *f);

void enqueue(Fila *f, int info);

void dequeue(Fila *f);

void imprimir(Fila *f);

struct no* achaElemento(struct no *p, int n); // funcao de apoio para realizar inverte Fila!!

void inverte(Fila *f);

#endif // FILA_H
