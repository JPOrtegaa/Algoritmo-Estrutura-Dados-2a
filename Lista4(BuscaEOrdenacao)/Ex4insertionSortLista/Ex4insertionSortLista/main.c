#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int info;
    struct no *prox;
    struct no *ant;
} Lista;

Lista* insereLista(Lista *l, int info){
    Lista *aux, *p;
    aux = (Lista *) malloc(sizeof(Lista));
    aux->info = info;
    aux->prox = NULL;
    if(l == NULL){ // caso a lista esteja vazia!!
        aux->ant = NULL;
        return aux;
    }
    p = l;
    while(p->prox != NULL)
        p = p->prox;
    p->prox = aux;
    aux->ant = p;
    return l;
}

Lista* insertionSort(Lista *l){
    Lista *i, *j, *elemento;
    i = l->prox;
    while(i != NULL){
        elemento = i; // elemento a ser analisado!!
        j = elemento->ant;   // avalia os elementos anteriores!!
        j->prox = elemento->prox; // retira o elemento analisado, para ser colocado no local correto da lista!!
        if(elemento->prox != NULL)
            elemento->prox->ant = j;  // retira o elemento analisado, para ser colocado no local correto da lista!!
        while(j != NULL){
            if(elemento->info > j->info)
                break;
            j = j->ant;
        }
        if(j == NULL){ // caso seja o menor numero, o elemento deve ser inserido na cabeca!!
            i = elemento->prox;
            elemento->ant = NULL;
            elemento->prox = l;
            l->ant = elemento;
            l = elemento;
        }
        else{ // elemento inserido no meio da lista, fazendo o encadeamento correto!!
            i = elemento->prox;
            elemento->prox = j->prox;
            if(j->prox != NULL) // caso o elemento seja o ultimo!!
                j->prox->ant = elemento;
            j->prox = elemento;
            elemento->ant = j;
        }
    }
    return l;
}

void imprimeLista(Lista *l){
    while(l != NULL){
        printf("%d ", l->info);
        l = l->prox;
    }
    printf("\n");
}

int main(){
    Lista *l = NULL;

    l = insereLista(l, 2);
    l = insereLista(l, 4);
    l = insereLista(l, 3);
    l = insereLista(l, 5);
    l = insereLista(l, 1);

    imprimeLista(l);

    l = insertionSort(l);


    imprimeLista(l);

    return 0;
}
