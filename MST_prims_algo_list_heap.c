#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node
{
    int data;
    int weight;
    struct Node *next;
} Node;

Node* createNode(int data, int weight)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->weight = weight;
    newNode->next = NULL;

    return newNode;
}

Node** createGraph(int verNum)
{
    Node** list = malloc(verNum * sizeof(Node*));
    int i;
    for(i = 0; i < verNum; i++)
    {
        list[i] = NULL;
    }

    return list;
}

void addEdge(Node** list, int u, int v, int w)
{
    Node* nodeU = createNode(u, w);
    Node* nodeV = createNode(v, w);

    nodeU->next = list[v];
    list[v] = nodeU;

    nodeV->next = list[u];
    list[u] = nodeV;
}

typedef struct HeapNode
{
    int vertex;
    int key;
} HeapNode;

typedef struct MinHeap
{
    int size;
    int *pos;
    HeapNode** array;
} MinHeap;

HeapNode* createHeapNode(int vertex, int key)
{
    HeapNode* newNode = malloc(sizeof(HeapNode));
    newNode->key = key;
    newNode->vertex = vertex;

    return newNode;
}

MinHeap* createHeap(int verNum)
{
    MinHeap* newHeap = malloc(sizeof(MinHeap));
    newHeap->array = malloc(verNum * sizeof(HeapNode*));
    newHeap->pos = malloc(verNum * sizeof(int));
    newHeap->size = 0;

    return newHeap;
}

void swap(HeapNode** a, HeapNode** b)
{
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}

void heapify(MinHeap* curHeap, int idx)
{
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int smallest = idx;

    if(left < curHeap->size && curHeap->array[left]->key < curHeap->array[smallest]->key)
        smallest = left;

    if(right < curHeap->size && curHeap->array[right]->key < curHeap->array[smallest]->key)
        smallest = right;

    if(idx != smallest)
    {
        HeapNode *smallestNode = curHeap->array[smallest];
        HeapNode *idxNode = curHeap->array[idx];

        curHeap->pos[idxNode->vertex] = smallest;
        curHeap->pos[smallestNode->vertex] = idx;

        swap(&curHeap->array[smallest], &curHeap->array[idx]);
        heapify(curHeap, smallest);
    }
}

int isEmpty(MinHeap *curHeap)
{
    return curHeap->size == 0;
}

HeapNode* extractMinNode(MinHeap* curHeap)
{
    HeapNode* minNode = curHeap->array[0];
    HeapNode* lastNode = curHeap->array[curHeap->size - 1];

    curHeap->array[0] = lastNode;

    curHeap->pos[minNode->vertex] = curHeap->size - 1;
    curHeap->pos[lastNode->vertex] = 0;

    curHeap->size--;
    heapify(curHeap, 0);

    return minNode;
}

int isInHeap(MinHeap* curHeap, int vertex)
{
    return curHeap->pos[vertex] < curHeap->size;
}

void decreaseKey(MinHeap* curHeap, int vertex, int key)
{
    int i = curHeap->pos[vertex];
    curHeap->array[i]->key = key;

    while(i && curHeap->array[i]->key < curHeap->array[(i - 1) / 2]->key)
    {
        curHeap->pos[curHeap->array[i]->vertex] = (i - 1) / 2;
        curHeap->pos[curHeap->array[(i - 1) / 2]->vertex] = i;

        swap(&curHeap->array[i], &curHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void printMst(int v, int parent[])
{
    int i;
    printf("The MST is :\n");
    for (i = 1; i < v; i++)
        printf("%d -> %d\n", parent[i], i);
}

void primsMst(Node **graph, int verNum)
{
    int i, u, v, parent[verNum], keyArr[verNum];

    MinHeap *curHeap = createHeap(verNum);

    for(i = 1; i < verNum; ++i)
    {
        parent[i] = -1;
        keyArr[i] = INT_MAX;
        curHeap->array[i] = createHeapNode(i, keyArr[i]);
        curHeap->pos[i] = i;
    }

    keyArr[0] = 0;
    curHeap->array[0] = createHeapNode(0, 0);
    curHeap->pos[0] = 0;
    curHeap->size = verNum;

    while(!isEmpty(curHeap))
    {
        HeapNode* curNode = extractMinNode(curHeap);
        u = curNode->vertex;

        Node* temp = graph[u];
        while(temp != NULL)
        {
            v = temp->data;
            if(isInHeap(curHeap, v) && temp->weight < keyArr[v])
            {
                keyArr[v] = temp->weight;
                parent[v] = u;
                decreaseKey(curHeap, v, keyArr[v]);
            }
            temp = temp->next;
        }
    }

    printMst(verNum, parent);
}

int main()
{
    int v, e, i, x, y, w;
    Node ** graph;

    FILE * ptr = fopen("input.txt", "r");

    if(ptr == NULL)
        printf("Failed to open the file.\n");

    else
    {
        fscanf(ptr, "%d %d", &v, &e);
        graph = createGraph(v);

        for(i = 0; i < e; ++i)
        {
            fscanf(ptr, "%d %d %d", &x, &y, &w);
            addEdge(graph, x, y, w);
        }

        fclose(ptr);
    }

    primsMst(graph, v);

    return 0;
}
