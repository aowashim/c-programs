#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int findMinKey(int key[], int v, bool curMst[])
{
    int min = INT_MAX, i, idx;
    for (i = 0; i < v; i++)
    {
        if (key[i] < min && !curMst[i])
            min = key[i], idx = i;
    }

    return idx;
}

void printMst(int v, int parent[], int **graph)
{
    int i;
    for (i = 1; i < v; i++)
        printf("%d > %d : %d\n", parent[i], i, graph[parent[i]][i]);
}

void findMST(int **graph, int v)
{
    int parent[v], key[v], i, j;
    bool curMst[v];

    for (i = 0; i < v; i++)
    {
        curMst[i] = false;
        key[i] = INT_MAX;
    }

    key[0] = 0;
    parent[0] = -1;

    for (i = 0; i < v - 1; i++)
    {
        int u = findMinKey(key, v, curMst);
        curMst[u] = true;

        for (j = 0; j < v; j++)
        {
            if (graph[u][j] && !curMst[j] && graph[u][j] < key[j])
            {
                parent[j] = u;
                key[j] = graph[u][j];
            }
        }
    }

    printMst(v, parent, graph);
}

int main()
{
    int v, i, j, **graph;
    FILE *ptr = fopen("input.txt", "r");

    if (ptr == NULL)
        printf("Failed to open the file.\n");

    else
    {
        fscanf(ptr, "%d", &v);
        graph = malloc(v * sizeof(int *));
        for (i = 0; i < v; i++)
            graph[i] = malloc(v * sizeof(int));

        for (i = 0; i < v; i++)
        {
            for (j = 0; j < v; j++)
                fscanf(ptr, "%d, ", &graph[i][j]);
        }
        
        fclose(ptr);
    }

    findMST(graph, v);

    return 0;
}