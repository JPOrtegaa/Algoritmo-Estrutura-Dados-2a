#include <stdio.h>
#include <stdlib.h>

#define ORDEM 5

typedef struct no{
    int numChaves;
    int chave[ORDEM];
    struct no* filho[ORDEM+1];
} arvoreB;

struct noFila{
    arvoreB *item;
    struct noFila *prox;
};

typedef struct{
    struct noFila *inicio;
    struct noFila *fim;
} Fila;

int isFolha(arvoreB *raiz){
    return (raiz->filho[0] == NULL);
}

int overflow(arvoreB *raiz){
    return (raiz->numChaves == ORDEM);
}

arvoreB* split(arvoreB *x, int *infoMeio){
    arvoreB *y = (arvoreB*) malloc(sizeof(arvoreB));
    int metade = x->numChaves / 2;
    y->numChaves = metade; // x->numChaves - metade - 1 talvez!
    x->numChaves = metade;
    *infoMeio = x->chave[metade];
    y->filho[0] = x->filho[metade + 1]; // pq nao colocar dentro do for??
    for(int i = 0; i < y->numChaves; i++){
        y->chave[i] = x->chave[metade + i + 1];
        y->filho[i+1] = x->filho[metade + i + 2];
    }
    return y;
}

int buscaPos(arvoreB *raiz, int info, int *pos){
    for(*pos = 0; *pos < raiz->numChaves; (*pos)++){
        if(info == raiz->chave[*pos])
            return 1;
        if(info < raiz->chave[*pos])
            break;
    }
    return 0;
}

void insereDireita(arvoreB *raiz, int info, int pos, arvoreB *filho){
    int i;
    for(i = raiz->numChaves; i > pos; i--){
        raiz->chave[i] = raiz->chave[i-1];
        raiz->filho[i+1] = raiz->filho[i];
    }
    raiz->chave[i] = info; // talvez pos!!
    raiz->filho[i+1] = filho; // talvez pos!!
    raiz->numChaves++;
}

void insereAux(arvoreB *raiz, int info){
    int pos;
    if(!buscaPos(raiz, info, &pos)){ // busca se a info ja esta inserida neste no!!
        if(isFolha(raiz))
            insereDireita(raiz, info, pos, NULL);
        else{
            insereAux(raiz->filho[pos], info);
            if(overflow(raiz->filho[pos])){
                int infoMeio;
                arvoreB *aux = split(raiz->filho[pos], &infoMeio);
                insereDireita(raiz, infoMeio, pos, aux);
            }
        }
    }
}

arvoreB* inserir(arvoreB *raiz, int info){
    if(raiz == NULL){
        raiz = (arvoreB*) malloc(sizeof(arvoreB));
        raiz->numChaves = 1;
        raiz->chave[0] = info;
        for(int i = 0; i < ORDEM; i++)
            raiz->filho[i] = NULL;
        return raiz;
    }
    insereAux(raiz, info);
    if(overflow(raiz)){
        arvoreB *novaRaiz, *aux;
        int infoMeio;
        novaRaiz = (arvoreB*) malloc(sizeof(arvoreB));
        aux = split(raiz, &infoMeio);
        novaRaiz->chave[0] = infoMeio;
        novaRaiz->filho[0] = raiz;
        novaRaiz->filho[1] = aux;
        novaRaiz->numChaves = 1;
        for(int i = ORDEM/2; i < ORDEM; i++)
            raiz->filho[i+1] = NULL;
        return novaRaiz;
    }
    return raiz;
}

int underflow(arvoreB *raiz){
    return (raiz->numChaves < (ORDEM-1)/2 ? 1 : 0);
}

int menorElemento(arvoreB *raiz){
    if(raiz != NULL){
        if(isFolha(raiz))
            return raiz->chave[0];
        return menorElemento(raiz->filho[0]);
    }
    return -1;
}

int maiorElemento(arvoreB *raiz){
    if(raiz != NULL){
        if(isFolha(raiz))
            return raiz->chave[raiz->numChaves-1];
        else
            return maiorElemento(raiz->filho[raiz->numChaves]);
    }
    return -1;
}

int contaNosMinimos(arvoreB *raiz){
    int count = 0;
    if(raiz != NULL){
        count += (raiz->numChaves <= ORDEM/2);
        for(int i = 0; i < raiz->numChaves; i++)
            count += contaNosMinimos(raiz->filho[i]);
        count += contaNosMinimos(raiz->filho[raiz->numChaves]);
        return count;
    }
    return 0;
}

void removerAux(arvoreB *raiz, int pos){
    int i;
    for(i = pos; i < raiz->numChaves-1; i++){
        raiz->chave[i] = raiz->chave[i+1];
        raiz->filho[i] = raiz->filho[i+1];
    }
    raiz->filho[i] = raiz->filho[i+1];
    raiz->numChaves--;
}

int emprestimo(arvoreB *raiz, int pos){
    int irmaoEsq, irmaoDir, posChave;
    irmaoEsq = pos-1;
    irmaoDir = pos+1;
    if(irmaoEsq >= 0){
        if(raiz->filho[irmaoEsq]->numChaves > (ORDEM-1)/2){
            insereDireita(raiz->filho[pos], raiz->chave[pos-1], 0, NULL);
            posChave = raiz->filho[irmaoEsq]->numChaves-1;
            raiz->chave[pos-1] = raiz->filho[irmaoEsq]->chave[posChave];
            removerAux(raiz->filho[irmaoEsq], posChave);
            return 1;
        }
    }
    if(irmaoDir <= raiz->numChaves){
        if(raiz->filho[irmaoDir]->numChaves > (ORDEM-1)/2){
            insereDireita(raiz->filho[pos], raiz->chave[pos], raiz->filho[pos]->numChaves, NULL);
            raiz->chave[pos] = raiz->filho[irmaoDir]->chave[0];
            removerAux(raiz->filho[irmaoDir], 0);
            return 1;
        }
    }
    return 0;
}

void merge(arvoreB *raiz, int pos){
    int irmaoEsq, irmaoDir;
    irmaoEsq = pos-1;
    irmaoDir = pos+1;
    if(irmaoEsq >= 0){
        insereDireita(raiz->filho[pos], raiz->chave[pos-1], 0, raiz->filho[pos]->filho[0]);
        for(int i = 0; i < raiz->filho[irmaoEsq]->numChaves; i++)
            insereDireita(raiz->filho[pos], raiz->filho[irmaoEsq]->chave[i], i, raiz->filho[irmaoEsq]->filho[i+1]);
        raiz->filho[pos]->filho[0] = raiz->filho[irmaoEsq]->filho[0]; // em cima acontece shift right!!
        free(raiz->filho[irmaoEsq]);
        removerAux(raiz, pos-1);
    }
    else
        if(irmaoDir <= raiz->numChaves){
            insereDireita(raiz->filho[irmaoDir], raiz->chave[pos], 0, raiz->filho[irmaoDir]->filho[0]);
            for(int i = 0; i < raiz->filho[pos]->numChaves; i++)
                insereDireita(raiz->filho[irmaoDir], raiz->filho[pos]->chave[i], i, raiz->filho[pos]->filho[i+1]);
            raiz->filho[irmaoDir]->filho[0] = raiz->filho[pos]->filho[0];
            free(raiz->filho[pos]);
            removerAux(raiz, pos);
        }
}

arvoreB* remover(arvoreB *raiz, int info){
    int i, menor;
    if(raiz == NULL)
        return NULL;
    for(i = 0; i < raiz->numChaves; i++){
        if(info == raiz->chave[i] || info < raiz->chave[i])
            break;
    }
    if(i < raiz->numChaves && info == raiz->chave[i]){
        if(isFolha(raiz))
            removerAux(raiz, i);
        else{
            menor = menorElemento(raiz->filho[i+1]);
            raiz->chave[i] = menor;
            raiz->filho[i+1] = remover(raiz->filho[i+1], menor);
            if(underflow(raiz->filho[i+1])){
                if(!emprestimo(raiz, i+1)){
                    merge(raiz, i+1);
                }
            }
        }
    }
    else
        raiz->filho[i] = remover(raiz->filho[i], info);
    if(!isFolha(raiz)){
        if(underflow(raiz->filho[i])){
            if(!emprestimo(raiz, i)){
                merge(raiz, i);
            }
        }
    }
    if(raiz->numChaves == 0){
        arvoreB *novaRaiz = raiz->filho[0];
        free(raiz);
        return novaRaiz;
    }

    return raiz;
}

Fila* criarFila(){
    Fila *aux = (Fila*) malloc(sizeof(Fila));
    aux->inicio = aux->fim = NULL;
    return aux;
}

void enqueue(Fila *fila, arvoreB *item){
    struct noFila *aux = (struct noFila*) malloc(sizeof(struct noFila));
    aux->item = item;
    aux->prox = NULL;
    if(fila->inicio == NULL)
        fila->inicio = fila->fim = aux;
    else{
        fila->fim->prox = aux;
        fila->fim = aux;
    }
}

struct noFila* dequeue(Fila *fila){
    struct noFila *aux;
    aux = fila->inicio;
    if(fila->inicio != NULL)
        fila->inicio = fila->inicio->prox;
    return aux;
}

void printPorNivel(arvoreB *raiz){
    Fila *fila = criarFila();
    int i;
    struct noFila *aux;
    enqueue(fila, raiz);
    enqueue(fila, NULL);
    while(fila->inicio != NULL){
        aux = dequeue(fila);
        if(aux->item != NULL){
            printf("[");
            for(i = 0; i < aux->item->numChaves; i++){
                if(i == aux->item->numChaves-1)
                    printf("%d", aux->item->chave[i]);
                else
                    printf("%d ", aux->item->chave[i]);
                if(aux->item->filho[i] != NULL)
                    enqueue(fila, aux->item->filho[i]);
            }
            printf("] ");
            if(aux->item->filho[i] != NULL)
                enqueue(fila, aux->item->filho[i]);
        }
        else{
            printf("\n");
            if(fila->inicio != NULL)
                enqueue(fila, NULL);
        }
        free(aux);
    }
    free(fila);
}

int main(){
    arvoreB *raiz = NULL;

    raiz = inserir(raiz, 22);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 9);
    raiz = inserir(raiz, 44);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 11);
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 33);
    raiz = inserir(raiz, 67);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 17);
    raiz = inserir(raiz, 99);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 56);
    raiz = inserir(raiz, 80);
    raiz = inserir(raiz, 19);
    raiz = inserir(raiz, 55);
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 36);
    raiz = inserir(raiz, 27);
    raiz = inserir(raiz, 13);

    raiz = remover(raiz, 67);
    raiz = remover(raiz, 3);
    raiz = remover(raiz, 5);

    printPorNivel(raiz);
    printf("\n");

    printf("Maior elemento = %d\n", maiorElemento(raiz));
    printf("Menor elemento = %d\n", menorElemento(raiz));
    printf("Nos minimos = %d\n", contaNosMinimos(raiz));

    return 0;
}
