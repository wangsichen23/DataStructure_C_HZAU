/*
【问题描述】输入一个整数数组，判断该数组是不是某二叉查找树的后序遍历的结果。如果是返回true，否则返回false。
【输入形式】输入任意长度的数组，数字之间空格分开
【输出形式】true 或者 false
【样例输入】输入5 7 6 9 11 10 8
【样例输出】true
【样例说明】由于这一整数序列是如下树的后序遍历结果：
          8
       /      \
      6      10
    /   \     /   \
   5   7   9  11
因此返回true。
【评分标准】
暴力求解法不得分。
【提示】
后序遍历的最后一个结点一定是根结点，那么前面的数据就可以划分为比根小的、比根大的。依此类推下去。
*/
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
