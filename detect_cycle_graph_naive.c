#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
    int src, dest;
} Edge;

typedef struct Graph
{
    int verNum, edgeNum;
    Edge* edgeArr;
} Graph;

Graph* createGraph(int v, int e)
{
    Graph* newGraph = malloc(sizeof(Graph));
    newGraph->verNum = v;
    newGraph->edgeNum = e;
    newGraph->edgeArr = malloc(e * sizeof(Edge));

    return newGraph;
}

int findComponent(int component[], int i)
{
    if(component[i] == -1)
        return i;

    findComponent(component, component[i]);
}

int isCycle(Graph* graph)
{
    int i, x, y;
    int* component = malloc(graph->edgeNum * sizeof(int));

    for(i = 0; i < graph->verNum; i++)
        component[i] = -1;

    for(i = 0; i < graph->edgeNum; i++)
    {
        x = findComponent(component, graph->edgeArr[i].src);
        y = findComponent(component, graph->edgeArr[i].dest);

        if(x == y)
            return 1;

        component[x] = y;
    }
    return 0;
}

int main()
{
    int v, e, i, s, d;
    Graph* graph;

    FILE* ptr = fopen("input.txt", "r");

    if(ptr == NULL)
        printf("Failed to open the input file.");

    else
    {
        fscanf(ptr, "%d %d", &v, &e);
        graph = createGraph(v, e);

        for(i = 0; i < e; i++)
        {
            fscanf(ptr, "%d %d", &s, &d);
            graph->edgeArr[i].src = s;
            graph->edgeArr[i].dest = d;
        }
    }

    if(isCycle(graph))
        printf("Cycle is present.\n");

    else
        printf("No cycle.\n");
    
    return 0;
}