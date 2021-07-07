/*
【问题描述】第4讲循环链表里的考研真题，
带头结点的双向循环链表的排序，请编程实现双向循环链表及其排序。
【输入形式】随机的数据
【输出形式】排序后的数据
【样例输入】5 7 2 8 1 3 4 9 6 0
【样例输出】1 2 3 4 5 6 7 8 9
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

typedef struct DNode
{
    int data;
    struct DNode *prior,*next;
} DNode, *DoubleList;

int CreateDoubleList(DoubleList L)
{
	DNode *r, *s;
	int c;
	int flag =1;
	int i=0;
	r=L;
	while(flag)
	{
		scanf("%d",&c);
		if(c != 0)
		{
			s=(DNode*)malloc(sizeof(DNode));
			s->data=c;
			r->next=s;
			r=s;
			i++;
		}
		else
		{
			flag=0;
			r->next=L;
		}
	}
	return i;
}

void Sort(DoubleList L, int n) //ÉýÐòÅÅÁÐ
{
    int i=0;
    int k=0;
    int tem;
    DNode *p;
    p=L->next;
    for(i=0;i<n-1;i++)
    {
        DNode *s=p->next;
        for(k=i+1;k<n;k++)
        {
            if((s->data)<(p->data))
            {
                tem=p->data;
                p->data=s->data;
                s->data=tem;
            }
            s=s->next;
        }
        p=p->next;
    }
}


int main()
{
    int n;
    DoubleList L;
    DNode *p;
    L=(DoubleList)malloc(sizeof(DNode));

    n=CreateDoubleList(L);
    Sort(L, n);

    p=L->next;
	while(p!=L)
	{
		printf("%d ",p->data);
		p=p->next;
	}

    return 0;
}
