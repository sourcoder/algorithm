/*
����������������Ϊ�ַ����ͣ��Ӽ�����������ݹ�����ַ����У���#�ַ���ʾNULLָ����
������������洢�ṹ��Ȼ��ʵ�����������������������߶������洢�ṹ����first,next,last,
previous�ĸ�������ʵ����������������������������������򣩷ǵݹ��㷨��������������
*/

#include <iostream>
#include <fstream>
using namespace std;

enum PT {LINK, THREAD};//����ָ��������
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
    enum PT ltag, rtag;
}*SBiT, SBiT_Node;

ifstream is("input.txt");
//����һ�Ŷ�����
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
//������������btΪ��ɨ��ָ�룬preʼ��ָ��ǰ���ڵ�
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
//�����������һ���ʽڵ�
SBiT first(SBiT p)
{
    while(p&&p->ltag == LINK)
        p = p->lchild;
    return p;
}
//���������ĳ�ڵ�ĺ��
SBiT next(SBiT p)
{
    if(p->rtag == THREAD)
        return p->rchild;
    return first(p->rchild);

}
//�������,�ǵݹ��㷨
void midtravel(SBiT root)
{
    SBiT p = first(root);
    while(p)
    {
        cout << p->data ;
        p = next(p);
    }
}
//���һ��Ԫ��
SBiT last(SBiT p)
{
    while(p && p->rtag == LINK)
        p = p->rchild;
    return p;
}
//�ҵ�ǰ���ڵ�
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
