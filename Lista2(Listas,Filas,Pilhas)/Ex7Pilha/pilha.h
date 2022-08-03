#ifndef PILHA_H
#define PILHA_H

struct no{
    int info;
    struct no *prox;
};

typedef struct{
    struct no *topo;
} Pilha;

Pilha* inicializar();

int vazia(Pilha *p);

void push(Pilha *p, int info);

void pop(Pilha *p);

int topo(Pilha *p);

void imprimir(Pilha *p);

#endif // PILHA_H
