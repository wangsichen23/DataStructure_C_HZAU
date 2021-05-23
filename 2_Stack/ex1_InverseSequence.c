#include<stdio.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0

#define Stack_Size 1001

typedef struct
{
    char elem[Stack_Size];
    int top;
}SeqStack;

void InitStack(SeqStack *S)
{
    S->top=-1;
}

int Push(SeqStack *S,char x)
{
    if(S->top==Stack_Size-1)
        return(FALSE);
    S->top++;
    S->elem[S->top]=x;
    return(TRUE);
}

int Pop(SeqStack *S,char *x)
{
    if(S->top==-1)
        return(FALSE);
    else
    {
        *x=S->elem[S->top];
        S->top--;
        return(TRUE);
    }
}

int main()
{
    SeqStack S;
	InitStack(&S);
	int l=0;
	char ch,p='0';
	ch=getchar();
	while(ch!='&')
    {
		Push(&S,ch);
		l++;
		ch=getchar();
	}
	if(ch=='&')
	{
	    ch=getchar();
	    while(ch!='@')
		{
			Pop(&S,&p);
			if(ch==p)
                ch=getchar();
            else
            {
                printf("no");
                return 0;
            }
		}
	}
	printf("%d",l);
	return 0;
}
