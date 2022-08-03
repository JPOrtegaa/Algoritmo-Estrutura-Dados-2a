#include <stdio.h>

int buscaBinaria(int vet[], int n, int x){
    int e, meio, d;
    e = 0;
    d = n;
    while(e < d-1){
        meio = (e+d)/2;
        if(vet[meio] > x)
            d = meio;
        else
            e = meio;
    }
    if(vet[e] == x)
        if(e == vet[e])
            return e;
    return -1;
}

void insertionSort(int vet[], int n){
    int i, j, x;
    for(i = 1; i < n; i++){
        x = vet[i]; // elemento a ser analisado!!
        for(j = i-1; j >= 0; j--){
            if(x > vet[j]) // caso seja maior, seu local foi encontrado, um acima do elemento em que ele eh maior!!
                break;
            vet[j+1] = vet[j]; // copia os maiores elementos caso x nao seja maior!!
        }
        vet[j+1] = x; // caso seja o menor numero seja colocado na primeira posicao!!
    }
}

void printVet(int vet[], int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

int main(){
    int vet[10] = {0, 1, 2, 4, 5, 6};
    int n = 6;

    printVet(vet, n);

    insertionSort(vet, n);
    printVet(vet, n);

    printf("index = %d\n", buscaBinaria(vet, n, 2));


    return 0;
}
