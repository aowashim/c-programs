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

void bfs(Node** list, int u, int v, int n)
{
    int i, *dist, s;
    bool *vis;

    vis = malloc(n * sizeof(bool));
    //dist = malloc(n * sizeof(int));

    for(i = 0; i < n; i++)
    {
        vis[i] = false;
        //dist[i] = 0;
    }

    Queue* q = createQueue();
    vis[u] = true;
    enQueue(q, u);

    while(!isEmpty(q))
    {
        u = deQueue(q);
        printf("%d > ", u);
        Node* temp = list[u];
        while(temp != NULL)
        {
            s = temp->data;
            if(!vis[s])
            {
                vis[s] = true;
                //dist[s] = dist[u] + 1;
                enQueue(q, s);
            }
            temp = temp->next;
        }
    }
}

/* dfs using recursion
void dfs(Node** list, int u, int v, bool* vis)
{
    int s = u;
    printf("%d > ", s);
    vis[s] = true;

    Node* temp = list[u];
    while(temp != NULL)
    {
        u = temp->data;

        //if(u == v)
          //  return;

        if(!vis[u])
            dfs(list, u, v, vis);

        temp = temp->next;
    }
} */

int main()
{
    Node** graph;
    int verNum;
    scanf("%d", &verNum);

    graph = createGraph(verNum + 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 5);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 6);
    addEdge(graph, 3, 5);

    bfs(graph, 6, 1, verNum + 1);

    return 0;
}
