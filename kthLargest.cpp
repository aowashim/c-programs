#include <iostream>
#include <algorithm>

using namespace std;

int findMedian(int arr[], int n)
{
    sort(arr, arr + n);
    return arr[n / 2];
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int l, int r, int x)
{
    int i;
    for (i = l; i < r; i++)
        if (arr[i] == x)
            break;
    swap(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            if (i != j)
                swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int kthLargest(int arr[], int l, int r, int k)
{
    int n = r - l + 1;
    if (n <= 5)
    {
        sort(arr, arr + n);
        return arr[n - k];
    }

    else
    {
        int i, s = (n + 4) / 5;
        int median[s];

        for (i = 0; i < n / 5; i++)
            median[i] = findMedian(arr + l + i * 5, 5);

        if (i * 5 < n)
        {
            median[i] = findMedian(arr + l + i * 5, n % 5);
            i++;
        }

        int mom = kthLargest(median, 0, s - 1, s / 2);
        int pos = partition(arr, l, r, mom);

        if (r - pos == k - 1)
            return arr[pos];
        if (r - pos < k - 1)
        {
            int larr[n - r + pos - 1];
            for (i = 0; i < pos; i++)
                larr[i] = arr[i];
            return kthLargest(larr, l, pos - 1, k - r + pos - 1);
        }
        else
        {
            int j = 0, rarr[r - pos];
            for (i = pos + 1; i < n; i++)
                rarr[j++] = arr[i];
            return kthLargest(rarr, pos + 1, r, k);
        }
    }
}

int main()
{
    //int arr[] = {1, 2, 4, 5, 6, 7, 8, 0, 11, 13, 12, 36, 26, 17, 19, 41};
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]), k;
    cin >> k;
    cout << "Kth largest element is "
         << kthLargest(arr, 0, n - 1, k);
    return 0;
}