#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
char s[100];    //输入字符串
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
}*BiTree, BiNode;
ofstream os("output.txt");
void preOrder(char *s, int root)
{
    if(s[root])
    {
         os << s[root];
        if(s[root*2+1] != '\0')
            preOrder(s, root*2+1);
        if(s[root*2+2] != '\0')
            preOrder(s, root*2+2);
    }
}

void inOrder(char *s, int root)
{
    if(s[root])
    {
        if(s[root*2+1] != '\0')
            inOrder(s, root*2+1);
        os << s[root];
        if(s[root*2+2] != '\0')
            inOrder(s, root*2+2);
    }
}

void lasOrder(char *s, int root)
{
    if(s[root])
    {
        if(s[root*2+1] != '\0')
            lasOrder(s, root*2+1);
        if(s[root*2+2] != '\0')
            lasOrder(s, root*2+2);
        os << s[root];
    }
}

void array_to_bitree(BiTree *root, char *a, int n)
{

    for(int i = 0; i < n; i++)
        root[i] = new BiNode();
    for(int i = 0; i <= n-1; i++)
    {
        root[i]->data = a[i];
        if(i*2 + 1 <= n-1)
            root[i]->lchild = root[i*2 + 1];
        else
            root[i]->lchild = root[i]->rchild = NULL;
        if(i*2 + 2 <= n-1)
            root[i]->rchild = root[i*2 + 2];
        else
            root[i]->rchild = NULL;
    }
}

void bi_preOrder(BiTree root)
{
    if(root)
    {
        os << root->data;
        bi_preOrder(root->lchild);
        bi_preOrder(root->rchild);
    }
}
void bi_inOrder(BiTree root)
{
    if(root)
    {
        bi_inOrder(root->lchild);
        os << root->data;
        bi_inOrder(root->rchild);
    }
}
void bi_lasOrder(BiTree root)
{
    if(root)
    {
        bi_lasOrder(root->lchild);
        bi_lasOrder(root->rchild);
        os << root->data;
    }
}
int main()
{
    ifstream cin("input.txt");
    while(cin >> s)
    {
    //cin >> s;
         //一位数组直接遍历
        os << "一维数组遍历结果：" << endl;
        os << "前序遍历：";
        preOrder(s, 0);os << endl;
        os << "中序遍历：";
        inOrder(s, 0);os << endl;
        os << "后序遍历：";
        lasOrder(s, 0);os << endl;
        os << "一维数组转换二叉链表遍历结果：" << endl;
        BiTree bt[100];//二叉链表存储结构
        array_to_bitree(bt, s, strlen(s));
        os << "前序遍历：";
        bi_preOrder(*bt);os << endl;
        os << "中序遍历：";
        bi_inOrder(*bt);os << endl;
        os << "后序遍历：";
        bi_lasOrder(*bt);os << endl;
        os << endl;
    }
    return 0;
}


/*//实验报告代码
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
char s[100];    //输入字符串
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
}*BiTree, BiNode;
void preOrder(char *s, int root)
{
    if(s[root])
    {
         cout << s[root];
        if(s[root*2+1] != '\0')
            preOrder(s, root*2+1);
        if(s[root*2+2] != '\0')
            preOrder(s, root*2+2);
    }
}

void inOrder(char *s, int root)
{
    if(s[root])
    {
        if(s[root*2+1] != '\0')
            inOrder(s, root*2+1);
        cout << s[root];
        if(s[root*2+2] != '\0')
            inOrder(s, root*2+2);
    }
}
void array_to_bitree(BiTree *root, char *a, int n)
{

    for(int i = 0; i < n; i++)
        root[i] = new BiNode();
    for(int i = 0; i <= n-1; i++)
    {
        root[i]->data = a[i];
        if(i*2 + 1 <= n-1)
            root[i]->lchild = root[i*2 + 1];
        else
            root[i]->lchild = root[i]->rchild = NULL;
        if(i*2 + 2 <= n-1)
            root[i]->rchild = root[i*2 + 2];
        else
            root[i]->rchild = NULL;
    }
}
void lasOrder(char *s, int root)
{
    if(s[root])
    {
        if(s[root*2+1] != '\0')
            lasOrder(s, root*2+1);
        if(s[root*2+2] != '\0')
            lasOrder(s, root*2+2);
        cout << s[root];
    }
}

void bi_preOrder(BiTree root)
{
    if(root)
    {
        cout << root->data;
        bi_preOrder(root->lchild);
        bi_preOrder(root->rchild);
    }
}
void bi_inOrder(BiTree root)
{
    if(root)
    {
        bi_inOrder(root->lchild);
        cout << root->data;
        bi_inOrder(root->rchild);
    }
}
void bi_lasOrder(BiTree root)
{
    if(root)
    {
        bi_lasOrder(root->lchild);
        bi_lasOrder(root->rchild);
        cout << root->data;
    }
}
int main()
{
    ifstream cin("input.txt");
    //while(cin >> s)
   // {
   cin >> s;
         //一位数组直接遍历
        cout << "一位数组遍历结果：" << endl;
        cout << "前序遍历：";
        preOrder(s, 0);cout << endl;
        cout << "中序遍历：";
        inOrder(s, 0);cout << endl;
        cout << "后序遍历：";
        lasOrder(s, 0);cout << endl;
        cout << "一位数组转换二叉链表遍历结果：" << endl;
        BiTree bt[100];//二叉链表存储结构
       // cout << strlen(s) << endl;
        array_to_bitree(bt, s, strlen(s));
        cout << "前序遍历：";
        bi_preOrder(*bt);cout << endl;
        cout << "中序遍历：";
        bi_inOrder(*bt);cout << endl;
        cout << "后序遍历：";
        bi_lasOrder(*bt);cout << endl;
  //  }
    return 0;
}

*/
