#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

Fila* inicializar(){
    Fila *aux = (Fila *) malloc(sizeof(Fila));
    aux->n = 0;
    aux->prim = NULL;
    aux->ultimo = NULL;
    return aux;
}

int vazia(Fila *f){
    return (f->n == 0 || f->prim == NULL);
}

void enqueue(Fila *f, int info){
    struct no *aux = (struct no *) malloc(sizeof(struct no));
    aux->info = info;
    aux->prox = NULL;
    if(vazia(f)){
        f->prim = f->ultimo = aux;
        f->n++;
    }
    else{
        f->ultimo->prox = aux;
        f->ultimo = aux;
        f->n++;
    }
}

void dequeue(Fila *f){
    struct no *p;
    p = f->prim;
    if(!vazia(f)){
        if(f->prim == f->ultimo){ // caso tenha somente um elemento na fila!!
            f->prim = f->ultimo = NULL;
            f->n--;
            free(p);
        }
        else{
            p = f->prim->prox;
            free(f->prim);
            f->prim = p;
            f->n--;
        }
    }
    else
        printf("Fila vazia!!\n");
}

void imprimir(Fila *f){
    struct no *p = f->prim;
    printf("Tamanho da Fila = %d\n", f->n);
    while(p != NULL){
        printf("%d\n", p->info);
        p = p->prox;
    }
}

struct no* achaElemento(struct no *p, int n){
    while(n--)
        p = p->prox;
    return p;
}

void inverte(Fila *f){
    int n, tamanhoOriginal;
    struct no *p;
    tamanhoOriginal = f->n;
    n = tamanhoOriginal-1;
    p = f->prim;
    if(f->prim == f->ultimo)
        printf("Nao eh preciso inverter!!\n");
    else{
        while(n--){
            p = achaElemento(p, n); // acha elemento para enfileirar!!
            enqueue(f, p->info);
            p = f->prim;
        }
        n = tamanhoOriginal-1;
        while(n--) // desenfileira a fila antiga!!
            dequeue(f);
    }
}
