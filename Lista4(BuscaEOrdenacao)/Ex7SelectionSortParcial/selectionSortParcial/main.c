#include <stdio.h>

void printVet(int vet[], int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", vet[i]);
}

void troca(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

void selectionSortParcial(int vet[], int n, int k){
    int i, j, menor;
    for(i = 0; i < k; i++){ // vai ate n-1 pois j comeca em i+1, caso fosse ate n j pegaria um elemento invalido!!
        menor = i;
        for(j = i+1; j < n; j++) // loop para encontrar o menor elemento!
            if(vet[j] < vet[menor])
                menor = j;
        troca(&vet[i], &vet[menor]);
        printVet(vet, n);
        printf("\n");
    }
}

void selectionSortRecursivoAuxParcial(int vet[], int n, int i, int j, int menor){
    if(j < n){
        if(vet[j] < vet[menor])
            return selectionSortRecursivoAuxParcial(vet, n, i, j+1, j);
        else
            return selectionSortRecursivoAuxParcial(vet, n, i, j+1, menor);
    }
    troca(&vet[i], &vet[menor]);
}

void selectionSortRecursivoParcial(int vet[], int n, int i, int k){
    if(i < k){
        selectionSortRecursivoAuxParcial(vet, n, i, i+1, i);
        printVet(vet, n);
        printf("\n");
        return selectionSortRecursivoParcial(vet, n, i+1, k);
    }
}

int main(){
    int vet1[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int vet2[10] = {11, 7, 20, 11, 3, 6, 30, 28, 22, 25};
    int n = 10;

    printVet(vet1, n);
    printf("\n");

    selectionSortParcial(vet1, n, 3);
    printf("\n\n");

    printVet(vet2, n);
    printf("\n");

    selectionSortRecursivoParcial(vet2, n, 0, 3);
    printf("\n\n");

    return 0;
}
