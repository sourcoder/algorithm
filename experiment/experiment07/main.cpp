/*
设二叉树结点数据域为字符类型，从键盘输入先序递归遍历字符序列（用#字符表示NULL指针域）
建立二叉链表存储结构，然后实现中序线索化。基于中序穿线二叉树存储结构定义first,next,last,
previous四个函数并实现中序线索二叉树中序遍历（正序与逆序）非递归算法，输出遍历结果。
*/

#include <iostream>
#include <fstream>
using namespace std;

enum PT {LINK, THREAD};//定义指针域类型
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
    enum PT ltag, rtag;
}*SBiT, SBiT_Node;

ifstream is("input.txt");
//创建一颗二叉树
SBiT create()
{
    char c;
    is >> c;
    if('#' == c)
        return NULL;
    SBiT bt = new SBiT_Node();
    bt->data = c;
    bt->lchild = create();
    bt->rchild = create();
    return bt;
}
//中序线索化，bt为主扫描指针，pre始终指向前驱节点
void midThreading(SBiT bt, SBiT &pre)
{
    if(bt)
    {
        midThreading(bt->lchild, pre);
        if(pre)
        {
            if(pre->rchild)
                pre->rtag = LINK;
            else
            {
                pre->rtag = THREAD;
                pre->rchild = bt;
            }
        }

        if(bt->lchild)
            bt->ltag = LINK;
        else
        {
            bt->ltag = THREAD;
            bt->lchild = pre;
        }
        pre = bt;
        midThreading(bt->rchild, pre);
    }
}
//求中序遍历第一访问节点
SBiT first(SBiT p)
{
    while(p&&p->ltag == LINK)
        p = p->lchild;
    return p;
}
//求中序遍历某节点的后继
SBiT next(SBiT p)
{
    if(p->rtag == THREAD)
        return p->rchild;
    return first(p->rchild);

}
//中序遍历,非递归算法
void midtravel(SBiT root)
{
    SBiT p = first(root);
    while(p)
    {
        cout << p->data ;
        p = next(p);
    }
}
//最后一个元素
SBiT last(SBiT p)
{
    while(p && p->rtag == LINK)
        p = p->rchild;
    return p;
}
//找到前驱节点
SBiT previous(SBiT p)
{
    if(p->ltag == THREAD)
        return p->lchild;
    return last(p->lchild);
}
void midtravel2(SBiT root)
{
    SBiT p = last(root);
    while(p)
    {
        cout << p->data;
        p = previous(p);
    }
}
int main()
{
    SBiT root = create(),pre = NULL;;
    midThreading(root, pre);
    pre->rtag = THREAD;
    midtravel(root);
    cout << endl;
    midtravel2(root);
    return 0;
}
