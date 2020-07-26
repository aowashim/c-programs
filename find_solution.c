#include <stdio.h>

int main()
{
    float arr[6], x, y, m1, m2, in1, in2;
    int i;

    printf("Enter the values of a1, b1, c1, a2, b2 and c2 respectively in a single line separated by blank space : \n");

    for(i = 0; i < 6; ++i)
        scanf("%f", &arr[i]);

    printf("\nYour two equations are : \n");
    printf("(%.2f)x + (%.2f)y = %.2f\n", arr[0], arr[1], arr[2]);
    printf("(%.2f)x + (%.2f)y = %.2f\n\n", arr[3], arr[4], arr[5]);

    m1 = -(arr[0] / arr[1]);
    m2 = -(arr[3] / arr[4]);
    in1 = arr[2] / arr[1];
    in2 = arr[5] / arr[4];

    if ((m1 == m2) && (in1 != in2))
        printf("There is no solution to this system of equations.\n");

    else if((m1 == m2) && (in1 == in2))
    {
        printf("There are infinite solutions to this system of equations.\n");
        printf("One of them : (x = 1, y = %.2f)\n", (arr[2] - arr[0]) / arr[1]);
    }

    else
    {
        y = (arr[3] * arr[2] - arr[0] * arr[5]) / (arr[3] * arr[1] - arr[0] * arr[4]);
        x = (arr[5] - arr[4] * y) / arr[3];

        printf("The solution is : (x = %.2f, y = %.2f)\n", x, y);
    }

    return 0;
}