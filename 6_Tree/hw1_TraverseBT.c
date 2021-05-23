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

void  PreOrder(BiTree root)
/*先序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
{
	if (root!=NULL)
	{
		printf("%c ",root->data);  /*访问根结点*/
		PreOrder(root->LChild);  /*先序遍历左子树*/
		PreOrder(root->RChild);  /*先序遍历右子树*/
	}
}

void  InOrder(BiTree root)
/*中序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
{
	if (root!=NULL)
	{
		InOrder(root->LChild);   /*中序遍历左子树*/
		printf("%c ",root->data);  /*访问根结点*/
		InOrder(root->RChild);   /*中序遍历右子树*/
	}
}

void  PostOrder(BiTree root)
/* 后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
{
	if(root!=NULL)
	{
		PostOrder(root->LChild); /*后序遍历左子树*/
		PostOrder(root->RChild); /*后序遍历右子树*/
		printf("%c ",root->data); /*访问根结点*/
	}
}

int main()
{
    BiTree BT;
    CreateBiTree(&BT);

    PreOrder(BT);
    printf("\n");
    InOrder(BT);
    printf("\n");
    PostOrder(BT);
    printf("\n");

    return 0;
}
