/*
    顺序表的链式存储结构
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
#define CreateNode(p) p=(Polyn)malloc(sizeof(PNode))
#define DeleteNode(p) free((void *)(p))
//结构体的定义
typedef struct Polynode
{

    int c;                   //系数
    int e;                   //指数
    struct Polynode *next;       //指针
}PNode, *Polyn;

ifstream is("input.txt");   //从文件input.txt读取数据
ofstream os("output.txt");  //从文件output.txt写入程序运行结果数据

//按照先入先出发创建顺序表，即先输入的数据存储在前面
Polyn create()
{

    Polyn last, p;
    Polyn h = new PNode; h->next = NULL;
    last = h;
    int c, e;
    while(is >> c >> e && c!= 0)
    {
        p = new PNode;
        p->c = c;
        p->e = e;
        last->next = p;
        last = p;
    }
    last->next = NULL;
    return h;
}
//打印出多项式
void print(Polyn h)
{
    Polyn p = h->next;
    while(p)
    {
        os << p->c << "  " << p->e << endl;
        p = p->next;
    }
}

//按照指数升序排列，默认输入数据没有相同的指数
void upsort(Polyn h)
{
    Polyn q, s, pr, p;
    q = h->next;
    h->next = NULL; //断开头结点
    while(q)
    {
        s = q;q = q->next;  //摘下节点
        pr = h; p = h->next;    //初始化主从动指针
        while(p && p->e < s->e )
        {
            pr = p;
            p = p->next;
        }
        //following insert node *s
        pr->next = s;
        s->next = p;
    }
}
/*
两个多项式相加算法类似于两个升序表的归并算法；
以下算法考虑利用两个源多项式结点生成和式的结点；
算法要求两个源多项式结点按指数e升序连接；
算法结束后，两个源多项式成为空链表。
*/
Polyn add(Polyn h1, Polyn h2)//函数返回和式头指针
{
    Polyn p1, p2, p3, h, p;
    p1 = h1->next;  p2 = h2->next;
    CreateNode(h);  p3 = h;//h为和式附加头结点指针
    while(p1 && p2)
    {
        if(p1->e < p2->e)
        {
            p = p1;
            p1 = p1->next;
        }else if(p2->e < p1->e)
        {
            p = p2;
            p2 = p2->next;
        }else//p1->e==p2->e为真时
        {
            p1->c = p1->c + p2->c;
            if( p1->c == 0)//p1->c==0应删除两个结点
            {
                p = p1; p1 = p1->next;  DeleteNode(p);
                p = p2; p2 = p2->next;  DeleteNode(p);
                continue;
            }
            p = p2; p2 = p2->next;  DeleteNode(p);
            p = p1; p1 = p1->next;
        }
        p3->next = p; p3 = p;//插入*p结点至和式末尾
    }
    if(p1)
        p3->next = p1;
    else if(p2)
        p3->next = p2;
    else
        p2->next = NULL;
    return h;
}

/*
//原理性算法如下
R(x)=0;
for(i=0; i<n; i++)
{ T(x)=P(x)cixdi; //T(x)结点数与P(x)相同
R(x)=R(x)+T(x); //利用加法算法
}
*/
Polyn mul(Polyn hp, Polyn hq)
{
    Polyn hr, ht, p, q, pt;
    CreateNode(hr); hr->next = NULL;//R(x)=0;
    CreateNode(ht); ht->next = NULL;//T(x)=0;
    q = hq->next;
    while(q)//实现for(i=0; i<n; i++)
    {
        pt = ht;
        p = hp->next;
        while(p)
        {
            //以下实现T(x)=P(x)cixdi;
            CreateNode(pt->next);
            pt = pt->next;
            pt->c = p->c * q->c;
            pt->e = p->e + q->e;
            p = p->next;
        }
        pt->next = NULL;
        q = q->next;
        //以下实现R(x)=R(x)+T(x)
        p = add(hr, ht);
        DeleteNode(hr);
        hr = p;
    }
    DeleteNode(ht);
    return hr;
}
int main()
{

    int T = 3;  //测试样例次数
    while(T--)
    {
        Polyn hp, hq, hmul;
        hp = create();
        hq = create();
        upsort(hp);
        upsort(hq);
        os << "case" << 3-T << " :"<< endl;
        os << "hp排序后：" << endl;
        print(hp);
        os << "hp排序后：" << endl;
        print(hq);
        hmul = mul(hp, hq);
        os << "hp*hq的结果:" << endl;
        print(hmul);
    }
    return 0;
}
