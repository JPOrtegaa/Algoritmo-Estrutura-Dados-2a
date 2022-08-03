#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct no{
    char *info;
    struct no *esq;
    struct no *dir;
} Arvore;

int main(){
    Arvore *raiz = NULL; // 6+7*11
    char *expressao = "6+7*11";

    raiz = constroiArvore(raiz, expressao);





    return 0;
}
