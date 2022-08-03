#ifndef LISTADUPLACIRCULAR_H
#define LISTADUPLACIRCULAR_H

typedef struct no{
    int info;
    struct no *prox;
    struct no *ant;
} Lista;

int vazia(Lista *l);

Lista* inserirCabeca(Lista *l, int info);

Lista* inserirCauda(Lista *l, int info);

Lista* remover(Lista *l, int info);

Lista* removerModularizado(Lista *l, int info); // funcao remover modularizada!!

Lista* removerCabeca(Lista *l, Lista *p);

Lista* removerMeio(Lista *l, Lista *p);

Lista* removerCauda(Lista *l, Lista *p); // faz a mesma coisa que o removerMeio!!

void imprimir(Lista *l);

#endif // LISTADUPLACIRCULAR_H
