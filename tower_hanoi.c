#include<stdio.h>

void show_moves(int n, char from_plat, char to_plat, char mid_plat)
{
    if(n == 1)
        {
        printf("The disk %d moved from %c to %c.\n", n, from_plat, to_plat);
        return;
        }
    show_moves(n-1, from_plat, mid_plat, to_plat);
    printf("The disk %d moved from %c to %c.\n", n-1, from_plat, to_plat);
    show_moves(n-1, mid_plat, to_plat, from_plat);
}

int main()
{
    int n;
    scanf("%d", &n);
    show_moves(n,'A','C','B');

    return 0;
}