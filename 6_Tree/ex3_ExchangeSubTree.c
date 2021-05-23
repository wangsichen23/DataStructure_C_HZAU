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
		*bt=(BiTree)malloc(sizeof(BiTNode)); //����һ���½��
        (*bt)->data=ch;
        CreateBiTree(&((*bt)->LChild)); //����������
        CreateBiTree(&((*bt)->RChild)); //����������
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
/* ���������������rootΪָ�������(��ĳһ����)������ָ��*/
{
	if(root!=NULL)
	{
		PostOrder(root->LChild); /*�������������*/
		PostOrder(root->RChild); /*�������������*/
		printf("%c",root->data); /*���ʸ����*/
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
