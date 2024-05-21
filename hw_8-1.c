#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode{
char data;
struct TreeNode *left, *right;
}TreeNode;

#define MAX_QUEUE_SIZE 100
#define SIZE 100
typedef TreeNode *element;
typedef struct{
element data[MAX_QUEUE_SIZE];
int front,rear;
}QueueType;

void error(char *message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}

void init_queue(QueueType *q)
{
    q->front=q->rear=0;
}

int is_full(QueueType *q)
{
    return((q->rear+1)%MAX_QUEUE_SIZE==q->front);
}

int is_empty(QueueType *q)
{
    return(q->front==q->rear);
}

void enqueue(QueueType *q,element item)
{
    if(is_full(q)){
        error("큐가 포화상태입니다.");
        return;
    }
    q->rear=(q->rear+1)%MAX_QUEUE_SIZE;
    q->data[q->rear]=item;
}

element dequeue(QueueType *q)
{
    if(is_empty(q))
        error("큐가 공백상태입니다.");
    q->front=(q->front+1)%MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int top=-1;
TreeNode *stack[SIZE];

void push(TreeNode *p)
{
    if(top<SIZE -1)
        stack[++top]=p;
}

TreeNode *pop()
{
    TreeNode *p=NULL;
    if(top>=0)
        p=stack[top--];
    return p;
}

void preorder(TreeNode *root)
{
    if(root!=NULL){
        printf("[%c]",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(TreeNode *root)
{
    if(root!=NULL){
        inorder(root->left);
        printf("[%c]",root->data);
        inorder(root->right);
    }
}

void postorder(TreeNode *root)
{
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("[%c]",root->data);
    }
}

void level_order(TreeNode *ptr)
{
    QueueType q;
    init_queue(&q);
    if(ptr==NULL)
        return;
    enqueue(&q,ptr);
    while(!is_empty(&q)){
        ptr=dequeue(&q);
        printf("[%c]",ptr->data);
        if(ptr->left)
            enqueue(&q,ptr->left);
        if(ptr->right)
            enqueue(&q,ptr->right);
    }
}

TreeNode n1 ={'I',NULL,NULL}; //i
TreeNode n2 ={'J',NULL,NULL};  //j
TreeNode n3 ={'D',&n1,&n2};   //d
TreeNode n4 ={'F',NULL,NULL};  //f
TreeNode n5 ={'B',&n3,&n4};  //b
TreeNode n6 ={'K',NULL,NULL}; //k
TreeNode n7 ={'G',NULL,&n6};  //G
TreeNode n8 ={'H',NULL,NULL};   //H
TreeNode n9 ={'C',&n7,&n8};    //c
TreeNode n10 ={'A',&n5,&n9}; //A
TreeNode *root =&n10;

int main()
{
    int n;
    while(1){
    printf("\n순회 방법을 선택하세요\n");
    printf("1.레벨 순회 2.전위 순회 3.중위 순회 4.후위 순회 5.종료\n");
    scanf("%d",&n);
    switch(n){
case 1:
    printf("레벨순회=");
    level_order(root);
    printf("\n");
    break;
case 2:
    printf("전위 순회=");
    preorder(root);
    printf("\n");
    break;
case 3:
    printf("중위 순회=");
    inorder(root);
    printf("\n");
    break;
case 4:
    printf("후위 순회=");
    postorder(root);
    printf("\n");
    break;
case 5:
    printf("프로그램 종료");
    return 0;
    }
    }
}
