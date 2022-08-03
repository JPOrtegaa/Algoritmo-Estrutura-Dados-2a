#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Fila *f;
    f = inicializar();

    enqueue(f, 1);
    enqueue(f, 2);
    enqueue(f, 3);
    enqueue(f, 4);

    imprimir(f);

    inverte(f);
    imprimir(f);
 /*   dequeue(f);
    imprimir(f);
    dequeue(f);
    imprimir(f);
    dequeue(f);
    imprimir(f);
    dequeue(f);
    imprimir(f);*/



    return 0;
}
