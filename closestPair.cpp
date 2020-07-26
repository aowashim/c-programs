#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<iostream>
#include<algorithm>

using namespace std;

int dist(int p1, int p2)
{
    return abs(p1-p2);
}

int closestOfThree(int p[], int n, int res[])
{
    int m = INT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(p[i], p[j]) < m)
            {
                m = dist(p[i], p[j]);
                if(abs(res[0] - res[1]) > m)
                {
                    res[0] = p[i]; res[1] = p[j];
                }
            }
    return m;
}

const char* strToInt(char s[])
{
    int i = 1, j=0;
    char *ns = (char*)(malloc(sizeof(char)));
    while(s[i] != ',')
    {
        ns[j++] = s[i++];
    }
    return ns;
}

int findMedian(int arr[], int n)
{
    sort(arr, arr+n);
    return arr[n/2];
}

void swap_(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitions(int arr[], int l, int r, int x)
{
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap_(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap_(&arr[i], &arr[j]);
            i++;
        }
    }
    swap_(&arr[i], &arr[r]);
    return i;
}

int kthLargest(int arr[], int l, int r, int k)
{
    int n = r - l + 1;
    if(n <= 5)
    {
        sort(arr, arr+n);
        return arr[n-k];
    }

    else
    {
        int i, s = (n+4)/5;
        int median[s];
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n)
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

        int mom = kthLargest(median, 0, s-1, s/2);
        int pos = partitions(arr, l, r, mom);

        if (r-pos == k-1)
            return arr[pos];
        if (r-pos < k-1)
        {
            int larr[n-r+pos-1];
            for(i=0; i<pos; i++)
                larr[i] = arr[i];
            return kthLargest(larr, l, pos-1, k-r+pos-1);
        }
        else
        {
            int j = 0, rarr[r-pos];
            for(i=pos+1; i<n; i++)
                rarr[j++] = arr[i];
            return kthLargest(rarr, pos+1, r, k);
        }
    }
}

int findAcross(int la[], int ra[], int l, int r, int res[])
{
    int rm = INT_MAX, lm = INT_MIN, i;
    for(i=0; i<l; i++)
    {
        if(la[i] > lm)
            lm = la[i];
    }
    for(i=0; i<r; i++)
    {
        if(ra[i] < rm)
            rm = ra[i];
    }

    if(abs(rm-lm) < abs(res[0] - res[1]))
    {
        res[0] = lm; res[1] = rm;
    }

    return abs(rm - lm);
}

int closestPair(int arr[], int n, int res[])
{
    if(n <= 3)
        return closestOfThree(arr, n, res);

    int mid = kthLargest(arr, 0, n-1, n/2);

    int cur = n;
    if(n % 2 == 1)
        cur = n+1;
    int la[cur/2 + 1], ra[cur/2 - 1],i ,j=0, k=0;
    for(i=0; i<cur; i++)
    {
        if(arr[i] <= mid)
            la[j++] = arr[i];
        else
            ra[k++] = arr[i];
    }

    int dl = closestPair(la, cur/2 +1, res);
    int dr = closestPair(ra, cur/2 -1, res);
    int dlr = findAcross(la, ra, cur/2 +1, cur/2 -1, res);

    int curMin = min(dl,dr);
    curMin = min(curMin, dlr);

    return curMin;
}

int main()
{
    int n;
    const char* ch;
    char curPoint[150];

    FILE *f = fopen("input.txt", "r");
    ch = fgets(curPoint, 150, f);
    sscanf(ch, "%d", &n);
    int p[n];
    if(f == NULL)
        printf("Failed to open the file.\n");

    else
    {
        int j = 0;
        while(fgets(curPoint, 15, f) != NULL)
        {
            int x;
            ch = strToInt(curPoint);
            sscanf(ch, "%d", &x);
            p[j++] = x;
        }
    }
    fclose(f);

    int res[] = {p[0], p[1]};
    int d = closestPair(p, n, res);
    printf("\nThe minimum distance = %d between (%d, 0) , (%d, 0).\n", d, res[0], res[1]);
    return 0;
}
