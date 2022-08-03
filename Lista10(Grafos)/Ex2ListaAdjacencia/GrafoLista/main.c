#include <stdio.h>
#include <stdlib.h>

typedef struct{int v1; int v2;} Aresta;

typedef struct no{
    int v; // vertice
    struct no *prox;
} No;

struct grafo{
    No **array;
    int V; // total vertices
};

typedef struct grafo* Grafo;

Aresta criaAresta(int v1, int v2){
    Aresta e;
    e.v1 = v1;
    e.v2 = v2;

    return e;
}

No* criaNo(int v){
    No *x = (No *) malloc(sizeof(No));
    x->v = v;
    x->prox = NULL;

    return x;
}

Grafo inicializaGrafo(int V){
    Grafo g = (Grafo) malloc(sizeof(struct grafo));
    int i;

    g->V = V;
    g->array = (No **) malloc(sizeof(No*) * g->V);

    for(i = 0; i < g->V; i++){
        g->array[i] = (No *) malloc(sizeof(No));
        g->array[i]->v = -1;
        g->array[i]->prox = NULL;
    }

    return g;
}

void insereGrafo(Grafo g, Aresta e){
    No *i;
    if(e.v1 < g->V && e.v2 < g->V){
        i = g->array[e.v1];
        while(i->prox != NULL)
            i = i->prox;
        i->prox = criaNo(e.v2);

        i = g->array[e.v2];
        while(i->prox != NULL)
            i = i->prox;
        i->prox = criaNo(e.v1);
    }
    else
        printf("Aresta invalida!!\n");
}

void removeGrafo(Grafo g, Aresta e){
    No *i, *ant;
    if(e.v1 < g->V && e.v2 < g->V){
        ant = i = g->array[e.v1];
        while(i != NULL && i->v != e.v2){
            ant = i;
            i = i->prox;
        }
        if(i != NULL){
            ant->prox = i->prox;
            free(i);
        }

        ant = i = g->array[e.v2];
        while(i != NULL && i->v != e.v1){
            ant = i;
            i = i->prox;
        }
        if(i != NULL){
            ant->prox = i->prox;
            free(i);
        }
    }
    else
        printf("Aresta invalida!!\n");
}

int grafoArestas(Aresta e[], Grafo g){
    int i, total = 0;
    No *aux;
    for(i = 0; i < g->V; i++){
        aux = g->array[i]->prox;
        while(aux != NULL){
            if(aux->v >= i){
                e[total].v1 = i;
                e[total++].v2 = aux->v;
            }
            aux = aux->prox;
        }
    }
    return total;
}

void imprimirGrafo(Grafo g){
    int index;
    No *i;
    for(index = 0; index < g->V; index++){
        printf("Vertice %d:\n", index);
        i = g->array[index];
        while(i->prox != NULL){
            printf("%d -> %d\n", index, i->prox->v);
            i = i->prox;
        }
        printf("\n");
    }
}

int pertence(Grafo g, Aresta e){
    No *i;
    i = g->array[e.v1]->prox;
    while(i != NULL){
        if(i->v == e.v2)
            return 1;
        i = i->prox;
    }

    return 0;
}

int main(){
    Grafo g = inicializaGrafo(5);
    Aresta e[50];
    int totalAresta;

    insereGrafo(g, criaAresta(0, 1));
    insereGrafo(g, criaAresta(0, 4));
    insereGrafo(g, criaAresta(2, 3));
    insereGrafo(g, criaAresta(4, 1));
    insereGrafo(g, criaAresta(1, 2));

    imprimirGrafo(g);

    totalAresta = grafoArestas(e, g);
    printf("|E| = %d\n", totalAresta);

    for(int i = 0; i < totalAresta; i++)
        printf("%d -> %d\n", e[i].v1, e[i].v2);

    Aresta x = criaAresta(4, 0);
    if(pertence(g, x))
        printf("\nAresta %d -> %d pertence!\n", x.v1, x.v2);
    else
        printf("\nAresta %d -> %d nao pertence!\n", x.v1, x.v2);

    return 0;
}
