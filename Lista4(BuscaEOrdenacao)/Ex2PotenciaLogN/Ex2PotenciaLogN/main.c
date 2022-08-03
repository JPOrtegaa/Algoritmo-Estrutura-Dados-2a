#include <stdio.h>

int potenciaLogN(int k, int n){
    if(n > 0){
        if(n % 2 == 0)
            return potenciaLogN(k, n/2) * potenciaLogN(k, n/2);
        else
            return potenciaLogN(k, n/2) * potenciaLogN(k, n/2) * k;
    }
    return 1;
}

int main(){
    int k, n;
    k = 2;
    n = 4;

    printf("%d^%d = %d\n", k, n, potenciaLogN(k, n));

    return 0;
}
