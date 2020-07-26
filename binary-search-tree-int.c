#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    struct node *left, *right;
};

struct node* createNode(int val)
{
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->key = val;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

struct node* insertNode(struct node* root, int val)
{
    if(root == NULL)
        return createNode(val);

    else if(root->key > val)
        root->left = insertNode(root->left, val);

    else if(root->key < val)
        root->right = insertNode(root->right, val);

    return root;
}

void inorder(struct node* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d ",root->key);
        inorder(root->right);
    }
}

int main()
{
    struct node* root = NULL;
    root = insertNode(root, 8);
    root = insertNode(root, 10);
    root = insertNode(root,3);
    root = insertNode(root, 5);
    root = insertNode(root, 45);

    inorder(root);
    printf("\n");
}