#include<stdio.h>
#include<iostream>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};
struct Node* newNode(int value){
    struct Node* node= (struct Node*)malloc(sizeof(Node));   
    node->data= value;
    node->left = NULL;
    node->right =NULL;
    node->height=1;
    return node;
}

int max(int a, int b){
    if(a>b) return a;
    else if (a=b) return a;
    else return b;
}

int height(struct Node* node){
    if(node==NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(struct Node* node){
    if(node==NULL)
        return 0;
    return height(node->left)-height(node->right);
}

struct Node* rightRotate(struct Node* node){
    struct Node* x= node->left;
    struct Node* y= x->right;

    x->right=node;
    node->left=y;

    x->height = 1+max(height(x->left),height(x->right));
    node->height = 1+max(height(node->left),height(node->right));

    return x;
}

struct Node* leftRotate(struct Node* node){
    
    struct Node* x= node->right;
    struct Node* y= x->left;

    x->left=node;
    node->right=y;

    x->height = 1+max(height(x->left),height(x->right));
    node->height = 1+max(height(node->left),height(node->right));

    return x;
}

struct Node* AInsert(struct Node* node,int value){
   //Insertion Part
    if(node==NULL)
        return newNode(value);
    if(node->data > value)
        node->left= AInsert(node->left,value);
    
    if(node->data < value)
        node->right= AInsert(node->right,value);

    //Updating Height
    node->height= 1+max(height(node->left),height(node->right));
    
    //Getting Balance Factor
    int balance = getBalanceFactor(node);

//Applying rotations according to the balance factors

    //Left Left Case
    if(balance>1 && value<node->left->data)
        return rightRotate(node);
    
    //Right Right Case
    if(balance<-1 && value>node->right->data)
        return leftRotate(node);
    //Left Right Case
    if(balance>1 && value>node->left->data){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    //Right Left Case
    if(balance<-1 && value<node->right->data){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

void inOrder(struct Node* root){
    if(root==NULL)
        return;
    inOrder(root->left);
    std::cout<<root->data<<" "<<std::endl;
    inOrder(root->right);
}

void preOrder(struct Node* root){
    if(root==NULL)
        return;
    std::cout<<root->data<<" "<<std::endl;
    preOrder(root->left);
    preOrder(root->right);    
}

int main(){
    struct Node* root=NULL;
   do{
        int choice,count=0;
        printf("\n\nChoose from the following operations to be performed on a AVL Tree\n");
        printf("1.Insert\n");
        printf("2.Inorder Traversal\n");
        printf("3.Preorder Traversal\n");
        printf("4.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                int value;
                printf("\nEnter the value you want to insert: ");
                scanf("%d",&value);
                count==0? root=AInsert(root,value):AInsert(root,value);
                count++;
                break;
            case 2:
                printf("\nThe Inorder Traversel of the BST is:\n");
                inOrder(root);
                break;
                break;
            case 3:
                printf("\nThe Preorder Traversel of the BST is:\n");
                preOrder(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Enter a valid input ^_^\n");
                break;
        }

    }while(1);
    
    return 0;
}