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
/*����s���±�pos��len���ַ����Ƶ�sub��*/
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
/*�������s���±�pos�𣬴�t��һ�γ��ֵ�λ�ã��ɹ�����λ����ţ����ɹ�����-1*/
{
	int i, j, start;
	if (t.len==0)
		return(0);   /* ģʽ��Ϊ�մ�ʱ�������⴮��ƥ�䴮 */
	start=0;
	i=start;
	j=0;  /* ������pos��ʼ��ģʽ����ͷ��0����ʼ */
	while (i<s.len && j<t.len)
		if (s.ch[i]==t.ch[j])
		{
			i++;
			j++;
		}   /* ��ǰ��Ӧ�ַ����ʱ�ƽ� */
		else
		{
			start++;        /* ��ǰ��Ӧ�ַ�����ʱ���� */
			i=start;
			j=0;   /* ������start+1��ʼ��ģʽ����ͷ��0����ʼ*/
		}
		if (j>=t.len)
			return(start);    /* ƥ��ɹ�ʱ������ƥ����ʼλ�� */
		else
			return(-1);    /* ƥ�䲻�ɹ�ʱ������-1 */
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
