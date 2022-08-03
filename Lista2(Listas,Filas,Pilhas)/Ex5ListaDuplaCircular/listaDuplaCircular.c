#include "listaDuplaCircular.h"
#include <stdio.h>
#include <stdlib.h>

int vazia(Lista *l){
    return (l == NULL);
}

Lista* inserirCabeca(Lista *l, int info){
    Lista *aux = (Lista *) malloc(sizeof(Lista));
    Lista *p = l;
    aux->info = info;
    if(vazia(l)){
        aux->prox = aux;
        aux->ant = aux;
        return aux;
    }
    aux->prox = l;
    aux->ant = l->ant;
    l->ant = aux;
    while(p->prox != l) // manter a circularidade da lista!!
        p = p->prox;
    p->prox = aux;
    return aux;
}

Lista* inserirCauda(Lista *l, int info){
    Lista *aux = (Lista *) malloc(sizeof(Lista));
    Lista *p = l;
    aux->info = info;
    if(vazia(l)){
        aux->prox = aux;
        aux->ant = aux;
        return aux;
    }
    while(p->prox != l)
        p = p->prox;
    p->prox = aux;
    aux->prox = l;
    aux->ant = p;
    l->ant = aux;
    return l;
}

Lista* removerCabeca(Lista *l, Lista *p){
    if(l == l->prox){
        free(l);
        return NULL;
    }
    l = l->prox;
    l->ant = p->ant;
    p->ant->prox = l;
    free(p);
    return l;
}

Lista* removerMeio(Lista *l, Lista *p){
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    free(p);
    return l;
}

Lista* removerCauda(Lista *l, Lista *p){
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    free(p);
    return l;
}

Lista* removerModularizado(Lista *l, int info){
    Lista *p = l;
    if(!vazia(l)){
        if(l->info == info){
            l = removerCabeca(l, p);
            return l;
        }
        while(p->prox != l){
            if(p->info == info){
                l = removerMeio(l, p);
                return l;
            }
            p = p->prox;
        }
        if(p->info == info){ // remocao na cauda!!
            l = removerCauda(l, p);
            return l;
        }
        printf("Elemento nao encontrado!!\n");
        return l;
    }
    else
        printf("Nao tem elementos para remover!!\n");
    return NULL;
}

Lista* remover(Lista *l, int info){
    Lista *p = l;
    if(!vazia(l)){
        if(l->info == info){ // remocao na cabeca!!
            if(l == l->prox){ // caso tenha somente um elemento na lista, eh preciso reseta-la!!
                free(l);
                return NULL;
            }
            l = l->prox;
            l->ant = p->ant;
            p->ant->prox = l;
            free(p);
            return l;
        }
        while(p->prox != l){ // remocao no meio!!
            if(p->info == info){
                p->ant->prox = p->prox;
                p->prox->ant = p->ant;
                free(p);
                return l;
            }
            p = p->prox;
        }
        if(p->info == info){ // remocao na cauda!!
            p->ant->prox = p->prox;
            p->prox->ant = p->ant;
            free(p);
            return l;
        }
        printf("Elemento nao encontrado!!\n");
        return l;
    }
    else
        printf("Nao tem elementos para remover!!\n");
    return NULL;
}


void imprimir(Lista *l){
    Lista *p, *aux;
    p = aux = l;
    if(!vazia(l)){
        printf("%d\n", p->info);
        p = p->prox;
        while(p != aux){
            printf("%d\n", p->info);
            p = p->prox;
        }
        printf("\n\n");
    }
    else
        printf("Lista vazia!!\n\n");
}
