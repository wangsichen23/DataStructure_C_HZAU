/*
【问题描述】
给定两个字符串，求出它们两个最长的相同子字符串的长度。
最长公共子串(Longest Common Substring)是一个非常经典的面试题目，在实际的程序中也有很高的实用价值。同学们不应该单单只是写出该问题的基本解决代码而已，关键还是享受把算法一步步的优化，让时间和空间复杂度一步步的减少的惊喜。

【输入形式】
两个字符串

【输出形式】
最长的公共子串，若没有则输出“no”

【样例输入】
acbcbcef
abcbced

【样例输出】
bcbce

【温馨提示】
问题的关键不在于提交代码并通过测试数据，而是你是否真正掌握了所有求解的算法。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

#define MAXLEN 100

typedef struct
{
    char ch[MAXLEN];
    int len;
}SString;

void createstring(SString *s)
{
	int i,j;
	char c[MAXLEN];
	fgets(c, MAXLEN, stdin);
	j=strlen(c);
	for(i=0;i<j;i++)
		s->ch[i]=c[i];
	s->len=j;
}

void output(SString *s)
{
	int i;
	for (i=0;i<s->len;i++)
		printf("%c",s->ch[i]);
}

int SubString(SString *sub, SString s, int pos, int len)
/*将串s中下标pos起len个字符复制到sub中*/
{
	int i;
	if (pos<0 || pos>s.len || len<1 || len>s.len-pos)
	{
		sub->len=0;
		return(0);
	}
	else
	{
		for (i=0; i<len; i++)
			sub->ch[i]=s.ch[i+pos];
		sub->len=len;
		return(1);
	}
}

int StrIndex(SString s,SString t)
/*求从主串s的下标pos起，串t第一次出现的位置，成功返回位置序号，不成功返回-1*/
{
	int i, j, start;
	if (t.len==0)
		return(0);   /* 模式串为空串时，是任意串的匹配串 */
	start=0;
	i=start;
	j=0;  /* 主串从pos开始，模式串从头（0）开始 */
	while (i<s.len && j<t.len)
		if (s.ch[i]==t.ch[j])
		{
			i++;
			j++;
		}   /* 当前对应字符相等时推进 */
		else
		{
			start++;        /* 当前对应字符不等时回溯 */
			i=start;
			j=0;   /* 主串从start+1开始，模式串从头（0）开始*/
		}
		if (j>=t.len)
			return(start);    /* 匹配成功时，返回匹配起始位置 */
		else
			return(-1);    /* 匹配不成功时，返回-1 */
}

int LCS(SString s1,SString s2)
{
    int i,j,k,l,flag=0;
    SString s;

    if(s1.len >= s2.len)
    {
        l=s2.len;
        for(j=l;j>0;j--)
            for(i=0;i<l-j;i++)
            {
                SubString(&s,s2,i,j);
                k=StrIndex(s1,s);
                if(k!=-1)
                {
                    output(&s);
                    flag=1;
                    return(flag);
                }
            }
    }
    else
    {
        l=s1.len;
        for(j=l;j>0;j--)
            for(i=0;i<l-j;i++)
            {
                SubString(&s,s1,i,j);
                k=StrIndex(s2,s);
                if(k!=-1)
                {
                    output(&s);
                    flag=1;
                    return(flag);
                }
            }
    }
    return(flag);
}

int main()
{
    int a;
    SString s1,s2;

	createstring(&s1);
	createstring(&s2);

    a=LCS(s1,s2);
    if(!a)
        printf("no");

    return 0;
}
