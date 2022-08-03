#include <stdio.h>

void lerVet(int vet[], int n, int i){
	if(i == n)
		;
	else
		scanf("%d", &vet[i]), lerVet(vet, n, ++i);
}

void printVet(int vet[], int n, int i){
	if(i == n-1)
		printf("%d\n", vet[i]);
	else
		printf("%d ", vet[i]), printVet(vet, n, ++i);
}

void trocar(int *x, int *y){
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

void inverteVet(int vet[], int n, int i){
	if(i >= n)
		;
	else
		trocar(&vet[i], &vet[n-1]), inverteVet(vet, --n, ++i);
}

int main(){
	int vet[100], n;
	scanf("%d", &n);
	
	lerVet(vet, n, 0);
	
	printf("\nVetor = ");
	printVet(vet, n, 0);
	
	printf("VetorInvertido = ");
	
	inverteVet(vet, n, 0);
	printVet(vet, n, 0);
	
	return 0;
}
