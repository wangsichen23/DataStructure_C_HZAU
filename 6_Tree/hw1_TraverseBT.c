/*
问题描述】
给出一个按照先序遍历得出的字符串
'#' 代表空的子节点，大写字母代表节点内容。
请通过这个字符串建立二叉树
分别采用“递归”的先序、中序、后序遍历的算法输出每一个非空节点。

【输入形式】
输入只有一行
包含一个字符串S，用来建立二叉树。
保证S为合法的二叉树先序遍历字符串，节点内容只有大写字母
S的长度不超过100

【输出形式】
共有3行，每一行包含一串字符
分别按递归的先序、中序、后序遍历得出的节点内容
每个字母后输出一个空格。
行尾输出换行。

【样例输入】
ABC##DE#G##F###

【样例输出】
A B C D E G F
C B E G D F A
C G E F D B A
*/

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
        (*bt)->data=ch; //输入节点字符
        CreateBiTree(&((*bt)->LChild)); //生成左子树
        CreateBiTree(&((*bt)->RChild)); //生成右子树
	}
}

void  PreOrder(BiTree root)
{/*先序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
	if (root!=NULL)
	{
		printf("%c ",root->data);  /*访问根结点*/
		PreOrder(root->LChild);  /*先序遍历左子树*/
		PreOrder(root->RChild);  /*先序遍历右子树*/
	}
}

void  InOrder(BiTree root)
{/*中序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
	if (root!=NULL)
	{
		InOrder(root->LChild);   /*中序遍历左子树*/
		printf("%c ",root->data);  /*访问根结点*/
		InOrder(root->RChild);   /*中序遍历右子树*/
	}
}

void  PostOrder(BiTree root)
{/*后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
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
