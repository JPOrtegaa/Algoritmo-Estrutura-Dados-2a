#include <stdio.h>
#include <string.h>

int isPalindromo(char str[], int i, int j){
	if(str[i] == str[j])
		return 1 * isPalindromo(str, i+1, j-1);
	else{
		if(i >= j)
			return 1;
		else
			return 0;
	}
}

// ------------- Algoritmo Preferido ------------------ 
int isPalindromo2(char str[], int i, int j){
	if(str[i]){
		if(str[i] == str[j])
			return 1 * isPalindromo2(str, i+1, j-1);
		else
			return 0;
	}
	else
		return 1;
}

int main(){
	int length;
	char str[100];
	
	scanf("%[^\n]%*c", str);
	length = strlen(str);
	
	if(isPalindromo2(str, 0, length-1))
		printf("%s eh palindromo\n", str);
	else
		printf("%s nao eh palindromo\n", str);
	
	return 0;
}
