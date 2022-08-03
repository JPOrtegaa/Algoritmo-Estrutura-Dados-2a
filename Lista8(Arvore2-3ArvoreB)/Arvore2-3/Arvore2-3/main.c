#include <stdio.h>
#include <stdlib.h>

struct no{
    int chaveEsq;
    int chaveDir;
    int n;
    struct no *esq;
    struct no *meio;
    struct no *dir;
};

typedef struct no* arvore23;

int isFolha(arvore23 raiz){
    return (raiz->esq == NULL);
}

arvore23 criaNo(int chaveEsq, int chaveDir, arvore23 esq, arvore23 meio, arvore23 dir, int n){
    arvore23 aux = (struct no*) malloc(sizeof(struct no));

    aux->chaveEsq = chaveEsq;
    aux->chaveDir = chaveDir;
    aux->esq = esq;
    aux->meio = meio;
    aux->dir = dir;
    aux->n = n;

    return aux;
}

void insereChave(arvore23 raiz, int info, arvore23 filho){
    if(info < raiz->chaveEsq){
        raiz->chaveDir = raiz->chaveEsq;
        raiz->dir = raiz->meio;
        raiz->chaveEsq = info;
        raiz->meio = filho;
    }
    else{
        raiz->chaveDir = info;
        raiz->dir = filho;
    }
    raiz->n = 2;
}

arvore23 split(arvore23 raiz, int info, arvore23 filho, int *chavePromovida){
    arvore23 aux;
    if(info < raiz->chaveEsq){ // info mais a esquerda!!
        *chavePromovida = raiz->chaveEsq;
        aux = criaNo(raiz->chaveDir, 0, raiz->meio, raiz->dir, NULL, 1);
        raiz->chaveEsq = info;
        raiz->meio = filho;
        raiz->dir = NULL;
        raiz->n = 1;
        return aux;
    }
    else
        if(info > raiz->chaveDir){ // info mais a direita!!
            *chavePromovida = raiz->chaveDir;
            aux = criaNo(info, 0, raiz->dir, filho, NULL, 1);
            raiz->dir = NULL;
            raiz->n = 1;
            return aux;
        }
        else{ // info no meio!!
            *chavePromovida = info;
            aux = criaNo(raiz->chaveDir, 0, filho, raiz->dir, NULL, 1);
            raiz->dir = NULL;
            raiz->n = 1;
            return aux;
        }
}

arvore23 inserirAux(arvore23 raiz, int info, int *chavePromovida){
    if(isFolha(raiz)){
        if(raiz->n == 1){
            insereChave(raiz, info, NULL);
            return NULL;
        }
        else
            return split(raiz, info, NULL, chavePromovida);
    }
    else{
        arvore23 noAux;
        int chaveAux;
        if(info < raiz->chaveEsq)
            noAux = inserirAux(raiz->esq, info, &chaveAux);
        else
            if(raiz->n == 1 || info < raiz->chaveDir)
                noAux = inserirAux(raiz->meio, info, &chaveAux);
            else
                noAux = inserirAux(raiz->dir, info, &chaveAux);
        if(noAux == NULL)
            return NULL;
        if(raiz->n == 1){
            insereChave(raiz, chaveAux, noAux);
            return NULL;
        }
        else
            return split(raiz, chaveAux, noAux, chavePromovida);
    }
}

arvore23 inserir(arvore23 raiz, int info){
    if(raiz == NULL)
        return criaNo(info, 0, NULL, NULL, NULL, 1);
    else{
        int chavePromovida;
        arvore23 aux = inserirAux(raiz, info, &chavePromovida); // filho!!
        if(aux != NULL)
            return criaNo(chavePromovida, 0, raiz, aux, NULL, 1);
        return raiz;
    }
}

int minimo(arvore23 raiz){
    if(raiz != NULL){
        if(isFolha(raiz))
            return raiz->chaveEsq;
        return minimo(raiz->esq);
    }
    return -1;
}

int maximo(arvore23 raiz){
    if(raiz != NULL){
        if(isFolha(raiz)){
            if(raiz->n == 1)
                return raiz->chaveEsq;
            return raiz->chaveDir;
        }
        if(raiz->n == 1)
            return maximo(raiz->meio);
        return maximo(raiz->dir);
    }
    return -1;
}

int contaNos(arvore23 raiz){
    if(raiz != NULL)
        return 1 + contaNos(raiz->esq) + contaNos(raiz->meio) + contaNos(raiz->dir);
    return 0;
}

void printInOrdem(arvore23 raiz){
    if(raiz != NULL){
        printInOrdem(raiz->esq);
        printf("%d ", raiz->chaveEsq);
        printInOrdem(raiz->meio);
        if(raiz->n == 2)
            printf("%d ", raiz->chaveDir);
        printInOrdem(raiz->dir);
    }
}

int altura(arvore23 raiz){
    if(raiz != NULL)
        return 1 + altura(raiz->esq);
    return -1;
}

void printNivel(arvore23 raiz, int i, int nivel){
    if(raiz != NULL){
        if(i == nivel){
            printf("[");
            if(raiz->n == 2){
                printf("%d ", raiz->chaveEsq);
                printf("%d", raiz->chaveDir);
            }
            else
                printf("%d", raiz->chaveEsq);
            printf("] ");
        }
        printNivel(raiz->esq, i+1, nivel);
        printNivel(raiz->meio, i+1, nivel);
        printNivel(raiz->dir, i+1, nivel);
    }
}

void printPorNivel(arvore23 raiz){
    int i, alturaArvore;
    alturaArvore = altura(raiz);
    for(i = 0; i <= alturaArvore; i++){
        printNivel(raiz, 0, i);
        printf("\n");
    }
}

void teste(arvore23 raiz){

}

int main(){
    arvore23 raiz = NULL;

    void *blah = NULL;

    teste(blah);

    blah = inserir(blah, 60);
    blah = inserir(blah, 20);
    blah = inserir(blah, 10);
    blah = inserir(blah, 30);
    blah = inserir(blah, 25);
    blah = inserir(blah, 50);
    blah = inserir(blah, 80);

    printf("Minimo = %d\n", minimo(blah));
    printf("Maximo = %d\n", maximo(blah));
    printf("Total nos = %d\n", contaNos(blah));
    printf("Altura = %d\n", altura(blah));

    printInOrdem(blah);
    printf("\n");

    printPorNivel(blah);

    return 0;
}
