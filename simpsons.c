#include<stdio.h>

int main()
{
    float h, xArr[5], yArr[5], res;
    int i;

    h = 0.25;
    xArr[0] = 0;

    for(i = 1; i < 5; ++i)
        xArr[i] = xArr[0] + i * h;

    for(i = 0; i < 5; ++i)
        yArr[i] = 1 / (1 + xArr[i] * xArr[i]);

    res = h / 3 * (yArr[0] + yArr[4] + 4 * (yArr[1] + yArr[3]) + 2 * yArr[2]);

    printf("The numerical value is = %.4f\n", res);

    return 0;
}