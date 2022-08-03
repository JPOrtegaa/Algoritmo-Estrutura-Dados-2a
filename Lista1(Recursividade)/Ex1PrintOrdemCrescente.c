#include <stdio.h>

void printCrescente(int n, int i){
	if(i == n)
		printf("%d\n", n);
	else
		printf("%d", i), printCrescente(n, i+1);
}

int main(){
	int n;
	scanf("%d", &n);
		
	printCrescente(n, 0);
	
	return 0;
}
