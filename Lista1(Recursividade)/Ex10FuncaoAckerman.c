#include <stdio.h>

int funcaoAckerman(int m, int n){
	if(m == 0)
		return n+1;
	if(m > 0 && n == 0)
		return funcaoAckerman(m-1, 1);
	if(m > 0 && n > 0)
		return funcaoAckerman(m-1, funcaoAckerman(m, n-1));
}

int main(){
	int m, n;
	scanf("%d%d", &m, &n);
	
	printf("%d\n", funcaoAckerman(m, n));

	return 0;
}
