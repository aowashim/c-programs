#include<stdio.h>
#include<math.h>

/*void rfunc(int n)
{
    if(n > 1)
    {
        rfunc(floor(n/2));
        for(int i = 0; i < n; i++)
        {
            printf("%d ", i);
        }
    }
    rfunc(floor(n/2));
}*/

int main()
{
    int n;
    scanf("%d", &n);

    //rfunc(n);
    n = n / 2;
    printf("%d", n);
    return 0;
}