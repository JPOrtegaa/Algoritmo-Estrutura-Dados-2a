#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no *esq;
    struct no *dir;
};

typedef struct no* Arvore; // ISSO JA EH UM PONTEIRO!!!!!!!!

int vazia(Arvore raiz){
    return (raiz == NULL);
}

Arvore inserir(Arvore raiz, int info){
    if(raiz == NULL){
        raiz = (struct no *) malloc(sizeof(struct no));
        raiz->info = info;
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    if(info < raiz->info)
        raiz->esq = inserir(raiz->esq, info);
    if(info > raiz->info)
        raiz->dir = inserir(raiz->dir, info);
    return raiz;
}

Arvore inserirIterativo(Arvore raiz, int info){
    struct no *aux, *p;
    aux = (struct no *) malloc(sizeof(struct no));
    aux->info = info;
    aux->esq = NULL;
    aux->dir = NULL;
    if(raiz == NULL)
        return aux;
    p = raiz;
    while(1){
        if(info < p->info){
            if(p->esq == NULL){
                p->esq = aux;
                break;
            }
            else
                p = p->esq;
        }
        if(info > p->info){
            if(p->dir == NULL){
                p->dir = aux;
                break;
            }
            else
                p = p->dir;
        }
    }
    return raiz;
}

Arvore remover(Arvore raiz, int info){
    if(raiz == NULL)
        return NULL;
    if(info < raiz->info) // Caso info seja menor, procure do lado esquerdo!!
        raiz->esq = remover(raiz->esq, info);
    if(info > raiz->info) // Caso info seja maior, procure do lado direito!!
        raiz->dir = remover(raiz->dir, info);
    if(info == raiz->info){ // Info encontrado!!
        if(raiz->esq == NULL && raiz->dir == NULL){ // Caso seja folha, basta dar free e retornar NULL!!
            free(raiz);
            return NULL;
        }
        else{ // Caso nao seja folha!!
            if(raiz->esq != NULL){ // Procurar na esquerda o maior elemento e coloca-lo, depois exlui-lo!!
                raiz->info = maiorElemento(raiz->esq);
                raiz->esq = remover(raiz->esq, raiz->info);
            }
            else
                if(raiz->dir != NULL || (raiz->esq != NULL && raiz->dir != NULL)){ // Procurar na direita o menor elemento e coloca-lo, depois exclui-lo!!
                    raiz->info = menorElemento(raiz->dir);
                    raiz->dir = remover(raiz->dir, raiz->info);
                }
        }
    }
    return raiz;
}

void printArvoreInfix(Arvore raiz){ // mesma coisa que InOrdem!!
    if(raiz->esq)
        printArvoreInfix(raiz->esq);
    printf("%d\n", raiz->info);
    if(raiz->dir)
        printArvoreInfix(raiz->dir);
}

void printArvorePrefix(Arvore raiz){ // mesma coisa que PreOrdem!!
    printf("%d\n", raiz->info);
    if(raiz->esq)
        printArvorePrefix(raiz->esq);
    if(raiz->dir)
        printArvorePrefix(raiz->dir);
}

void printArvorePosfix(Arvore raiz){ // mesma coisa que PosOrdem!!
    if(raiz->esq)
        printArvorePosfix(raiz->esq);
    if(raiz->dir)
        printArvorePosfix(raiz->dir);
    printf("%d\n", raiz->info);
}

void printArvoreInOrdem(Arvore raiz){
    if(raiz){
        printArvoreInOrdem(raiz->esq);
        printf("%d\n", raiz->info);
        printArvoreInOrdem(raiz->dir);
    }
}

int maiorElemento(Arvore raiz){
    if(raiz->dir == NULL)
        return raiz->info;
    else
        return maiorElemento(raiz->dir);
}

int maiorElementoIterativo(Arvore raiz){
    while(raiz->dir != NULL)
        raiz = raiz->dir;
    return raiz->info;
}

int menorElemento(Arvore raiz){
    if(raiz->esq == NULL)
        return raiz->info;
    else
        return menorElemento(raiz->esq);
}

int menorElementoIterativo(Arvore raiz){
    while(raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz->info;
}

int alturaArvore(Arvore raiz){
    int esq, dir;
    esq = 0;
    dir = 0;
    if(raiz->esq != NULL)
        esq = 1 + alturaArvore(raiz->esq);
    if(raiz->dir != NULL)
        dir = 1 + alturaArvore(raiz->dir);
    if(esq > dir)
        return esq;
    else
        return dir;
}

int somaArvore(Arvore raiz){
    if(raiz->esq != NULL && raiz->dir != NULL) // Esta celula tem o caminho da esquerda e da direita!!
        return raiz->info + somaArvore(raiz->esq) + somaArvore(raiz->dir);
    if(raiz->esq != NULL) // Somente o caminho da esquerda!!
        return raiz->info + somaArvore(raiz->esq);
    if(raiz->dir != NULL) // Somente o caminho da direita!!
        return raiz->info + somaArvore(raiz->dir);
    return raiz->info; // Eh celula folha!!
}

void deleteArvore(Arvore raiz){
    if(raiz->esq)
        deleteArvore(raiz->esq);
    if(raiz->dir)
        deleteArvore(raiz->dir);
    free(raiz);
}

void imprimePorNivel(Arvore raiz){ // arrumar ainda!!
    if(raiz != NULL)
        printf("%d\n", raiz->info);







}

int isEstritamenteBinaria(Arvore raiz){ // Celulas podem haver 0 ou 2 filhos!!
    if(raiz->esq != NULL && raiz->dir != NULL) // Caso tenha 2 filhos, procure nos dois!!
        return 1 * isEstritamenteBinaria(raiz->esq) * isEstritamenteBinaria(raiz->dir);
    else
        if(raiz->esq != NULL || raiz->dir != NULL) // Caso somente um dos dois tenha filho nao eh estritamente binaria!!
            return 0;
        else
            if(raiz->esq == NULL && raiz->dir == NULL) // Caso tenha 0 filhos!!
                return 1;
}

int main(){
    Arvore raiz = NULL;

    raiz = inserirIterativo(raiz, 11);
    raiz = inserirIterativo(raiz, 14);
    raiz = inserirIterativo(raiz, 22);
    raiz = inserirIterativo(raiz, 5);
    raiz = inserirIterativo(raiz, 15);
    raiz = inserirIterativo(raiz, 8);
    raiz = inserirIterativo(raiz, 2);
    raiz = inserirIterativo(raiz, 27);
    raiz = inserirIterativo(raiz, 25);

    printArvoreInfix(raiz);
    printf("\n\n");

  /*  raiz = remover(raiz, 11);
    raiz = remover(raiz, 22);*/

    printArvoreInfix(raiz);
    printf("\n\n");

    printf("Maior elemento = %d\n", maiorElementoIterativo(raiz));
    printf("Menor elemento = %d\n", menorElementoIterativo(raiz));
    printf("Altura arvore = %d\n", alturaArvore(raiz));
    printf("Soma arvore = %d\n", somaArvore(raiz));
    if(isEstritamenteBinaria(raiz))
        printf("Arvore estritamente binaria: SIM\n");
    else
        printf("Arvore estritamente binaria: NAO\n");
    printf("\n\n");
    imprimePorNivel(raiz);

    deleteArvore(raiz);

    return 0;
}
