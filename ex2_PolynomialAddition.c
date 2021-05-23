#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

typedef struct Polynode
{
	float coef;
	int exp;
	struct Polynode *next;
}Polynode, *Polylist;

void CreatePolylist(Polylist L, int n)
{
	Polynode *r, *s;
	int i, e;
	float c;
	r=L;
	for(i=0; i<n; i++)
	{
		scanf("%f",&c);
		scanf("%d",&e);
        s=(Polynode*)malloc(sizeof(Polynode));
        s->coef=c;
        s->exp=e;
        r->next=s;
        r=s;
	}
	r->next=NULL; //�����һ������next������Ϊ�գ���ʾ����Ľ���
}

void Sort(Polylist L, int n) //��������
{
    int i=0;
    int k=0;
    int exptem;
    float coeftem;
    Polynode *p;
    p=L->next;
    for(i=0;i<n-1;i++)
    {
        Polynode *s=p->next;
        for(k=i+1;k<n;k++)
        {
            if((s->exp)<(p->exp))
            {
                exptem=p->exp;
                p->exp=s->exp;
                s->exp=exptem;
                coeftem=p->coef;
                p->coef=s->coef;
                s->coef=coeftem;
            }
            s=s->next;
        }
        p=p->next;
    }
}

void ISort(Polylist L, int n) //��������
{
    int i=0;
    int k=0;
    int exptem;
    float coeftem;
    Polynode *p;
    p=L->next;
    for(i=0;i<n-1;i++)
    {
        Polynode *s=p->next;
        for(k=i+1;k<n;k++)
        {
            if((s->exp)>(p->exp))
            {
                exptem=p->exp;
                p->exp=s->exp;
                s->exp=exptem;
                coeftem=p->coef;
                p->coef=s->coef;
                s->coef=coeftem;
            }
            s=s->next;
        }
        p=p->next;
    }
}

void  polyadd(Polylist polya, Polylist polyb)
/*�˺������ڽ���������ʽ��ӣ�Ȼ�󽫺Ͷ���ʽ����ڶ���ʽpolya�У���������ʽploybɾ��*/
{
	Polynode  *p, *q, *pre, *temp;
	float sum;
	p=polya->next;   /*�� p��q�ֱ�ָ��polya��polyb����ʽ�����еĵ�һ�����*/
	q=polyb->next;
	pre=polya;  /* rָ��Ͷ���ʽ��β���*/
	while (p!=NULL && q!=NULL) /*����������ʽ��δɨ�����ʱ*/
	{
		if  (p->exp < q->exp)
			/*���pָ��Ķ���ʽ���ָ��С��q��ָ������p�����뵽�Ͷ���ʽ��*/
		{
			pre->next=p;
			pre=p;
			p=p->next;
		}
		else if ( p->exp == q->exp)  /*��ָ����ȣ�����Ӧ��ϵ�����*/
        {
            sum=p->coef + q->coef;
            if (sum != 0)
            {
                p->coef=sum;
                pre->next=p;
                pre=p;
                p=p->next;
                temp=q;
                q=q->next;
                free(temp);
            }
            else
            {
                temp=p;
                p=p->next;
                free(temp);
                temp=q;
                q=q->next;
                free(temp);
            }
        }
        else
        {
            pre->next=q;
            pre=q; /*��q�����뵽�Ͷ���ʽ��*/
            q = q->next;
        }
	}
	if(p!=NULL)  /*����ʽA�л���ʣ�࣬��ʣ��Ľ����뵽�Ͷ���ʽ��*/
		pre->next=p;
	else      /*���򣬽�B�еĽ����뵽�Ͷ���ʽ��*/
		pre->next=q;
}

int main()
{
    int na,nb,n,i;
    Polylist la,lb;
    Polynode *p;
    //Polynode *pa,*pb;

    la=(Polylist)malloc(sizeof(Polynode));
	la->next=NULL;
	scanf("%d ", &na);
	CreatePolylist(la, na);

	lb=(Polylist)malloc(sizeof(Polynode));
	lb->next=NULL;
	scanf("%d ", &nb);
	CreatePolylist(lb, nb);

    Sort(la,na);
	Sort(lb,nb);

	/* ����ʽ�ӷ��������
    pa=la->next;
	for(i=0;i<na;i++)
    {
        printf("%.1f %d ",pa->coef,pa->exp);
        pa=pa->next;
    }
    printf("\n");

    pb=lb->next;
    for(i=0;i<nb;i++)
    {
        printf("%.1f %d ",pb->coef,pb->exp);
        pb=pb->next;
    }
    printf("\n");*/

	polyadd(la,lb);

    n=0;
	p=la->next;
	while(p!=NULL)
    {
        n++;
        p=p->next;
    }

    ISort(la,n);

    /* ����ʽ��ӽ������
    pa=la->next;
	for(i=0;i<n;i++)
    {
        printf("%.1f %d ",pa->coef,pa->exp);
        pa=pa->next;
    }
    printf("\n");*/

    p=la->next;
    scanf("%d",&n);
	for(i=1;i<n;i++)
        p=p->next;

    printf("%.1f %d",p->coef,p->exp);

    return 0;

}
