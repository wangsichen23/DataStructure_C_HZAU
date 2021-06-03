#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;

typedef struct node
{
	KeyType key ; /*关键字的值*/
	struct node *lchild,*rchild;/*左右指针*/
}BSTNode, *BSTree;

void InsertBST(BSTree *bst, KeyType key)
{/*若在二叉排序树中不存在关键字等于key的元素，插入该元素*/
	BSTree s;
	if (*bst==NULL)/*递归结束条件*/
	{
		s=(BSTree)malloc(sizeof(BSTNode));/*申请新的结点s*/
		s->key=key;
		s->lchild=NULL;
		s->rchild=NULL;
		*bst=s;
	}
	else if (key<(*bst)->key)
			InsertBST(&((*bst)->lchild), key);/*将s插入左子树*/
    else if (key>(*bst)->key)
            InsertBST(&((*bst)->rchild), key); /*将s插入右子树*/
}

void CreateBST(BSTree *bst)
{/*从键盘输入元素的值，创建相应的二叉排序树*//*从键盘输入元素的值，创建相应的二叉排序树*/
	KeyType key;
	*bst=NULL;
	scanf("%d", &key);
	while (key!=0)   /*ENDKEY为自定义常量*/
	{
		InsertBST(bst, key);
		scanf("%d", &key);
	}
}

void PreOrder(BSTree root)
{/*先序遍历二叉树, root为指向二叉树根结点的指针*/
	if (root!=NULL)
	{
		printf("%d ",root->key);  /*输出结点*/
		PreOrder(root->lchild);  /*先序遍历左子树*/
		PreOrder(root->rchild);  /*先序遍历右子树*/
	}
	else
        printf("# ");
}

void InOrder(BSTree root)
{/*中序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
	if (root!=NULL)
	{
		InOrder(root->lchild);   /*中序遍历左子树*/
		printf("%d ",root->key);  /*访问根结点*/
		InOrder(root->rchild);   /*中序遍历右子树*/
	}
}

BSTNode *DelBST(BSTree t, KeyType k)
{/*在二叉排序树t中删去关键字为k的结点*/
	BSTNode *p, *f,*s ,*q;
	p=t;
	f=NULL;
	while(p)  /*查找关键字为k的待删结点p*/
	{
		if(p->key==k)
            break;  /*找到则跳出循环*/
		f=p;   /*f指向p结点的双亲结点*/
		if(p->key>k)
			p=p->lchild;
		else
			p=p->rchild;
	}
	if(p==NULL)
        return t;  /*若找不到，返回原来的二叉排序树*/
	if(p->lchild==NULL)  /*p无左子树*/
	{
		if(f==NULL)
			t=p->rchild;  /*p是原二叉排序树的根*/
		else if(f->lchild==p)  /*p是f的左孩子*/
            f->lchild=p->rchild ;  /*将p的右子树链到f的左链上*/
        else  /*p是f的右孩子*/
            f->rchild=p->rchild ;  /*将p的右子树链到f的右链上*/
        free(p);  /*释放被删除的结点p*/
	}
	else  /*p有左子树*/
	{
		q=p;
		s=p->lchild;
		while(s->rchild)  /*在p的左子树中查找最右下结点*/
		{
			q=s;
			s=s->rchild;
		}
		if(q==p)
			q->lchild=s->lchild ;  /*将s的左子树链到q上*/
		else
			q->rchild=s->lchild;
		p->key=s->key;  /*将s的值赋给p*/
		free(s);
	}
	return t;
}

void SearchLayer(BSTree bst, KeyType key)
{
	int a=0;
	BSTree q;
	q=bst;
	while(q)
	{
		if (q->key==key)
        {
            a++;
            printf("%d",a);
        }  /*查找成功*/
		if (q->key>key)
		{
		    q=q->lchild;  /*在左子树中查找*/
			a++;
        }
		else
        {
            q=q->rchild;  /*在右子树中查找*/
            a++;
        }
	}
}

int main()
{
	int a,b;
	BSTree T,result;
    CreateBST(&T);
    scanf("%d",&a);
    scanf("%d",&b);
	PreOrder(T);
	printf("\n");
	result=DelBST(T,a);
	InOrder(result);
	printf("\n");
	SearchLayer(result,b);
	return 0;
}
