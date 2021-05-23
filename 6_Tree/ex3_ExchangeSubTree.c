#include <stdio.h>
#include <malloc.h>
//#include <conio.h>

typedef char DataType;

typedef struct Node
{
	DataType data;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree *bt)
{
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
{
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
{
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
/* 后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
{
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
