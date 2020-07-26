#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node* createNode(int data)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}









/* Queue implementaion using linked list (start) */
typedef struct Queue
{
    Node *front, *rear;
} Queue;

Queue* createQueue()
{
    Queue* newQueue = malloc(sizeof(Queue));
    newQueue->front = newQueue->rear = NULL;

    return newQueue;
}

void enQueue(Queue* q, int data)
{
    Node* newNode = createNode(data);

    if(q->front == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

bool isEmpty(Queue* q)
{
    if(q->front == NULL)
        return true;

    return false;
}

int deQueue(Queue* q)
{
    int res = q->front->data;
    Node* temp = q->front;
    q->front = q->front->next;

    if(q->front == NULL)
        q->rear = NULL;

    free(temp);

    return res;
}
/* Queue implementaion using linked list (end) */

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

void addEdge(Node** list, int u, int v)
{
    Node* nodeU = createNode(u);
    Node* nodeV = createNode(v);

    nodeU->next = list[v];
    list[v] = nodeU;

    nodeV->next = list[u];
    list[u] = nodeV;
}

/* breadth first search to find the minimum path */
int bfs(Node** list, int u, int v, int n)
{
    int i, *dist, s;
    bool *vis;

    vis = malloc(n * sizeof(bool));
    dist = malloc(n * sizeof(int));

    for(i = 0; i < n; i++)
    {
        vis[i] = false;
        dist[i] = -1;
    }

    Queue* q = createQueue();
    vis[u] = true;
    dist[u] = 0;
    enQueue(q, u);

    while(!isEmpty(q))
    {
        u = deQueue(q);
        Node* temp = list[u];
        while(temp != NULL)
        {
            s = temp->data;
            if(!vis[s])
            {
                vis[s] = true;
                dist[s] = dist[u] + 1;
                enQueue(q, s);
            }
            if(u == v)
                return dist[v];
            temp = temp->next;
        }
    }
    return dist[v];
}

void makeLinear(int m, int prd, int i, int x, int y, int bound, Node** list)
{
    int xBound, yBound;
    int curRow = bound / m;
    int curColm = i % m;

    if(curColm == 0)
        curColm = m;

    if(x == 0)
        xBound = 0;
    else
    {
        xBound = curColm + (m * x);
        if(xBound > prd)
            xBound = prd;
    }

    if(y == 0)
        yBound = 0;
    else
    {
        yBound = curRow * (curColm + y) + (curColm - 1);
        if(yBound > bound)
            yBound = bound;
    }

    int j;
    for(j = i; j <= xBound; j += 6)
        addEdge(list, i, j);

    for(j = i; j <= yBound; j++)
        addEdge(list, i, j);
}

/* main function (taking input from a text file) */
int main()
{
    Node** graph;

    FILE *ptr;
    int x, y, n, m, prd, i, bound, res;
    ptr = fopen("input.txt", "r");

    if(ptr == NULL)
    {
        printf("Failed to open the input file.\n");
    }
    
    else
    {
        fscanf(ptr, "%d %d", &n, &m);
        prd = n * m;
        bound = m;
        graph = createGraph(prd + 1);

        for(i = 1; i <= prd; i++)
        {
            fscanf(ptr, "%d %d", &x, &y);
            if(i > bound)
                bound += m;

            makeLinear(m, prd, i, x, y, bound, graph);
        }
    }

    fclose(ptr);

    res = bfs(graph, 1, prd, prd + 1);
    printf("%d", res);

    return 0;
}
