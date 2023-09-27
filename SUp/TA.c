#include <stdlib.h>
#include <stdio.h>



int a;
int *P;
int main() 
{
    P=&a;
    a=5;
    printf("%d\n", P);
    printf("%d\n", &a);
    printf("%d\n", &P);
    printf("%d\n", *P);
}