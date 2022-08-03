#include <stdio.h>

int somaDigitos(int n){
	if(n == 0)
		return 0;
	else
		return n%10 + somaDigitos(n/10);
}

int main(){
	int n;
	scanf("%d", &n);
	
	printf("SomaDigitos(%d) = %d\n", n, somaDigitos(n));	
	
	
	return 0;
}
