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

void  PreOrder(BiTree root)
/*�������������, rootΪָ�������(��ĳһ����)������ָ��*/
{
	if (root!=NULL)
	{
		printf("%c ",root->data);  /*���ʸ����*/
		PreOrder(root->LChild);  /*�������������*/
		PreOrder(root->RChild);  /*�������������*/
	}
}

void  InOrder(BiTree root)
/*�������������, rootΪָ�������(��ĳһ����)������ָ��*/
{
	if (root!=NULL)
	{
		InOrder(root->LChild);   /*�������������*/
		printf("%c ",root->data);  /*���ʸ����*/
		InOrder(root->RChild);   /*�������������*/
	}
}

void  PostOrder(BiTree root)
/* ���������������rootΪָ�������(��ĳһ����)������ָ��*/
{
	if(root!=NULL)
	{
		PostOrder(root->LChild); /*�������������*/
		PostOrder(root->RChild); /*�������������*/
		printf("%c ",root->data); /*���ʸ����*/
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
