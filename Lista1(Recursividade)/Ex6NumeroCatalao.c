#include <stdio.h>

unsigned int numeroCatalao(int n){
	if(n == 0)
		return 1;
	else
		return (2*(2*n-1) / (n + 1)) * numeroCatalao(n-1);
}

int main(){
	int n;
	scanf("%d", &n);
	
	printf("numeroCatalao(%d) = %d\n", n, numeroCatalao(n));
	
	return 0;
}
