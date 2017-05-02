//
//  main.cpp
//  treehm2
//
//  Created by kinredon on 2017/5/2.
//  Copyright © 2017年 kinredon. All rights reserved.
//

#include <iostream>
using namespace std;

typedef struct node
{
    int data;
    struct node *lchild, *rchild;
}*BiTree, BiTNode;

int n = 0, c;
BiTree create()//创建二叉树
{
    scanf("%d", &c);
    if( 0 == c)
    {
        return NULL;
    }
    BiTree bt;
    bt = new BiTNode();
    bt->data = c;
    bt->lchild = create();
    bt->rchild = create();
    return bt;
}
int cmp(int a, int b)
{
    return a>b;
}
//task 01
int diameter(BiTree bt)
{
    if(!bt)
        return 0;
    int dr, dl;
    dl = diameter(bt->lchild);
    dr = diameter(bt->rchild);
    return max(dr, dl) + 1;
}
int mark = 0;
BiTree acester;
void sca(BiTree bt,BiTree q, BiTree p,int &mark)
{
    if(bt)
    {
        if(bt == q)
            mark++;
        if(bt == p)
            mark++;
        sca(bt->lchild, q, p, mark);
        if(mark == 1)
            acester = bt;
        sca(bt->rchild, q, p, mark);
    }
}
int main() {
    BiTree root = create();
    cout << "树的高度" << diameter(root) << endl;
    cout << "最近的公共祖先：" << acester->data << endl;
    return 0;
}
