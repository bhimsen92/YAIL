#include<stdio.h>
#include<stdlib.h>

double fact(double n){
    if(n == 0)
        return 1;
    else
        return n * fact(n - 1);
}

int main(){
    printf("%d\n", fact());
}
