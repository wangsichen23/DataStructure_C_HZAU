#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 100

typedef char DataType;

typedef struct Node
{
	DataType data;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode, *BiTree;

BiTNode* CreateBiTree(char *InOrderPut,char *PostOrderPut,int length)
{
    int i=0,leftlength,rightlength;
    char ch=PostOrderPut[length-1];

    if(length==0)
        return NULL;

    while(InOrderPut[i]!=ch && i<length)
        i++;

    leftlength=i;
    rightlength=length-i-1;

    BiTNode *T;
    T=(BiTNode*)malloc(sizeof(BiTNode));

    T->data=ch;
    T->LChild=CreateBiTree(&InOrderPut[0], &PostOrderPut[0], leftlength);
    T->RChild=CreateBiTree(&InOrderPut[i+1], &PostOrderPut[i], rightlength);

    return T;
}

void PreOrderTraverse(BiTNode *root)
{
    if(root!=NULL)
    {
        printf("%c", root->data);
        PreOrderTraverse(root->LChild);
        PreOrderTraverse(root->RChild);
    }
}

int main()
{
    BiTNode *bt;
    char InOrderPut[MAXSIZE];
    char PostOrderPut[MAXSIZE];
    int length;

    scanf("%s", InOrderPut);
    scanf("%s", PostOrderPut);

    length=strlen(InOrderPut);

    bt=(BiTNode*)malloc(sizeof(BiTNode));
    bt=CreateBiTree(InOrderPut, PostOrderPut, length);
    PreOrderTraverse(bt);

    return 0;
}
