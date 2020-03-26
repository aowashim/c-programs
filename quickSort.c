#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int makePartition(int arr[], int l, int r)
{
    int rm = rand() % (r - l + 1) + l;
    //printf("%d ", rm);
    swap(&arr[rm], &arr[r]);

    int pi = arr[r];
    int i = l - 1;
    int j;

    for(j = l; j < r; j++)
    {
        if(arr[j] < pi)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    return i+1;
}

void quickSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int pi = makePartition(arr, l, r);

        quickSort(arr, l, pi - 1);
        quickSort(arr, pi + 1, r);
    }
}

int main()
{
    int arr[] = {1,33,4,6,8,22,99,10,4};
    int i,n;
    n = sizeof(arr)/sizeof(arr[0]);
    printf("Before sorting : ");
    for(i = 0; i < n; i++)
        printf("%d ",arr[i]);

    quickSort(arr, 0, n - 1);
    printf("\nAfter sorting : ");
    for(i = 0; i < n; i++)
        printf("%d ",arr[i]);

    printf("\n");
    return 0;
}