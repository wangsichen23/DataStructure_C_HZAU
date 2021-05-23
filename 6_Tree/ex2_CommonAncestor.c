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

BiTree CreateBiTree(char *PreOrderPut,char *InOrderPut,int length)
{
    if(length==0)
        return NULL;

    int i=0;
    char ch=PreOrderPut[0];

    while(InOrderPut[i]!=ch && i<length)
        i=i+1;

    BiTNode *T;
    T=(BiTNode*)malloc(sizeof(BiTNode));
    T->data=ch;
    T->LChild=CreateBiTree(&PreOrderPut[1], &InOrderPut[0], i);
    T->RChild=CreateBiTree(&PreOrderPut[i+1], &InOrderPut[i+1], length-i-1);

    return T;
}

BiTree CommonAncestor(BiTree bt,char a,char b)
{
    BiTree LeftTree,RightTree;

    if(bt==NULL)
        return NULL;

    if(bt->data==a||bt->data==b)
        return bt;

    LeftTree=CommonAncestor(bt->LChild,a,b);
    RightTree=CommonAncestor(bt->RChild,a,b);

    if(LeftTree!=NULL && RightTree!=NULL)
        return bt;
    else if(LeftTree!=NULL)
        return LeftTree;
    else
        return RightTree;
}

int main()
{
    BiTree bt;
    int length;
    char PreOrderPut[MAXSIZE],InOrderPut[MAXSIZE];
    char Child1,Child2;

    scanf("%s",PreOrderPut);
    scanf("%s",InOrderPut);
    scanf("%c",&Child1);
    scanf("%c",&Child2);

    length=strlen(PreOrderPut);

    bt=(BiTNode*)malloc(sizeof(BiTNode));
    bt=CreateBiTree(PreOrderPut,InOrderPut,length);

    BiTNode *ca=CommonAncestor(bt,Child1,Child2);

    if(ca==NULL)
        printf("NULL");
    else
        printf("%c",ca->data);

    return 0;
}
