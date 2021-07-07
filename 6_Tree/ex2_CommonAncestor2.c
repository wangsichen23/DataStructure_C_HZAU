#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 100

char SearchCA(char *Pre,char *In)
{
    int i,j;
    char ca,temp='0';
    for(i=0;i<strlen(Pre);i++)
    {
        ca=Pre[i];
        for(j=0;j<strlen(In);j++)
            if(ca==In[j])
                temp=ca;
    }
    ca=temp;
    return ca;
}

int main()
{
    int i,j,k=0,length;
    char PreOrderPut[MAXSIZE],InOrderPut[MAXSIZE];
    char Pre[MAXSIZE],In[MAXSIZE],Child[2];
    char Child1,Child2,ca;

    scanf("%s",PreOrderPut);
    scanf("%s",InOrderPut);
    scanf("%s",Child);

    Child1=Child[0];
    Child2=Child[1];

    length=strlen(PreOrderPut);

    for(i=0;i<length;i++)
    {
        if(PreOrderPut[i]!=Child1)
            Pre[i]=PreOrderPut[i];
        else
            break;
    }

    for(j=0;j<length;j++)
    {
        if(InOrderPut[j]==Child1)
            break;
    }
    for(i=j+1;i<length;i++)
    {
        if(InOrderPut[i]!=Child2)
        {
            In[k]=InOrderPut[i];
            k++;
        }
        else
            break;
    }

    ca=SearchCA(Pre,In);
    if(ca=='0')
        printf("NULL");
    else
        printf("%c",ca);

    return 0;
}
