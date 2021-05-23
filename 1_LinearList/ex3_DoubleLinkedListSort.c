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
