#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

Pilha* inicializar(){
    Pilha *aux = (Pilha *) malloc(sizeof(Pilha));
    aux->topo = NULL;
    return aux;
}

int vazia(Pilha *p){
    return (p->topo == NULL);
}

void push(Pilha *p, int info){
    struct no *aux = (struct no *) malloc(sizeof(struct no));
    aux->info = info;
    if(vazia(p)){
        aux->prox = NULL;
        p->topo = aux;
    }
    else{
        aux->prox = p->topo;
        p->topo = aux;
    }
}

void pop(Pilha *p){
    struct no *aux;
    aux = p->topo;
    if(!vazia(p)){
        p->topo = p->topo->prox;
        free(aux);
    }
    else
        printf("Pilha vazia!!\n");
}

int topo(Pilha *p){
    return p->topo->info;
}

void imprimir(Pilha *p){
    struct no *aux = p->topo;
    while(aux != NULL){
        printf("%d\n", aux->info);
        aux = aux->prox;
    }
}
