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
	KeyType  key ; /*�ؼ��ֵ�ֵ*/
	struct node  *lchild,*rchild;/*����ָ��*/
}BSTNode, *BSTree;

void InsertBST(BSTree *bst, KeyType key)
{ /*���ڶ����������в����ڹؼ��ֵ���key��Ԫ�أ������Ԫ��*/
	BSTree s;
	if (*bst == NULL)/*�ݹ��������*/
	{
		s=(BSTree)malloc(sizeof(BSTNode));/*�����µĽ��s*/
		s->key=key;
		s->lchild=NULL;
		s->rchild=NULL;
		*bst=s;
	}
	else if(key<(*bst)->key)
        InsertBST(&((*bst)->lchild), key);/*��s����������*/
    else if(key>(*bst)->key)
        InsertBST(&((*bst)->rchild), key); /*��s����������*/
}

void CreateBST(BSTree *bst,int a[],int n)
/*�Ӽ�������Ԫ�ص�ֵ��������Ӧ�Ķ���������*/
{
	*bst=NULL;
	int i;
	for(i=n-1;i>=0;i--)
        InsertBST(bst, a[i]);
}

void  PostOrder(BSTree root)
/* ���������������rootΪָ�������(��ĳһ����)������ָ��*/
{
	if(root!=NULL)
	{
		PostOrder(root->lchild); /*�������������*/
		PostOrder(root->rchild); /*�������������*/
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
