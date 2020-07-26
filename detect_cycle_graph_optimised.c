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

typedef struct Subset
{
    int component, length;
} Subset;

int find(Subset *subset, int i)
{
    if(subset[i].component == i)
        return i;

    find(subset, subset[i].component);
}

void union_(Subset* subset, int x, int y)
{
    int xComp = find(subset, x);
    int yComp = find(subset, y);

    if(subset[xComp].length < subset[yComp].length)
    {
        subset[xComp].component = yComp;
    }

    else if(subset[xComp].length > subset[yComp].length)
    {
        subset[yComp].component = xComp;
    }

    else
    {
        subset[yComp].component = xComp;
        subset[xComp].length++;
    }
}

int isCycle(Graph* graph)
{
    int i, x, y;
    Subset* subset = malloc(graph->verNum * sizeof(Subset));


    for(i = 0; i < graph->verNum; i++)
    {
        subset[i].component = i;
        subset[i].length = 0;
    }

    for(i = 0; i < graph->edgeNum; i++)
    {
        x = find(subset, graph->edgeArr[i].src);
        y = find(subset, graph->edgeArr[i].dest);

        if(x == y)
            return 1;

        union_(subset, x, y);
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