#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
using namespace std;

typedef struct Node{
    char data;
    struct Node * LChild;
    struct Node * RChild;
}BiTNode, * BiTree;

BiTree create(char * pre,char * in,int length){//前序和中序遍历建树
    if(length==0) return NULL;
    BiTNode * node = (BiTNode *)malloc(sizeof(BiTNode));
    node->data = *pre;
    int i=0;
    for(;i<length;++i)
        if(*pre==*(in+i))
            break;
    node->LChild = create(pre+1,in,i);
    node->RChild = create(pre+i+1,in+i+1,length-i-1);
    return node;
}

BiTree getLCA(BiTree head,char p,char q){//求二叉树结点的共同祖先
    if(head==NULL)
        return NULL;
    if(head->data==p || head->data==q)
        return head;

    BiTree left = getLCA(head->LChild,p,q); //在左子树中查找目标节点

    BiTree right = getLCA(head->RChild,p,q); //在右子树中查找目标节点s

    if(left!=NULL && right!=NULL)
        return head;
    else if(left!=NULL)
        return left;
    else
        return right;
}

int main()
{
    BiTree t;
    char a[100],b[100];
    cin >> a >> b;
    t = create(a,b,strlen(a));

    char c,d;
    cin >> c >> d;
    BiTNode * x = getLCA(t,c,d);
    if(x==NULL)
        cout << "NULL" << endl;
    else cout << x->data << endl;
    return 0;
}
