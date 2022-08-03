#include <stdio.h>

int fatorial(int n){
	if(n == 0)
		return 1;
	else
		return n * fatorial(n-1);
}

int superFatorial(int n){
	if(n == 0)
		return fatorial(0);
	else
		return fatorial(n) * superFatorial(n-1);
}

int main(){
	int n;
	scanf("%d", &n);
	
	printf("fatorial de N = %d\n", fatorial(n));
	printf("superFatorial de N = %d\n", superFatorial(n));

	return 0;
}
