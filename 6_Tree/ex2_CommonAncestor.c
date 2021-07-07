/*
【问题描述】
假设二叉树采用二叉链表方式存储，
root指向根结点，p所指结点和q所指结点为二叉树中的两个不同结点，
且互不成为根到该结点的路径上的点，编程求解距离它们最近的共同祖先。

【输入形式】
二叉树的前序和中序遍历序列，用以创建该二叉树的链式存储结构；
以及二叉树的两个结点数据 x 和 y

【输出形式】
结点数据值为 x 和结点数据值为 y 的最近的共同祖先，若没有共同祖先则输出NULL

【样例输入】
GABDCEF
BDAEFCG
DF

【样例输出】
A
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef char DataType;

typedef struct Node
{//定义二叉树
	DataType data;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode, *BiTree;

BiTree CreateBiTree(char *PreOrderPut,char *InOrderPut,int length)
{//根据先序遍历及中序遍历创建二叉树
    int i=0,leftlength,rightlength;
    char ch=PreOrderPut[0];

    if(length==0)
        return NULL;

    while(InOrderPut[i]!=ch && i<length)
        i++; //根节点
    leftlength=i; //左子树长
    rightlength=length-i-1; //右子树长度

    BiTNode *T;
    T=(BiTNode*)malloc(sizeof(BiTNode));
    T->data=ch;
    T->LChild=CreateBiTree(&PreOrderPut[1], &InOrderPut[0], leftlength);
    T->RChild=CreateBiTree(&PreOrderPut[i+1], &InOrderPut[i+1], rightlength);

    return T;
}

BiTree CommonAncestor(BiTree bt,char a,char b)
{//寻找a与b的共同祖先
    BiTree LeftTree,RightTree;
    if(bt==NULL)
        return NULL;
    if(bt->data==a||bt->data==b)
        return bt;
    LeftTree=CommonAncestor(bt->LChild,a,b);
    RightTree=CommonAncestor(bt->RChild,a,b);

    if(LeftTree!=NULL && RightTree!=NULL)
        return bt;
    return LeftTree!=NULL ? LeftTree : RightTree;
}

int isAncestor(BiTree bt, char a)
{//判断是否bt为a的祖先
    if(bt==NULL)
        return FALSE;
    if(bt->data==a)
        return TRUE;
    else
        return(isAncestor(bt->LChild,a)||isAncestor(bt->RChild, a));
}

BiTree SearchCommon(BiTree bt,char a,char b)
{//寻找a与b的共同祖先
    int flag1,flag2;
    if(bt==NULL)
        return NULL; //没有找到或者node为空
    if(bt->data==a||bt->data==b)
        return NULL; //一个元素为根节点，另一个是子元素，无共同祖先
    flag1=isAncestor(bt->LChild,a);
    flag2=isAncestor(bt->LChild,b);
    if(flag1!=flag2)
        return bt; //a,b分别位于左右子树
    else
    {
        if(flag1==TRUE)
            return SearchCommon(bt->LChild,a,b);//a,b都在左子树
        else
            return SearchCommon(bt->RChild,a,b);//a,b都在右子树
    }
}

int main()
{
    BiTree bt,ca;
    int length=0;
    char PreOrderPut[MAXSIZE];
    char InOrderPut[MAXSIZE];
    char Child1,Child2;

    scanf("%s%s\n",PreOrderPut,InOrderPut);
    scanf("%c%c",&Child1,&Child2);
    length=strlen(PreOrderPut);

    bt=(BiTNode*)malloc(sizeof(BiTNode));
    bt=CreateBiTree(PreOrderPut,InOrderPut,length);
    /*2种方法*/
    ca=CommonAncestor(bt,Child1,Child2);
    ca=SearchCommon(bt,Child1,Child2);

    if(ca==NULL)
        printf("NULL");
    else
        printf("%c",ca->data);

    return 0;
}
