#include <stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node* head = NULL;

Node* createNode(int data)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insert(int data)
{
    Node* newNode = createNode(data);
    newNode->next = head;
    head = newNode;
}

void append(int data)
{
    Node* newNode = createNode(data);
    if(head == NULL)
        head = newNode;

    else
    {
        Node* temp = head;
        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }
}

void print()
{
    Node* temp = head;
    while(temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    insert(1);
    insert(2);
    insert(3);
    insert(40);
    insert(1);

    print();

    return 0;
}