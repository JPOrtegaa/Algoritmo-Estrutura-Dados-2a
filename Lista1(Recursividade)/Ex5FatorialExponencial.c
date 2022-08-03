#include <stdio.h>
#include <math.h>

float fatorialExponencial(float n){
	if(n == 0)
		return 1;
	else
		return pow(n, fatorialExponencial(n-1));
}

int main(){
	float n;
	scanf("%f", &n);
	
	printf("fatexp(%.0f) = %.0f\n", n, fatorialExponencial(n));
	
	return 0;
}
