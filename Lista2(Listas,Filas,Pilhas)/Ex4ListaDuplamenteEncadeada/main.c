#include "listaDuplamenteEncadeada.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Lista *l1, *l2, *aux;
    l1 = NULL;
    l2 = NULL;
    aux = NULL;

    l1 = inserirCauda(l1, 1);
    l1 = inserirCauda(l1, 2);
    l1 = inserirCauda(l1, 3);

    l2 = inserirCauda(l2, 4);
    l2 = inserirCauda(l2, 5);
    l2 = inserirCauda(l2, 6);
    l2 = inserirCauda(l2, 7);
    l2 = inserirCauda(l2, 8);

    imprimir(l1);
    imprimir(l2);

    l2 = removerRecursivo(l2, 5, l2);
    imprimir(l2);


    aux = concatenar(l2, l1);
    imprimir(aux);

    aux = intercalar(l1, l2);
    imprimir(aux);

    l1 = inverter(l1);
    imprimir(l1);

    l2 = inverter(l2);
    imprimir(l2);

    return 0;
}
