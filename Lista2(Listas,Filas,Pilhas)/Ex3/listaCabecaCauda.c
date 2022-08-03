#include "listaCabecaCauda.h"
#include <stdio.h>
#include <stdlib.h>

Lista* inicializar(){
    Lista *aux;
    aux = (Lista *) malloc(sizeof(Lista));
    aux->cabeca = NULL;
    aux->cauda = NULL;
    return aux;
}

int vazia(Lista *l){
    if(l->cabeca == NULL)
        return 1;
    else
        return 0;
}

void imprimir(Lista *l){
    struct no *p;
    p = l->cabeca;
    while(p != l->cauda){
        printf("%d\n", p->info);
        p = p->prox;
    }
    printf("%d\n", l->cauda->info);
}

Lista* inserirCabeca(Lista *l, int info){
    struct no *aux = (struct no *) malloc(sizeof(struct no));
    aux->info = info;
    if(l->cabeca == NULL){ // caso a lista esteja vazia!!
        aux->prox = NULL;
        l->cabeca = l->cauda = aux;
        return l;
    }
    aux->prox = l->cabeca;
    l->cabeca = aux;
    return l;
}

Lista* inserirCauda(Lista *l, int info){
    struct no *aux;
    aux = (struct no *) malloc(sizeof(struct no));
    aux->info = info;
    aux->prox = NULL;
    if(l->cabeca == NULL){ // caso a lista esteja vazia!!
        l->cabeca = l->cauda = aux;
        return l;
    }
    l->cauda->prox = aux;
    l->cauda = aux;
    return l;
}

Lista* remover(Lista *l, int info){
    struct no *p, *ant;
    p = l->cabeca;
    ant = NULL;
    if(l->cabeca->info == info){ // caso esteja na cabeca!!
        l->cabeca = l->cabeca->prox;
        free(p);
        return l;
    }
    while(p->prox != NULL){ // ate a cauda, modificacao no meio da lista!!
        if(p->info == info){
            ant->prox = p->prox;
            free(p);
            return l;
        }
        ant = p;
        p = p->prox;
    }
    if(l->cauda->info == info){ // caso esteja na cauda!!
        ant->prox = l->cauda->prox;
        free(p);
        l->cauda = ant;
        return l;
    }
    printf("Elemento nao encontrado!!\n");
    return l;
}
