#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no *esq;
    struct no *dir;
};

typedef struct no* Arvore;

Arvore inserir(Arvore raiz, int info){
    if(raiz == NULL){
        raiz = (struct no*) malloc(sizeof(struct no));
        raiz->info = info;
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    else{
        if(info < raiz->info)
            raiz->esq = inserir(raiz->esq, info);
        if(info >= raiz->info)
            raiz->dir = inserir(raiz->dir, info);
    }
    return raiz;
}

int maiorElemento(Arvore raiz){
    if(raiz->dir != NULL)
        return maiorElemento(raiz->dir);
    return raiz->info;
}

int menorElemento(Arvore raiz){
    if(raiz->esq != NULL)
        return menorElemento(raiz->esq);
    return raiz->info;
}

Arvore remover(Arvore raiz, int info){
    if(raiz == NULL)
        return NULL;
    if(info < raiz->info)
        raiz->esq = remover(raiz->esq, info);
    if(info > raiz->info)
        raiz->dir = remover(raiz->dir, info);
    if(info == raiz->info){
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }
        else
            if(raiz->esq != NULL){
                raiz->info = maiorElemento(raiz->esq);
                raiz->esq = remover(raiz->esq, raiz->info);
            }
        else
            if(raiz->dir != NULL){
                raiz->info = menorElemento(raiz->dir);
                raiz->dir = remover(raiz->dir, raiz->info);
            }
    }
    return raiz;
}

void printInOrdem(Arvore raiz){
    if(raiz->esq != NULL)
        printInOrdem(raiz->esq);
    printf("%d\n", raiz->info);
    if(raiz->dir != NULL)
        printInOrdem(raiz->dir);
}

int alturaArvore(Arvore raiz){
    int esq = 0;
    int dir = 0;
    if(raiz->esq != NULL && raiz->dir != NULL){
        esq = 1 + alturaArvore(raiz->esq);
        dir = 1 + alturaArvore(raiz->dir);
        return (esq > dir ? esq : dir);
    }
    if(raiz->esq != NULL){
        esq = 1 + alturaArvore(raiz->esq);
        return esq;
    }
    if(raiz->dir != NULL){
        dir = 1 + alturaArvore(raiz->dir);
        return dir;
    }
    return 0;
}

int isArvoreAVL(Arvore raiz){
    int fb = 0;
    if(raiz != NULL){
        if(raiz->esq != NULL && raiz->dir != NULL){
            fb = alturaArvore(raiz->esq) - alturaArvore(raiz->dir); // aqui seria redundante utilizar + 1 dos dois lados!!
            if(fb == 1 || fb == 0 || fb == -1)
                return 1 * isArvoreAVL(raiz->esq) * isArvoreAVL(raiz->dir);
            return 0;
        }
        if(raiz->esq == NULL && raiz->dir == NULL){
            fb = 0;
            return 1;
        }
        if(raiz->esq != NULL){
            fb = (alturaArvore(raiz->esq) + 1) - 0; // + 1 pois eh a altura da esquerda da celula, nao a altura da celula da esquerda!!
            if(fb == 1 || fb == 0 || fb == -1)
                return 1 * isArvoreAVL(raiz->esq);
            return 0;
        }
        if(raiz->dir != NULL){
            fb = 0 - (alturaArvore(raiz->dir) + 1); // + 1 pois eh a altura da direita da celula, nao a altura da celula da direita!!
            if(fb == 1 || fb == 0 || fb == -1)
                return 1 * isArvoreAVL(raiz->dir);
            return 0;
        }
    }
    return 0;
}

int main(){
    Arvore raiz = NULL;

    raiz = inserir(raiz, 11);
    raiz = inserir(raiz, 14);
    raiz = inserir(raiz, 22);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 27);
    raiz = inserir(raiz, 25);

    printInOrdem(raiz);
    printf("\n\n");

    raiz = remover(raiz, 15);
    raiz = remover(raiz, 27);
    raiz = remover(raiz, 25);

    printInOrdem(raiz);

    printf("Maior elemento = %d\n", maiorElemento(raiz));
    printf("Menor elemento = %d\n", menorElemento(raiz));
    printf("Altura arvore = %d\n", alturaArvore(raiz));
    if(isArvoreAVL(raiz))
        printf("AVL: SIM\n");
    else
        printf("AVL: NAO\n");

    return 0;
}
