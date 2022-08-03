#include "conjunto.h"
#include <stdio.h>
#include <stdlib.h>

int repetido(Lista *l, int info){
    while(l != NULL){
        if(info == l->info)
            return 1;
        l = l->prox;
    }
    return 0;
}

Lista* inserir(Lista *l, int info){
    Lista *aux, *p;
    p = l;
    if(l == NULL){ // insercao
        aux = (Lista *) malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = NULL;
        l = aux;
        return l;
    }
    if(!repetido(l, info)){
        aux = (Lista *) malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = NULL;
        while(p->prox != NULL)
            p = p->prox;
        p->prox = aux;
        return l;
    }
    else
        printf("Elemento repetido!\n");
    return l;
}

Lista* uniao(Lista *l1, Lista *l2){
    Lista *aux = NULL;
    while(l1 != NULL){
        aux = inserir(aux, l1->info);
        l1 = l1->prox;
    }
    while(l2 != NULL){
        aux = inserir(aux, l2->info);
        l2 = l2->prox;
    }
    return aux;
}

Lista* intersecao(Lista *l1, Lista *l2){
    Lista *aux = NULL;
    while(l1 != NULL){
        if(repetido(l2, l1->info))
            aux = inserir(aux, l1->info);
        l1 = l1->prox;
    }
    return aux;
}

Lista* diferenca(Lista *l1, Lista *l2){
    Lista *inter, *aux;
    inter = NULL;
    aux = NULL;
    inter = intersecao(l1, l2);
    while(l1 != NULL){
        if(!repetido(inter, l1->info))
            aux = inserir(aux, l1->info);
        l1 = l1->prox;
    }
    return aux;
}

int contido(Lista *l1, Lista *l2){
    while(l2 != NULL){
        if(!repetido(l1, l2->info))
            return 0;
        l2 = l2->prox;
    }
    return 1;
}

void imprimir(Lista *l){
    while(l != NULL){
        printf("%d\n", l->info);
        l = l->prox;
    }
}
