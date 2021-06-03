#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;

typedef struct node
{
	KeyType key ; /*�ؼ��ֵ�ֵ*/
	struct node *lchild,*rchild;/*����ָ��*/
}BSTNode, *BSTree;

void InsertBST(BSTree *bst, KeyType key)
{/*���ڶ����������в����ڹؼ��ֵ���key��Ԫ�أ������Ԫ��*/
	BSTree s;
	if (*bst==NULL)/*�ݹ��������*/
	{
		s=(BSTree)malloc(sizeof(BSTNode));/*�����µĽ��s*/
		s->key=key;
		s->lchild=NULL;
		s->rchild=NULL;
		*bst=s;
	}
	else if (key<(*bst)->key)
			InsertBST(&((*bst)->lchild), key);/*��s����������*/
    else if (key>(*bst)->key)
            InsertBST(&((*bst)->rchild), key); /*��s����������*/
}

void CreateBST(BSTree *bst)
{/*�Ӽ�������Ԫ�ص�ֵ��������Ӧ�Ķ���������*//*�Ӽ�������Ԫ�ص�ֵ��������Ӧ�Ķ���������*/
	KeyType key;
	*bst=NULL;
	scanf("%d", &key);
	while (key!=0)   /*ENDKEYΪ�Զ��峣��*/
	{
		InsertBST(bst, key);
		scanf("%d", &key);
	}
}

void PreOrder(BSTree root)
{/*�������������, rootΪָ�������������ָ��*/
	if (root!=NULL)
	{
		printf("%d ",root->key);  /*������*/
		PreOrder(root->lchild);  /*�������������*/
		PreOrder(root->rchild);  /*�������������*/
	}
	else
        printf("# ");
}

void InOrder(BSTree root)
{/*�������������, rootΪָ�������(��ĳһ����)������ָ��*/
	if (root!=NULL)
	{
		InOrder(root->lchild);   /*�������������*/
		printf("%d ",root->key);  /*���ʸ����*/
		InOrder(root->rchild);   /*�������������*/
	}
}

BSTNode *DelBST(BSTree t, KeyType k)
{/*�ڶ���������t��ɾȥ�ؼ���Ϊk�Ľ��*/
	BSTNode *p, *f,*s ,*q;
	p=t;
	f=NULL;
	while(p)  /*���ҹؼ���Ϊk�Ĵ�ɾ���p*/
	{
		if(p->key==k)
            break;  /*�ҵ�������ѭ��*/
		f=p;   /*fָ��p����˫�׽��*/
		if(p->key>k)
			p=p->lchild;
		else
			p=p->rchild;
	}
	if(p==NULL)
        return t;  /*���Ҳ���������ԭ���Ķ���������*/
	if(p->lchild==NULL)  /*p��������*/
	{
		if(f==NULL)
			t=p->rchild;  /*p��ԭ�����������ĸ�*/
		else if(f->lchild==p)  /*p��f������*/
            f->lchild=p->rchild ;  /*��p������������f��������*/
        else  /*p��f���Һ���*/
            f->rchild=p->rchild ;  /*��p������������f��������*/
        free(p);  /*�ͷű�ɾ���Ľ��p*/
	}
	else  /*p��������*/
	{
		q=p;
		s=p->lchild;
		while(s->rchild)  /*��p���������в��������½��*/
		{
			q=s;
			s=s->rchild;
		}
		if(q==p)
			q->lchild=s->lchild ;  /*��s������������q��*/
		else
			q->rchild=s->lchild;
		p->key=s->key;  /*��s��ֵ����p*/
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
        }  /*���ҳɹ�*/
		if (q->key>key)
		{
		    q=q->lchild;  /*���������в���*/
			a++;
        }
		else
        {
            q=q->rchild;  /*���������в���*/
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
