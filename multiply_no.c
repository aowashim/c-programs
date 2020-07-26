#include<stdio.h>

int mult(int a, int b)
{
    if(b == 0)
        return 0;
    else if(b > 0)
        return (a + mult(a, b-1));
    else if(b < 0)
     return -mult(a, -b);
}

int main()
{
    int a, b;
    printf("Enter 1st number : ");
    scanf("%d",&a);
    printf("Enter 2nd number : ");
    scanf("%d",&b);

    printf("The result is : %d\n",mult(a, b));
    return 0;
}