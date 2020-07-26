#include<stdio.h>

// function to swap two array elements
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// bubble sort function
void bubbleSort(int arr[], int size)
{
    int i, j, flag;
    for(i = 0; i < size - 1; ++i)
    {
        flag = 1;
        for(j = 0; j < size - 1 - i; ++j)
        {
            // swap the values if arr[j] > arr[j + 1]
            if(arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]), flag = 0;
        }

        if(flag == 1)
            break;
    }
}

int main()
{
    int i, n;
    int arr[] = {1, 33, 0, -1, 2, 3, 2, 9, 7};
    n = sizeof(arr) / sizeof(arr[0]);

    printf("Array before sort : ");
    for(i = 0; i < n; ++i)
        printf("%d ", arr[i]);

    bubbleSort(arr, n);

    printf("\nArray after sort : ");
    for(i = 0; i < n; ++i)
        printf("%d ", arr[i]);

    return 0;
}