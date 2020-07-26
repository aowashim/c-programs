#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

typedef struct Queue
{
    struct Node *front, *rear;
} Queue;

Queue* createQueue()
{
    Queue* newQueue = malloc(sizeof(Queue));
    newQueue->front = newQueue->rear = NULL;

    return newQueue;
}

Node* createNode(int data)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
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
        q->rear == NULL;

    free(temp);

    return res;
}

void print(Queue* q)
{
    Node* temp = q->front;
    while(temp != NULL)
    {
        printf("%d > ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    Queue* q = createQueue();
    int q1, q2;
    bool emp;

    enQueue(q, 1);
    enQueue(q, 2);
    enQueue(q, 3);
    enQueue(q, 4);
    enQueue(q, 5);
    enQueue(q, 6);

    print(q);

     q1 = deQueue(q);
     q2 = deQueue(q);
     deQueue(q);
     deQueue(q);
     deQueue(q);
     deQueue(q);
     enQueue(q, 9);
    // printf("%d, %d\n", q1, q2);

    emp = isEmpty(q);
    if(!emp)
        print(q);

    else
        printf("Empty\n");

    return 0;
}