#include <iostream>
using namespace std;
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
}*BiT,BitNode;
/*
char *res backToFront(char &in, char &bk)
{

}
*/
BiT crtBT1(char *pr, int &i, char *mi, int u, int v)
{
    BiT bt;
    int k;
    if(u < v)
        return NULL;
    bt = new BitNode;
    bt->data = pr[i++];
    for(k = u; k <= v; k++)
        if(mi[k] == bt->data)
        break;
    bt->lchild = crtBT1(pr, i, mi, u, k-1);
    bt->rchild = crtBT1(pr, i, mi, k+1, v);
}
void preOrderTraverse(BiT bt)
{
    if(bt)
    {
        cout << bt->data;
        preOrderTraverse(bt->lchild);
        preOrderTraverse(bt->rchild);

    }
}
int mian()
{
    char *a = "ABCDEFG";
    char *b = "CBEDAFG";
 //   char *c = "CEDBGFA";
    int i = 0;
    BiT root;
    root = crtBT1(a, i, b, 0, 6);
    preOrderTraverse(root);
    return 0;
}
