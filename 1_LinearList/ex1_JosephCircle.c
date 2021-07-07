/*
【问题描述】根据课堂上讲解的用顺序表实现约瑟夫环问题，请用单链表实现约瑟夫环问题
【输入形式】n为总人数，m为报数密码
【输出形式】最终胜利者编号
【样例输入】6 4
【样例输出】5
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *LinkList;

void Createlist(LinkList L, int n)
{
    int i;
    Node *r,*s;
    r=L;
    r->data=1;
    for(i=1;i<n;i++)
    {
        s=(Node*)malloc(sizeof(Node));
        s->data=i+1;
        r->next=s;
        r=s;
    }
    r->next=L;
}

void Joseph(LinkList L,int n,int k)
{
    int i,j;
    Node *p,*q;
    p=L;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<k-2;j++)
            p=p->next;
        q=p->next;
        //printf("%d ",q->data);
        p->next=q->next;
        p=p->next;
        free(q);
    }
    printf("%d",p->data);
}

int main()
{
    int n,m;
    //Node *p;

    LinkList L;
    L=(LinkList)malloc(sizeof(Node));

    scanf("%d %d",&n,&m);
    Createlist(L,n);

    /*
    p = L;
	while(p->next!=L)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
	*/

	Joseph(L,n,m);
    return 0;
}
