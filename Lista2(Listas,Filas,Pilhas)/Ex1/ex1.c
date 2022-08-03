#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"

int vazia(Lista *l){
    if(l == NULL)
        return 1;
    else
        return 0;
}

Lista* inserirCabeca(Lista *l, int info){
    Lista *aux = (Lista *) malloc(sizeof(Lista));
    aux->info = info;
    aux->prox = l;
    return aux;
}

Lista* inserirCauda(Lista *l, int info){
    Lista *aux = (Lista *) malloc(sizeof(Lista));
    Lista *p = l;
    aux->info = info;
    aux->prox = NULL;
    if(l == NULL){
        l = aux;
        return l;
    }
    while(p->prox != NULL) // ate encontrar o ultimo no!!!
        p = p->prox;
    p->prox = aux;
    return l;
}

Lista* inserirOrdenado(Lista *l, int info){
    Lista *aux, *p, *ant;
    p = l;
    ant = NULL;
    aux = (Lista *) malloc(sizeof(Lista));
    aux->info = info;
    if(vazia(l)){ // caso a lista seja vazia, novo elemento sera a nova cabeca!!
        aux->prox = NULL;
        l = aux;
        return aux;
    }
    if(aux->info < l->info){ // caso seja feita alteracao logo na cabeca, aux vira nova cabeca!!!
        aux->prox = l;
        return aux;
    }
    while(p != NULL){
        if(aux->info < p->info){
           ant->prox = aux;
           aux->prox = p;
           return l;
        }
        ant = p;
        p = p->prox;
    }
    ant->prox = aux;
    aux->prox = NULL;
    return l;
}

Lista* remover(Lista *l, int info){
    Lista *p, *ant;
    p = l;
    ant = NULL;
    if(l->info == info){ // remocao na cabeca!!
        l = l->prox;
        free(p);
        return l;
    }
    while(p != NULL && p->info != info){ // remocao no meio!!
        ant = p;
        p = p->prox;
    }
    if(p == NULL)
        printf("Elemento nao encontrado!!\n");
    else{
        ant->prox = p->prox;
        free(p);
    }
    return l;
}

Lista* removerRecursivo(Lista *l, int info, Lista *p, Lista *ant){
    if(l->info == info){
        l = l->prox;
        free(p);
        return l;
    }
    if(p == NULL){
        printf("Elemento nao encontrado!!\n");
        return l;
    }
    if(p->info == info){
        ant->prox = p->prox;
        free(p);
        return l;
    }
    return removerRecursivo(l, info, p->prox, p);
}

Lista* removerTodos(Lista *l, int info){
    Lista *p, *ant;
    p = l;
    ant = NULL;
}

void imprimir(Lista *l){
    while(!vazia(l)){
        printf("%d\n", l->info);
        l = l->prox;
    }
}

void imprimirRecursivo(Lista *l){
    if(!vazia(l)){
        printf("%d\n", l->info);
        return imprimirRecursivo(l->prox);
    }
}

Lista* inverter(Lista *l){
    Lista *ant, *atual, *prox;
    ant = NULL;
    atual = l;
    prox = NULL;
    while(atual != NULL){
        prox = atual->prox;
        atual->prox = ant;
        ant = atual;
        atual = prox;
    }
    return ant;
}

Lista* inverterRecursivo(Lista *l, Lista *ant, Lista *atual, Lista *prox){
    if(atual != NULL){
        prox = atual->prox;
        atual->prox = ant;
        ant = atual;
        atual = prox;
        return inverterRecursivo(l, ant, atual, prox);
    }
    else
        return ant;
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

Lista* concatenarRecursivo(Lista *l1, Lista *l2, Lista *aux){
    if(!vazia(l1)){
        aux = inserirCauda(aux, l1->info);
        return concatenarRecursivo(l1->prox, l2, aux);
    }
    if(!vazia(l2)){
        aux = inserirCauda(aux, l2->info);
        return concatenarRecursivo(l1, l2->prox, aux);
    }
    return aux;
}

Lista* concatenarAoFinal(Lista *l1, Lista *l2){
    Lista *aux = NULL;
    while(!vazia(l1)){
        aux = inserirCauda(aux, l1->info);
        l1 = l1->prox;
    }
    while(!vazia(l2)){
        aux = inserirCauda(aux, l2->info);
        l2 = l2->prox;
    }
    return aux;
}

Lista* intercalar(Lista *l1, Lista *l2){
    int i;
    Lista *aux = NULL;
    for(i = 0; !vazia(l1) && !vazia(l2); i++){
        if(i % 2 == 0){
            aux = inserirCabeca(aux, l1->info);
            l1 = l1->prox;
        }
        else{
            aux = inserirCabeca(aux, l2->info);
            l2 = l2->prox;
        }
    }
   if(!vazia(l1))
        while(!vazia(l1)){
            aux = inserirCabeca(aux, l1->info);
            l1 = l1->prox;
        }
    else
        while(!vazia(l2)){
            aux = inserirCabeca(aux, l2->info);
            l2 = l2->prox;
        }
    return aux;
}

Lista* intercalarRecursivo(Lista *l1, Lista *l2, Lista *aux, int i){
    if(!vazia(l1) && (i % 2 == 0)){
        aux = inserirCauda(aux, l1->info);
        return intercalarRecursivo(l1->prox, l2, aux, i+1);
    }
    if(!vazia(l2) && (i % 2 != 0)){
        aux = inserirCauda(aux, l2->info);
        return intercalarRecursivo(l1, l2->prox, aux, i+1);
    }
    return aux;
}

int contaOcorrencias(Lista *l, int x){
    int contador = 0;
    while(!vazia(l)){
        if(x == l->info)
            contador++;
        l = l->prox;
    }
    return contador;
}

Lista* pares(Lista *l){
    Lista *aux = NULL;
    while(!vazia(l)){
        if(l->info % 2 == 0)
            aux = inserirCauda(aux, l->info);
        l = l->prox;
    }
    return aux;
}
