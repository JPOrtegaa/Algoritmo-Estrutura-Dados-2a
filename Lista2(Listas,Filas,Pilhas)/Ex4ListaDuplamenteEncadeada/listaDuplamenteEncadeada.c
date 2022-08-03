#include "listaDuplamenteEncadeada.h"
#include <stdio.h>
#include <stdlib.h>

int vazia(Lista *l){
    return (l == NULL);
}

Lista* inserirCabeca(Lista *l, int info){
    Lista *aux = (Lista *) malloc(sizeof(Lista));
    aux->info = info;
    aux->ant = NULL;
    aux->prox = l;
    if(!vazia(l)) // caso l seja NULL nao mexa na sua estrutura!!!
        l->ant = aux;
    return aux;
}

Lista* inserirCauda(Lista *l, int info){
    Lista *aux, *p;
    aux = (Lista *) malloc(sizeof(Lista));
    p = l;
    aux->info = info;
    aux->prox = NULL;
    if(vazia(l)){
        aux->ant = NULL;
        return aux;
    }
    while(p->prox != NULL)
        p = p->prox;
    p->prox = aux;
    aux->ant = p;
    return l;
}

Lista* remover(Lista *l, int info){
    Lista *p;
    p = l;
    if(!vazia(l)){
        if(l->info == info){
            if(l->prox == NULL){ // caso tenha somente a cabeca na lista, nao mexer no NULL, o qual nao tem estrutura alocada!!
                l = l->prox;
                free(p);
                return l;
            }
            l = l->prox;
            l->ant = NULL;
            free(p);
            return l;
        }
        while(p != NULL){
            if(p->info == info){
                p->ant->prox = p->prox;
                free(p);
                return l;
            }
            p = p->prox;
        }
        printf("Elemento nao encontrado!!\n");
        return l;
    }
    printf("Lista vazia!!\n");
    return l;
}

Lista* removerRecursivo(Lista *l, int info, Lista *aux){ // aux recebe copia da cabeca!!
    if(l->info == info){
        if(l->prox == NULL){
            l = l->prox;
            free(aux);
            return l;
        }
        l = l->prox;
        l->ant = NULL;
        free(aux);
        return l;
    }
    l->prox = removerRecursivo(l->prox, info, l->prox);
}

void imprimir(Lista *l){
    if(!vazia(l)){
        while(l != NULL){
            printf("%d\n", l->info);
            l = l->prox;
        }
        printf("\n\n");
    }
    else
        printf("Lista sem elementos para imprimir!!\n");
}

Lista* inverter(Lista *l){
    Lista *p, *aux;
    p = l;
    aux = NULL;
    if(!vazia(l)){
        while(p->prox != NULL){ // ate o ultimo elemento!!
            aux = p->ant;
            p->ant = p->prox;
            p->prox = aux;
            p = p->ant;
        }
        aux = p->ant;
        p->ant = p->prox;
        p->prox = aux;
        return p;
    }
    printf("Lista sem elementos para inverter!!\n");
    return l;
}

Lista* concatenar(Lista *l1, Lista *l2){
    Lista *aux = NULL;
    while(!vazia(l1)){
        aux = inserirCabeca(aux, l1->info);
        l1 = l1->prox;
    }
    while(!vazia(l2)){
        aux = inserirCabeca(aux, l2->info);
        l2 = l2->prox;
    }
    return aux;
}

Lista* intercalar(Lista *l1, Lista *l2){
    Lista *aux = NULL;
    while(!vazia(l1) && !vazia(l2)){
        aux = inserirCabeca(aux, l1->info);
        l1 = l1->prox;
        aux = inserirCabeca(aux, l2->info);
        l2 = l2->prox;
    }
    while(!vazia(l1)){
        aux = inserirCabeca(aux, l1->info);
        l1 = l1->prox;
    }
    while(!vazia(l2)){
        aux = inserirCabeca(aux, l2->info);
        l2 = l2->prox;
    }
    return aux;
}
