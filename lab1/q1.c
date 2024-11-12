#include<stdio.h>

void swap(int *a, int *b){
    int temp;
    temp    = *a;
    *a      = *b;
    *b      = temp;
    
}

int main() 
{
    int a,b;

    printf("ENTER TWO NUMBERS: ");
    scanf("%d%d",&a,&b);
    swap(&a,&b);
    printf("a=%d and b=%d",a,b);
    return 0;
}