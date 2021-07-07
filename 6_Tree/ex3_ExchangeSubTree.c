/*
【问题描述】
二叉树按照二叉链表的方式存储。
编写程序，计算二叉树中叶子结点的数目并输出；
编写程序，将二叉树的左右子树进行交换，并输出交换后的二叉树的后序遍历序列。

【输入形式】
二叉树的前序遍历序列，空指针的位置输入字符#

【输出形式】
叶子结点的数目
左右子树交换后，后序遍历的序列，空子树的位置输出字符#

【样例输入】
ABE##F##CG###

【样例输出】
3
###GC##F##EBA*/

#include <stdio.h>
#include <malloc.h>

typedef char DataType;

typedef struct Node
{//定义二叉树
	DataType data;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree *bt)
{//创建二叉树
	char ch;
	ch = getchar();
    if(ch=='#')
        *bt=NULL;
    else
	{
		*bt=(BiTree)malloc(sizeof(BiTNode)); //生成一个新结点
        (*bt)->data=ch;
        CreateBiTree(&((*bt)->LChild)); //生成左子树
        CreateBiTree(&((*bt)->RChild)); //生成右子树
	}
}

int CountRoot(BiTree bt)
{//计算二叉树中叶子结点的数目
    int n=0;
    if(bt==NULL)
        n=0;
    else if(bt->LChild==NULL && bt->RChild==NULL)
        n=1;
    else
        n=CountRoot(bt->LChild)+CountRoot(bt->RChild);
    return n;
}

void ExchangeSubTree(BiTree bt)
{//将二叉树的左右子树进行交换
    BiTNode *temp;
    if(bt!=NULL)
	{
        temp=bt->LChild;
        bt->LChild=bt->RChild;
        bt->RChild=temp;
	    ExchangeSubTree(bt->LChild);
        ExchangeSubTree(bt->RChild);
	}
}

void  PostOrder(BiTree root)
{ /*后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
	if(root!=NULL)
	{
		PostOrder(root->LChild); /*后序遍历左子树*/
		PostOrder(root->RChild); /*后序遍历右子树*/
		printf("%c",root->data); /*访问根结点*/
	}
	else
        printf("#");
}

int main()
{
    BiTree BT;
    CreateBiTree(&BT);
    printf("%d\n",CountRoot(BT));
    ExchangeSubTree(BT);
    PostOrder(BT);
    return 0;
}
