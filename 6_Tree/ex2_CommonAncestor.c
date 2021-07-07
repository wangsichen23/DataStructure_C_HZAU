/*
������������
������������ö�������ʽ�洢��
rootָ�����㣬p��ָ����q��ָ���Ϊ�������е�������ͬ��㣬
�һ�����Ϊ�����ý���·���ϵĵ㣬�����������������Ĺ�ͬ���ȡ�

��������ʽ��
��������ǰ�������������У����Դ����ö���������ʽ�洢�ṹ��
�Լ�������������������� x �� y

�������ʽ��
�������ֵΪ x �ͽ������ֵΪ y ������Ĺ�ͬ���ȣ���û�й�ͬ���������NULL

���������롿
GABDCEF
BDAEFCG
DF

�����������
A
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef char DataType;

typedef struct Node
{//���������
	DataType data;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode, *BiTree;

BiTree CreateBiTree(char *PreOrderPut,char *InOrderPut,int length)
{//������������������������������
    int i=0,leftlength,rightlength;
    char ch=PreOrderPut[0];

    if(length==0)
        return NULL;

    while(InOrderPut[i]!=ch && i<length)
        i++; //���ڵ�
    leftlength=i; //��������
    rightlength=length-i-1; //����������

    BiTNode *T;
    T=(BiTNode*)malloc(sizeof(BiTNode));
    T->data=ch;
    T->LChild=CreateBiTree(&PreOrderPut[1], &InOrderPut[0], leftlength);
    T->RChild=CreateBiTree(&PreOrderPut[i+1], &InOrderPut[i+1], rightlength);

    return T;
}

BiTree CommonAncestor(BiTree bt,char a,char b)
{//Ѱ��a��b�Ĺ�ͬ����
    BiTree LeftTree,RightTree;
    if(bt==NULL)
        return NULL;
    if(bt->data==a||bt->data==b)
        return bt;
    LeftTree=CommonAncestor(bt->LChild,a,b);
    RightTree=CommonAncestor(bt->RChild,a,b);

    if(LeftTree!=NULL && RightTree!=NULL)
        return bt;
    return LeftTree!=NULL ? LeftTree : RightTree;
}

int isAncestor(BiTree bt, char a)
{//�ж��Ƿ�btΪa������
    if(bt==NULL)
        return FALSE;
    if(bt->data==a)
        return TRUE;
    else
        return(isAncestor(bt->LChild,a)||isAncestor(bt->RChild, a));
}

BiTree SearchCommon(BiTree bt,char a,char b)
{//Ѱ��a��b�Ĺ�ͬ����
    int flag1,flag2;
    if(bt==NULL)
        return NULL; //û���ҵ�����nodeΪ��
    if(bt->data==a||bt->data==b)
        return NULL; //һ��Ԫ��Ϊ���ڵ㣬��һ������Ԫ�أ��޹�ͬ����
    flag1=isAncestor(bt->LChild,a);
    flag2=isAncestor(bt->LChild,b);
    if(flag1!=flag2)
        return bt; //a,b�ֱ�λ����������
    else
    {
        if(flag1==TRUE)
            return SearchCommon(bt->LChild,a,b);//a,b����������
        else
            return SearchCommon(bt->RChild,a,b);//a,b����������
    }
}

int main()
{
    BiTree bt,ca;
    int length=0;
    char PreOrderPut[MAXSIZE];
    char InOrderPut[MAXSIZE];
    char Child1,Child2;

    scanf("%s%s\n",PreOrderPut,InOrderPut);
    scanf("%c%c",&Child1,&Child2);
    length=strlen(PreOrderPut);

    bt=(BiTNode*)malloc(sizeof(BiTNode));
    bt=CreateBiTree(PreOrderPut,InOrderPut,length);
    /*2�ַ���*/
    ca=CommonAncestor(bt,Child1,Child2);
    ca=SearchCommon(bt,Child1,Child2);

    if(ca==NULL)
        printf("NULL");
    else
        printf("%c",ca->data);

    return 0;
}
