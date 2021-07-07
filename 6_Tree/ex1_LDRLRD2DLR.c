/*
【问题描述】
 已知一个二叉树的中序遍历序列和后序遍历序列，
 求这棵树的前序遍历序列。

【输入形式】
 一个树的中序遍历序列 该树后序遍历序列，中间用空格分开。
 输入序列中仅含有小写字母,且没有重复的字母

【输出形式】
 一个树的前序遍历序列

【样例输入】
 dbeafcg debfgca

【样例输出】
 abdecfg
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 100

typedef char DataType;

typedef struct Node
{//定义二叉树
	DataType data;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode, *BiTree;

BiTNode* CreateBiTree(char *InOrderPut,char *PostOrderPut,int length)
{//根据中序及后续遍历建立二叉树
    int i=0,leftlength,rightlength;
    char ch=PostOrderPut[length-1];//根绝点

    if(length==0)
        return NULL;

    while(InOrderPut[i]!=ch&&i<length)
        i++;
    leftlength=i; //左子树长
    rightlength=length-i-1; //右子树长度

    BiTNode *T;
    T=(BiTNode*)malloc(sizeof(BiTNode));
    T->data=ch; //根节点
    T->LChild=CreateBiTree(&InOrderPut[0], &PostOrderPut[0], leftlength);
    T->RChild=CreateBiTree(&InOrderPut[i+1], &PostOrderPut[i], rightlength);

    return T;
}

void PreOrderTraverse(BiTNode *root)
{//先序遍历二叉树
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
    int length;
    char InOrderPut[MAXSIZE]; //中序遍历二叉树
    char PostOrderPut[MAXSIZE]; //后序遍历二叉树
    scanf("%s", InOrderPut);
    scanf("%s", PostOrderPut);
    length=strlen(InOrderPut);
    bt=(BiTNode*)malloc(sizeof(BiTNode));
    bt=CreateBiTree(InOrderPut,PostOrderPut,length);
    PreOrderTraverse(bt);
    return 0;
}
