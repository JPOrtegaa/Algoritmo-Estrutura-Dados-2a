#include <stdio.h>

void printDecrescente(int n){
	if(n == 0)
		printf("%d\n", n);
	else
		printf("%d", n), printDecrescente(n-1);
}

int main(){
	int n;
	scanf("%d", &n);
	
	printDecrescente(n);
	
	return 0;
}
