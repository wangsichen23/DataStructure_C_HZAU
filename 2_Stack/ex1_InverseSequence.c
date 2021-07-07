/*
【注意】本题务必使用顺序栈或者链式栈的一种来实现，否则不给分。

【问题描述】试写一个算法，识别依次读入的一个以“@”为结束符的字符序列是否为形如 “序列1&序列2”  模式的字符序列。其中序列1和序列2都不含字符 “&”，且序列2是序列1的逆序列。例如，“ a+b&b+a ”是属该模式的字符序列，而 “1+3&3-1”则不是。

【输入形式】
 以@为结尾的一串字符

【输出形式】
 若符合模式则输出字符串长度，否则输出no

【样例输入】
 a+b&b+a@

【样例输出】
 3
*/
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
