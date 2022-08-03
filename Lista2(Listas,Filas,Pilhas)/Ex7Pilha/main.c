#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Pilha *p;
    p = inicializar();

    push(p, 1);
    push(p, 2);
    push(p, 3);
    imprimir(p);

    printf("Topo da Pilha = %d\n", topo(p));
    pop(p);
    pop(p);
    imprimir(p);
    pop(p);
    pop(p);

    return 0;
}
