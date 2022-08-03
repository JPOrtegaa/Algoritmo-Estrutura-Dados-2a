#include "listaCabecaCauda.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Lista *l = NULL;
    l = inicializar();

    l = inserirCauda(l, 0);
    l = inserirCauda(l, 1);
    l = inserirCauda(l, 2);
    l = inserirCauda(l, 3);
    l = inserirCauda(l, 4);

    l = remover(l, 4);
    l = remover(l, 0);

    imprimir(l);
    printf("\n\n");

    l = inserirCabeca(l, 1);
    l = inserirCabeca(l, 2);
    l = inserirCabeca(l, 3);
    l = inserirCabeca(l, 4);

    imprimir(l);

    return 0;
}
