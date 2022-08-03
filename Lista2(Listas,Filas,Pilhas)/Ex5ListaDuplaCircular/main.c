#include "listaDuplaCircular.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Lista *l1, *l2;
    l1 = l2 = NULL;

    printf("vazia = %d\n", vazia(l1));

    l1 = inserirCabeca(l1, 1);
    l1 = inserirCabeca(l1, 2);
    l1 = inserirCabeca(l1, 3);
    l1 = inserirCabeca(l1, 4);

    imprimir(l1);

    l1 = removerModularizado(l1, 4); // a funcao remover tambem funciona!!
    l1 = removerModularizado(l1, 2);
    l1 = removerModularizado(l1, 1);
    l1 = removerModularizado(l1, 3);

    imprimir(l1);

    l2 = inserirCauda(l2, 4);
    l2 = inserirCauda(l2, 5);
    l2 = inserirCauda(l2, 6);
    l2 = inserirCauda(l2, 7);

    imprimir(l2);


    return 0;
}
