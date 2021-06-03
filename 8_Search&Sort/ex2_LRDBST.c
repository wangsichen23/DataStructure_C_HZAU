#include <stdio.h>
#include <stdlib.h>

#define OK   1
#define ERROR  -1
#define TRUE 1
#define FALSE 0

typedef int KeyType;

int x[20],label=0;

typedef struct  node
{
	KeyType  key ; /*关键字的值*/
	struct node  *lchild,*rchild;/*左右指针*/
}BSTNode, *BSTree;

void InsertBST(BSTree *bst, KeyType key)
{ /*若在二叉排序树中不存在关键字等于key的元素，插入该元素*/
	BSTree s;
	if (*bst == NULL)/*递归结束条件*/
	{
		s=(BSTree)malloc(sizeof(BSTNode));/*申请新的结点s*/
		s->key=key;
		s->lchild=NULL;
		s->rchild=NULL;
		*bst=s;
	}
	else if(key<(*bst)->key)
        InsertBST(&((*bst)->lchild), key);/*将s插入左子树*/
    else if(key>(*bst)->key)
        InsertBST(&((*bst)->rchild), key); /*将s插入右子树*/
}

void CreateBST(BSTree *bst,int a[],int n)
/*从键盘输入元素的值，创建相应的二叉排序树*/
{
	*bst=NULL;
	int i;
	for(i=n-1;i>=0;i--)
        InsertBST(bst, a[i]);
}

void  PostOrder(BSTree root)
/* 后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
{
	if(root!=NULL)
	{
		PostOrder(root->lchild); /*后序遍历左子树*/
		PostOrder(root->rchild); /*后序遍历右子树*/
		x[label]=root->key;
		label++;
	}
}

int main()
{
	BSTree T;
	int i=0,n=0,flag=1;
    int *a=(int*)malloc(n*sizeof(int));
    char b;

    while((b=getchar())!='\n')
    {
        ungetc(b,stdin);
        a = (int*)realloc(a,++n*sizeof(int));
        scanf("%d",&a[i++]);
    }
    CreateBST(&T,a,n);
	PostOrder(T);
    for(i=0;i<n;i++)
        if(a[i]!=x[i])
            flag=0;
    if(flag)
        printf("true");
    else
        printf("false");
	return 0;
}
