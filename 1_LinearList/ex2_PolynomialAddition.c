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
	r->next=NULL; //将最后一个结点的next链域置为空，表示链表的结束
}

void Sort(Polylist L, int n) //升序排列
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

void ISort(Polylist L, int n) //降序排列
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
/*此函数用于将两个多项式相加，然后将和多项式存放在多项式polya中，并将多项式ployb删除*/
{
	Polynode  *p, *q, *pre, *temp;
	float sum;
	p=polya->next;   /*令 p和q分别指向polya和polyb多项式链表中的第一个结点*/
	q=polyb->next;
	pre=polya;  /* r指向和多项式的尾结点*/
	while (p!=NULL && q!=NULL) /*当两个多项式均未扫描结束时*/
	{
		if  (p->exp < q->exp)
			/*如果p指向的多项式项的指数小于q的指数，将p结点加入到和多项式中*/
		{
			pre->next=p;
			pre=p;
			p=p->next;
		}
		else if ( p->exp == q->exp)  /*若指数相等，则相应的系数相加*/
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
            pre=q; /*将q结点加入到和多项式中*/
            q = q->next;
        }
	}
	if(p!=NULL)  /*多项式A中还有剩余，则将剩余的结点加入到和多项式中*/
		pre->next=p;
	else      /*否则，将B中的结点加入到和多项式中*/
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

	/* 多项式加法结果测试
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

    /* 多项式相加结果检验
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
