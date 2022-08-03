#ifndef CONJUNTO_H
#define CONJUNTO_H

typedef struct no{
    int info;
    struct no *prox;
} Lista;

Lista* inserir(Lista *l, int info);

int repetido(Lista *l, int info);

Lista* uniao(Lista *l1, Lista *l2);

Lista* intersecao(Lista *l1, Lista *l2);

Lista* diferenca(Lista *l1, Lista *l2);

int contido(Lista *l1, Lista *l2);

void imprimir(Lista *l);

#endif // CONJUNTO_H
