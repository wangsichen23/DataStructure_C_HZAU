#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

typedef struct Node //����ڵ�����
{
	int data; //����������
	struct Node* next; //����ָ����
} Node, *LinkList; //����ڵ���ͷָ������

void CreateFromTail(LinkList L, int n) //β�巨����������
{
	Node *r, *s;
	int i, c;
	r=L; //rָ�붯ָ̬������ĵ�ǰ��β���Ա�����β���룬���ֵָ��ͷ���
	for(i=0; i<n; i++) //ѭ���������Ԫ��ֵ���������½��s�����β
	{
		scanf("%d",&c);
        s=(Node*)malloc(sizeof(Node));
        s->data=c;
        r->next=s;
        r=s;
	}
	r->next=NULL; //�����һ������next������Ϊ�գ���ʾ����Ľ���
}

LinkList MergeLinkList(LinkList LA, LinkList LB) //��������LA��LB�ϲ��ɵ�����LC
{
	Node *pa,*pb,*r;

	pa=LA->next; //paָ������LA�еĵ�һ�����
	pb=LB->next; //pbָ������LB�еĵ�һ�����

    LinkList LC; //��LC��ʼ�ÿձ�
	LC=(Node * )malloc(sizeof(Node));
	LC->next=NULL;
	r=LC;

	while(pa!=NULL && pb!=NULL) //���������о�δ������ʱ���Ƚ�ѡ�񽫽�Сֵ�����뵽�±�LC��
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

	if(pa) //����LAδ�꣬����LA�к���Ԫ�������±�LC��β
		r->next=pa;
	else //����LBδ�꣬����LB�к���Ԫ�������±�LC��β
		r->next=pb;

	return(LC);
}

void DelLinkList(LinkList L) //ɾ���б��е��ظ�ֵ
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
