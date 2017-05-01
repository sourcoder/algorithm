/*
    ˳������ʽ�洢�ṹ
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
#define CreateNode(p) p=(Polyn)malloc(sizeof(PNode))
#define DeleteNode(p) free((void *)(p))
//�ṹ��Ķ���
typedef struct Polynode
{

    int c;                   //ϵ��
    int e;                   //ָ��
    struct Polynode *next;       //ָ��
}PNode, *Polyn;

ifstream is("input.txt");   //���ļ�input.txt��ȡ����
ofstream os("output.txt");  //���ļ�output.txtд��������н������

//���������ȳ�������˳���������������ݴ洢��ǰ��
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
//��ӡ������ʽ
void print(Polyn h)
{
    Polyn p = h->next;
    while(p)
    {
        os << p->c << "  " << p->e << endl;
        p = p->next;
    }
}

//����ָ���������У�Ĭ����������û����ͬ��ָ��
void upsort(Polyn h)
{
    Polyn q, s, pr, p;
    q = h->next;
    h->next = NULL; //�Ͽ�ͷ���
    while(q)
    {
        s = q;q = q->next;  //ժ�½ڵ�
        pr = h; p = h->next;    //��ʼ�����Ӷ�ָ��
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
��������ʽ����㷨���������������Ĺ鲢�㷨��
�����㷨������������Դ����ʽ������ɺ�ʽ�Ľ�㣻
�㷨Ҫ������Դ����ʽ��㰴ָ��e�������ӣ�
�㷨����������Դ����ʽ��Ϊ������
*/
Polyn add(Polyn h1, Polyn h2)//�������غ�ʽͷָ��
{
    Polyn p1, p2, p3, h, p;
    p1 = h1->next;  p2 = h2->next;
    CreateNode(h);  p3 = h;//hΪ��ʽ����ͷ���ָ��
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
        }else//p1->e==p2->eΪ��ʱ
        {
            p1->c = p1->c + p2->c;
            if( p1->c == 0)//p1->c==0Ӧɾ���������
            {
                p = p1; p1 = p1->next;  DeleteNode(p);
                p = p2; p2 = p2->next;  DeleteNode(p);
                continue;
            }
            p = p2; p2 = p2->next;  DeleteNode(p);
            p = p1; p1 = p1->next;
        }
        p3->next = p; p3 = p;//����*p�������ʽĩβ
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
//ԭ�����㷨����
R(x)=0;
for(i=0; i<n; i++)
{ T(x)=P(x)cixdi; //T(x)�������P(x)��ͬ
R(x)=R(x)+T(x); //���üӷ��㷨
}
*/
Polyn mul(Polyn hp, Polyn hq)
{
    Polyn hr, ht, p, q, pt;
    CreateNode(hr); hr->next = NULL;//R(x)=0;
    CreateNode(ht); ht->next = NULL;//T(x)=0;
    q = hq->next;
    while(q)//ʵ��for(i=0; i<n; i++)
    {
        pt = ht;
        p = hp->next;
        while(p)
        {
            //����ʵ��T(x)=P(x)cixdi;
            CreateNode(pt->next);
            pt = pt->next;
            pt->c = p->c * q->c;
            pt->e = p->e + q->e;
            p = p->next;
        }
        pt->next = NULL;
        q = q->next;
        //����ʵ��R(x)=R(x)+T(x)
        p = add(hr, ht);
        DeleteNode(hr);
        hr = p;
    }
    DeleteNode(ht);
    return hr;
}
int main()
{

    int T = 3;  //������������
    while(T--)
    {
        Polyn hp, hq, hmul;
        hp = create();
        hq = create();
        upsort(hp);
        upsort(hq);
        os << "case" << 3-T << " :"<< endl;
        os << "hp�����" << endl;
        print(hp);
        os << "hp�����" << endl;
        print(hq);
        hmul = mul(hp, hq);
        os << "hp*hq�Ľ��:" << endl;
        print(hmul);
    }
    return 0;
}
