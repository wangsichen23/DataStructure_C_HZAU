#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

typedef struct Node //定义节点类型
{
	int data; //定义数据域
	struct Node* next; //定义指针域
} Node, *LinkList; //定义节点与头指针类型

void CreateFromTail(LinkList L, int n) //尾插法创建单链表
{
	Node *r, *s;
	int i, c;
	r=L; //r指针动态指向链表的当前表尾，以便于做尾插入，其初值指向头结点
	for(i=0; i<n; i++) //循环输入表中元素值，将建立新结点s插入表尾
	{
		scanf("%d",&c);
        s=(Node*)malloc(sizeof(Node));
        s->data=c;
        r->next=s;
        r=s;
	}
	r->next=NULL; //将最后一个结点的next链域置为空，表示链表的结束
}

LinkList MergeLinkList(LinkList LA, LinkList LB) //将单链表LA和LB合并成单链表LC
{
	Node *pa,*pb,*r;

	pa=LA->next; //pa指向单链表LA中的第一个结点
	pb=LB->next; //pb指向单链表LB中的第一个结点

    LinkList LC; //将LC初始置空表
	LC=(Node * )malloc(sizeof(Node));
	LC->next=NULL;
	r=LC;

	while(pa!=NULL && pb!=NULL) //当两个表中均未处理完时，比较选择将较小值结点插入到新表LC中
	{
		if(pa->data <= pb->data)
		{
			r->next=pa;
			r=r->next;
			pa=pa->next;
		}
		else
		{
			r->next=pb;
			r=r->next;
			pb=pb->next;
		}
	}

	if(pa) //若表LA未完，将表LA中后续元素链到新表LC表尾
		r->next=pa;
	else //若表LB未完，将表LB中后续元素链到新表LC表尾
		r->next=pb;

	return(LC);
}

void DelLinkList(LinkList L) //删除列表中的重复值
{
	Node *p,*r;
	p=L;
	r=p->next;
    while(p->next != NULL)
    {
        if(p->data == r->data)
        {
            p->next=p->next->next;
            free(r);
            r=p->next;
        }
        else
        {
            p=p->next;
            r=p->next;
        }
    }
}

int main()
{
	LinkList la,lb,lc;
	Node *p;
	int na, nb;

	la=(Node * )malloc(sizeof(Node));
	la->next=NULL;
	scanf("%d ", &na);
	CreateFromTail(la, na);

    lb=(Node * )malloc(sizeof(Node));
	lb->next=NULL;
	scanf("%d ", &nb);
	CreateFromTail(lb, nb);

	lc=MergeLinkList(la,lb);
	DelLinkList(lc);

    /*p = la->next;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");

	p = lb->next;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");*/

	p = lc->next;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	return 0;
}
