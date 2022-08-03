#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"

int main(){
    Lista *l1, *l2, *l3, *aux;
    l1 = NULL;
    l2 = NULL;
    l3 = NULL;
    aux = NULL;


    l1 = inserirCauda(l1, 1);
    l1 = inserirCauda(l1, 2);
    l1 = inserirCauda(l1, 3);
    l2 = inserirCauda(l2, 4);
    l2 = inserirCauda(l2, 5);
    l2 = inserirCauda(l2, 6);

    aux = pares(l2);
    imprimir(aux);
    printf("\n\n");

    printf("%d\n", contaOcorrencias(l1, 0));
    printf("\n");

    aux = concatenarAoFinal(l1, l2);
    imprimir(aux);
    printf("\n\n");

    l1 = removerRecursivo(l1, 4, l1, NULL);

    imprimirRecursivo(l1);
    printf("\n\n");

    imprimirRecursivo(l2);
    printf("\n\n");

    aux = concatenarRecursivo(l1, l2, NULL);

    imprimirRecursivo(aux);
    printf("\n\n");


    aux = intercalarRecursivo(l1, l2, NULL, 0);

    imprimirRecursivo(aux);
    printf("\n\n");

    l1 = inverterRecursivo(l1, NULL, l1, NULL);

    imprimirRecursivo(l1);
    printf("\n\n");

    l3 = inserirOrdenado(l3, 5);
    l3 = inserirOrdenado(l3, 6);
    l3 = inserirOrdenado(l3, 4);
    l3 = inserirOrdenado(l3, 3);
    l3 = inserirOrdenado(l3, 2);
    l3 = inserirOrdenado(l3, 1);
    l3 = inserirOrdenado(l3, 22);
    l3 = inserirOrdenado(l3, 2);

    imprimir(l3);
    printf("\n\n");

/*    l1 = inserirCabeca(l1, 1);
    l1 = inserirCabeca(l1, 3);
    l1 = inserirCabeca(l1, 5);
    l1 = inserirCabeca(l1, 7);
    l1 = inserirCabeca(l1, 9);
    l1 = inserirCabeca(l1, 11);
    l1 = inserirCabeca(l1, 13);
    l2 = inserirCabeca(l2, 2);
    l2 = inserirCabeca(l2, 4);
    l2 = inserirCabeca(l2, 6);
    l2 = inserirCabeca(l2, 8);
    l2 = inserirCabeca(l2, 10);
    l2 = inserirCabeca(l2, 12);
    l2 = inserirCabeca(l2, 14);

    imprimir(l1);
    printf("\n\n");


    imprimir(l2);
    printf("\n\n");

    aux = intercalar(l2, l1);
    imprimir(aux);
    printf("\n\n");

    aux = concatenar(l1, l2);
    imprimir(aux);
    printf("\n\n");

    l1 = inverter(l1);
    imprimir(l1);
    printf("\n\n");*/

    return 0;
}
