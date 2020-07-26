#include<stdio.h>
#include<stdlib.h>

struct node
{
    char val;
    int count;
    struct node *left, *right;
};

struct node* createNode(char val)
{
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->count = 1;

    return newNode;
}

struct node* insert(struct node* root, char val)
{
    if(root == NULL)
        return createNode(val);
    else if(root->val == val)
    {
        root->count++;
    }
    else if(root->val > val)
    {
        root->left = insert(root->left, val);
    }
    else
    {
        root->right = insert(root->right, val);
    }

    return root;
}


void inorder(struct node* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%c(%d) > ",root->val,root->count);
        inorder(root->right);
    }
}

void preorder(struct node* root)
{
    if(root != NULL)
    {
        printf("%c(%d) > ",root->val,root->count);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node* root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c(%d) > ",root->val,root->count);
    }
}

int main()
{
    struct node* root = NULL;
    int ch,i=0;
    char s[1000];
    printf("Enter your string : ");
    fgets(s, 1000, stdin);

    while(s[i+1] != '\0')
    {
        root = insert(root, s[i]);
        i++;
    }

    printf("Enter your option :\nIt will show the required traversal with number of occurence of a character within ().\n");
    printf("1 : Inorder\n2 : Preorder\n3 : Postorder\n");
    scanf("%d",&ch);

    switch(ch)
    {
        case 1: printf("The inorder traversal is : ");
        inorder(root);
        printf("\n");
        break;

        case 2: printf("The preorder traversal is : ");
        preorder(root);
        printf("\n");
        break;

        case 3: printf("The postorder traversal is : ");
        postorder(root);
        printf("\n");
        break;

        default : printf("Please enter a valid option.\n");
        break;
    }
    return 0;
}