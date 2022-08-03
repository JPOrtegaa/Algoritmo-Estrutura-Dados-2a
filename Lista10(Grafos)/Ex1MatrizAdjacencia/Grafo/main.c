#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INFINITO 999999999

typedef struct{
    int v1; // vertice1
    int v2; // vertice2
} Aresta;

struct grafo{
    int **mat; // matriz adjacencia
    int V;     // numero de vertices
};

typedef struct grafo* Grafo;

typedef struct no{
    int v;
    struct no *prox;
} No;

typedef struct{
    No *inicio;
    No *fim;
} Fila;

No* criaNo(int v){
    No *x = (No *) malloc(sizeof(No));
    x->v = v;
    x->prox = NULL;

    return x;
}

Fila* criaFila(){
    Fila *f = (Fila *) malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;

    return f;
}

void enqueue(Fila *q, No *x){
    if(q->inicio == NULL){
        q->inicio = x;
        q->fim = x;
        q->inicio->prox = q->fim;
        q->fim->prox = NULL;
    }
    else{
        x->prox = NULL;
        q->fim->prox = x;
        q->fim = x;
    }
}

void dequeue(Fila *q){
    No *aux;
    if(q->inicio != NULL){
        aux = q->inicio;
        q->inicio = q->inicio->prox;
        free(aux);
    }
}

Aresta criaAresta(int v1, int v2){
    Aresta e;
    e.v1 = v1;
    e.v2 = v2;

    return e;
}

int** criaMatriz(int n, int m){
    int **mat, i, j;
    mat = (int **) malloc(sizeof(int *) * n);

    for(i = 0; i < m; i++)
        mat[i] = (int *) malloc(sizeof(int) * m);

    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            mat[i][j] = 0;

    return mat;
}

Grafo inicializaGrafo(int V){
    Grafo g = (Grafo) malloc(sizeof(struct grafo));
    g->V = V;
    g->mat = criaMatriz(V, V);

    return g;
}

void insereGrafo(Grafo g, Aresta e){
    if(e.v1 < g->V || e.v2 < g->V){
        g->mat[e.v1][e.v2] = 1;
        g->mat[e.v2][e.v1] = 1;
    }
    else
        printf("Aresta invalida!!\n");
}

void removeGrafo(Grafo g, Aresta e){
    if(e.v1 < g->V || e.v2 < g->V){
        g->mat[e.v1][e.v2] = 0;
        g->mat[e.v2][e.v1] = 0;
    }
    else
        printf("Aresta invalida!!\n");
}

int grafoArestas(Aresta e[], Grafo g){
    int i, j, total = 0;

    for(i = 0; i < g->V; i++)
        for(j = 0; j <= i; j++)
            if(g->mat[i][j] == 1){
                e[total].v1 = i;
                e[total++].v2 = j;
            }

    return total;
}

void imprimirGrafo(Grafo g){
    int i, j;
    for(i = 0; i < g->V; i++){
        printf("Vertice %d:\n", i);
        for(j = 0; j < g->V; j++){
            if(g->mat[i][j] == 1)
                printf("%d -> %d\n", i, j);
        }
        printf("\n");
    }
}

int pertence(Grafo g, Aresta e){
    return g->mat[e.v1][e.v2];
}

void dfsVisit(Grafo g, int u, int cor[], int ant[], int d[], int f[], int *timestamp, int print){
    if(print)
        printf("%d ", u);
    cor[u] = CINZA;
    (*timestamp)++;
    d[u] = *timestamp;
    for(int i = 0; i < g->V; i++){
        if(g->mat[u][i]){ // caso vertice seja adjacente!!
            if(cor[i] == BRANCO){
                if(print)
                    printf("-> ");
                ant[i] = u;
                dfsVisit(g, i, cor, ant, d, f, timestamp, print);
            }
        }
    }
    cor[u] = PRETO;
    (*timestamp)++;
    f[u] = *timestamp;
}

void dfs(Grafo g, int s){
    int i, cor[g->V], ant[g->V], d[g->V], f[g->V], timestamp, print;
    print = 1;
    timestamp = 0;
    for(i = 0; i < g->V; i++){
        cor[i] = BRANCO;
        ant[i] = -1;
    }
    for(i = s; i < g->V + s; i++){
        if(cor[i % g->V] == BRANCO){
            dfsVisit(g, i % g->V, cor, ant, d, f, &timestamp, print);
            print = 0;
        }
    }
}

void bfs(Grafo g, int s){
    Fila *q = criaFila();
    No *cabeca;
    int i, cor[g->V], ant[g->V], d[g->V];

    for(i = 0; i < g->V; i++){
        if(i != s){
            cor[i] = BRANCO;
            ant[i] = -1;
            d[i] = INFINITO;
        }
    }
    cor[s] = CINZA; // vertice de origem!!
    ant[s] = -1;
    d[s] = 0;
    enqueue(q, criaNo(s));

    while(q->inicio != NULL){
        cabeca = q->inicio;
        printf("%d", cabeca->v);
        for(i = 0; i < g->V; i++){
            if(g->mat[cabeca->v][i]){ // caso vertice seja adjacente!!
                if(cor[i] == BRANCO){
                    cor[i] = CINZA;
                    d[i] = d[cabeca->v] + 1;
                    ant[i] = cabeca->v;
                    enqueue(q, criaNo(i));
                }
            }
        }
        cor[cabeca->v] = PRETO;
        dequeue(q);
        if(q->inicio != NULL)
            printf(" -> ");
    }

    free(q);
}

int main(){
    Grafo g = inicializaGrafo(6);
    Aresta e[50];
    int totalArestas;

    insereGrafo(g, criaAresta(0, 1));
    insereGrafo(g, criaAresta(0, 4));
    insereGrafo(g, criaAresta(3, 5));
    insereGrafo(g, criaAresta(4, 1));
    insereGrafo(g, criaAresta(1, 2));

    imprimirGrafo(g);

    totalArestas = grafoArestas(e, g);
    printf("arestas = %d\n", totalArestas);

    for(int i = 0; i < totalArestas; i++) // mudar array de arestas, 1 -> 2 e 2 -> 1 mesma aresta??
        printf("%d -> %d\n", e[i].v1, e[i].v2);

    Aresta x = criaAresta(0, 1);
    if(pertence(g, x))
        printf("\nAresta %d -> %d pertence!\n\n", x.v1, x.v2);
    else
        printf("\nAresta %d -> %d nao pertence!\n\n", x.v1, x.v2);

    dfs(g, 0); // busca em profundidade!!
    printf("\n");

    bfs(g, 0); // busca em largura!!
    printf("\n");

    return 0;
}
