#include<stdio.h>
#include<math.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

#define Stack_Size 50

typedef struct
{
    char elem[Stack_Size];
    int top;
}SeqStack;

typedef struct
{
    float elem[Stack_Size];
    int top;
}SeqStackFloat;

void InitStack(SeqStack *S)
{
    S->top=-1;
}

void InitStackFloat(SeqStackFloat *S)
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

int PushFloat(SeqStackFloat *S,float x)
{
    if(S->top==Stack_Size-1)
        return(FALSE);
    S->top++;
    S->elem[S->top]=x;
    return(TRUE);
}

char Pop(SeqStack *S,char *x)
{
    if(S->top==-1)
        return(FALSE);
    else
    {
        *x=S->elem[S->top];
        S->top--;
        return(*x);
    }
}

float PopFloat(SeqStackFloat *S)
{
    float x;
    if(S->top==-1)
        return(FALSE);
    else
    {
        x=S->elem[S->top];
        S->top--;
        return(x);
    }
}

char GetTop(SeqStack *S)
{
    if(S->top==-1)
        return(FALSE);
    else
        return(S->elem[S->top]);
}

float GetTopFloat(SeqStackFloat *S)
{
    if(S->top==-1)
        return(FALSE);
    else
        return(S->elem[S->top]);
}

char Compare(char m,char n)
{
	if(m==')')
	{
		if(n=='(')
            return '=';
		else
            return '<';
	}
	else if(m=='('||n=='(')
        return '>';
	else if(m=='#')
	{
		if(n=='#')
            return '=';
		else
            return '<';
	}
	else if(m=='*'||m=='/')
	{
		if(n=='*'||n=='/')
            return '<';
		else
            return '>';
	}
	else if(m=='+'||m=='-')
	{
		if(n=='#')
            return '>';
		else
            return '<';
	}
	return 0;
}

float Execute(float m,char op,float n)
{
	if(op=='+')
        return m+n;
	else if(op=='-')
        return m-n;
	else if(op=='*')
        return m*n;
	else if(op=='/')
        return m/n;
	else
        return FALSE;
}

float ExpEvaluation()
{
    SeqStack OPTR;
    SeqStackFloat OVS;
    InitStack(&OPTR);
    InitStackFloat(&OVS);

    char ch,op='+';
    float n,v,a,b;

    Push(&OPTR,'#');
    ch=getchar();

    while(ch!='#'||GetTop(&OPTR)!='#')
    {
        if(ch>='0'&&ch<='9')
        {
            n=ch-'0';
            //PushFloat(&OVS,n);
            ch=getchar();
            while(ch>='0'&&ch<='9')
            {
                //n=PopFloat(&OVS);
                n=n*10+ch-'0';
                //PushFloat(&OVS,n);
                ch=getchar();
            }
            if(ch == '.')
            {
                ch=getchar();
                if(ch>='0'&&ch<='9')
                {
                    //n=PopFloat(&OVS);
                    n=n+0.1*(ch-'0');
                    //PushFloat(&OVS,n);
                    ch=getchar();
                    if(ch>='0'&&ch<='9')
                    {
                        //n=PopFloat(&OVS);
                        n=n+0.01*(ch-'0');
                        //PushFloat(&OVS,n);
                        ch=getchar();
                    }
                }
            }
            PushFloat(&OVS,n);
        }
        else
            switch(Compare(ch,GetTop(&OPTR)))
            {
                case '>':
                    Push(&OPTR,ch);
                    ch=getchar();
                    break;
                case '=':
                    Pop(&OPTR,&op);
                    ch=getchar();
                    break;
                case '<':
                    Pop(&OPTR,&op);
                    b=PopFloat(&OVS);
                    a=PopFloat(&OVS);
                    v=Execute(a,op,b);
                    PushFloat(&OVS,v);
                    break;
            }
    }
    v=PopFloat(&OVS);
    return v;
}

int main()
{
    printf("%.2f",ExpEvaluation());
    return 0;
}
