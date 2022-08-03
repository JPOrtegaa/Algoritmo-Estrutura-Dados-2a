#include "conjunto.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Lista *l1, *l2, *aux;
    l1 = NULL;
    l2 = NULL;
    aux = NULL;

    l1 = inserir(l1, 1);
    l1 = inserir(l1, 2);
    l1 = inserir(l1, 3);
    l1 = inserir(l1, 3);
    l1 = inserir(l1, 2);

    imprimir(l1);
    printf("\n\n");

    l2 = inserir(l2, 3);
    l2 = inserir(l2, 4);
    l2 = inserir(l2, 5);
    l2 = inserir(l2, 6);
    l2 = inserir(l2, 2);
    l2 = inserir(l2, 1);

    imprimir(l2);
    printf("\n\n");

    aux = uniao(l1, l2);
    imprimir(aux);
    printf("\n\n");

    aux = intersecao(l1, l2);
    imprimir(aux);
    printf("\n\n");

    aux = diferenca(l2, l1);
    imprimir(aux);
    printf("\n\n");

    if(contido(l2, l1))
        printf("l1 esta contido em l2!!\n");
    else
        printf("l1 nao esta contido em l2!!\n");

    return 0;
}
