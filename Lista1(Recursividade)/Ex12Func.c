#include <stdio.h>

int func(int n){
	if(n == 0)
		return 1;
	if(n == 1)
		return 1;
	if(n == 2)
		return 2;
	else
		return func(func(n-1)) + func(n-2);
}

int main(){
	
	printf("func(3) = %d\n", func(3));
	printf("func(4) = %d\n", func(4));
	printf("func(5) = %d\n", func(5));
	printf("func(7) = %d\n", func(7));
	
	return 0;
}
