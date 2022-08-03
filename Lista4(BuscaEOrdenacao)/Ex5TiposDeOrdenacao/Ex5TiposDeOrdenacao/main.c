#include <stdio.h>
#include <stdlib.h>

int buscaBinaria(int vet[], int n, int x){
    int e, d, meio;
    e = 0;
    d = n;
    while(e < d-1){
        meio = (e+d)/2;
        if(vet[meio] > x)
            d = meio;
        else
            e = meio;
    }
    return e;
}

void troca(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

void selectionSort(int vet[], int n){ // nao eh estavel, pois nao mantem a chave original e in place!!
    int i, j, menor;
    for(i = 0; i < n-1; i++){
        menor = i; // elemento a ser analisado!!
        for(j = i+1; j < n; j++)
            if(vet[j] < vet[menor])
                menor = j;
        troca(&vet[i], &vet[menor]);
        printVet(vet, n);
    }
}

void insertionSort(int vet[], int n){ // eh estavel, pois mantem a chave original e in place!!
    int i, j, elemento;
    for(i = 1; i < n; i++){
        elemento = vet[i];
        for(j = i-1; j >= 0; j--){
            if(elemento > vet[j])
                break;
            vet[j+1] = vet[j];
        }
        vet[j+1] = elemento;
        printVet(vet, n);
    }
}

void bubbleSort(int vet[], int n){ // eh estavel, pois mantem a chave original e in place!!
    int i, j;
    for(i = n-1; i > 0; i--)
        for(j = 0; j < i; j++){
            if(vet[j] > vet[j+1])
                troca(&vet[j], &vet[j+1]);
            printVet(vet, n);
        }
}

void merge(int vet[], int e, int meio, int d){
    int i, j, k, *vetAux;
    i = e;  j = meio;  k = 0;
    vetAux = (int *) malloc(sizeof(d-e));
    while(i < meio && j < d){
        if(vet[i] < vet[j])
            vetAux[k++] = vet[i++];
        else
            vetAux[k++] = vet[j++];
    }
    while(i < meio)
        vetAux[k++] = vet[i++];
    while(j < d)
        vetAux[k++] = vet[j++];
    for(i = e; i < d; i++)
        vet[i] = vetAux[i-e];
    free(vetAux);
}

void mergeSort(int vet[], int e, int d){ // metodo estavel, pois mantem a chave original e nao eh in place, pois faz o uso de um vetor auxiliar!!
    int meio;
    if(e < d-1){
        meio = (e+d)/2;
        mergeSort(vet, e, meio);
        mergeSort(vet, meio, d);
        merge(vet, e, meio, d);
    }
}

int separa(int vet[], int e, int d){
    int i, j, pivo;
    pivo = vet[d];
    i = e; // i eh a posicao correta do vetor, caso nenhum elemento seja menor que o pivo ele eh o primeiro!!
    for(j = e; j < d; j++)
        if(vet[j] <= pivo)
            troca(&vet[j], &vet[i++]);
    troca(&vet[i], &vet[d]); // vai posicionar o pivo uma posicao acima do ultimo elemento inferior a ele encontrado!!
    return i;
}

void quickSort(int vet[], int e, int d){ // metodo nao eh estavel, pois nao mantem a chave original, e eh in place!!
    int x;
    if(e < d){
        x = separa(vet, e, d);  // retorna a posicao correta do pivo no vetor!!
        quickSort(vet, e, x-1); // faz o separa para a metade anterior ao pivo!!
        quickSort(vet, x+1, d); // faz o separa para a metade depois do pivo!!
    }
}

void printVet(int vet[], int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

int main(){
    int vet[10] = {2, 4, 5, 3, 1};
    int n = 5;

    printVet(vet, n);

 /*   selectionSort(vet, n);
    printVet(vet, n);*/

 /*   insertionSort(vet, n);
    printVet(vet, n);*/

 /*   bubbleSort(vet, n);
    printVet(vet, n);*/

/*    mergeSort(vet, 0, n);
    printVet(vet, n);*/

    quickSort(vet, 0, n-1);
    printVet(vet, n);

    printf("index = %d\n", buscaBinaria(vet, n, 1));



    return 0;
}
