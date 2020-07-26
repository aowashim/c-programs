#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
    int src, dest, weight;
} Edge;

typedef struct Graph
{
    int verNum, edgeNum;
    Edge *edgeArr;
} Graph;

Graph *createGraph(int v, int e)
{
    Graph *newGraph = malloc(sizeof(Graph));
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
    if (subset[i].component == i)
        return i;

    find(subset, subset[i].component);
}

void union_(Subset *subset, int x, int y)
{
    int xComp = find(subset, x);
    int yComp = find(subset, y);

    if (subset[xComp].length < subset[yComp].length)
    {
        subset[xComp].component = yComp;
    }

    else if (subset[xComp].length > subset[yComp].length)
    {
        subset[yComp].component = xComp;
    }

    else
    {
        subset[yComp].component = xComp;
        subset[xComp].length++;
    }
}

int comparator(const void *p, const void *q)
{
    Edge *e1 = (Edge *)p;
    Edge *e2 = (Edge *)q;

    return (e1->weight - e2->weight);
}

void kruskalMst(Graph *graph)
{
    int i, x, y, e = 0;
    Edge *res = malloc((graph->verNum - 1) * sizeof(Edge));
    Subset *subset = malloc(graph->verNum * sizeof(Subset));

    qsort(graph->edgeArr, graph->edgeNum, sizeof(graph->edgeArr[0]), comparator);

    for (i = 0; i < graph->verNum; i++)
    {
        subset[i].component = i;
        subset[i].length = 0;
    }

    i = 0;

    while (e < graph->verNum - 1 && i < graph->edgeNum)
    {
        Edge temp = graph->edgeArr[i++];

        x = find(subset, temp.src);
        y = find(subset, temp.dest);

        if (x != y)
        {
            res[e++] = temp;
            union_(subset, x, y);
        }
    }

    printf("The MST is :\n");
    for (i = 0; i < graph->verNum - 1; i++)
    {
        printf("%d -> %d : %d\n", res[i].src, res[i].dest, res[i].weight);
    }
}

int main()
{
    int v, e, i, s, d, w;
    Graph *graph;

    FILE *ptr = fopen("input.txt", "r");

    if (ptr == NULL)
        printf("Failed to open the input file.");

    else
    {
        fscanf(ptr, "%d %d", &v, &e);
        graph = createGraph(v, e);

        for (i = 0; i < e; i++)
        {
            fscanf(ptr, "%d %d %d", &s, &d, &w);
            graph->edgeArr[i].src = s;
            graph->edgeArr[i].dest = d;
            graph->edgeArr[i].weight = w;
        }

        fclose(ptr);
    }

    kruskalMst(graph);

    return 0;
}