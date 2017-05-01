#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
//�����˵���Ϣ
typedef struct person
{
    char name[10];    //�Ŷ��˵�����
}Person;

typedef struct node
{
    Person *elem;
    int n;  //��������
    int f;  //��ͷָ��
    int r;  //��βָ��
}SqQueue;
void clearQueue(SqQueue &q)
{
    q.r = q.f = -1;

}
void initQueue(SqQueue &q, int n)
{
    q.r = q.f = -1;
    q.n = n + 1;
}
int Empty(SqQueue &q)
{
    return q.f == q.r;
}

int full(SqQueue &q)
{
    return (q.r + 1)%q.n == (q.f + q.n)%q.n;
}

int enQueue(SqQueue &q, Person e)
{
    if((q.r +1)%q.n == (q.f + q.n) % q.n )
        return 0;   //���������ʧ��
    q.r = (q.r + 1) % q.n;
    q.elem[q.r] = e;
    return 1; //��ӳɹ�
}

int delQueue(SqQueue &q, Person &e)
{
    if(q.r == q.f)
        return 0;   //����Ϊ�գ�����ʧ��
    q.f = (q.f + 1) % q.n;
    e = q.elem[q.f];
    return 1;   //���ӳɹ�����1
}

void show(SqQueue &q)
{
    if(Empty(q))
    {
        cout << "Queue is empty!" << endl;
        return;
    }
    int i;
    for(i=q.f + 1; (q.r + q.n)%q.n != (i + q.n)%q.n; i = (i + 1)%q.n)
    {
        cout << "Name:" <<  q.elem[i].name << endl;
    }
    cout << "Name:" <<  q.elem[i].name << endl;
}
void mainMenu()
{
    cout << "1.�Ŷ�" << endl;
    cout << "2.��Ʊ" << endl;
    cout << "3.�鿴����" << endl;
    cout << "4.����" << endl;
}
int main()
{

    SqQueue q ;
    initQueue(q, 3);
    while(1)
    {
        char ch;
        mainMenu();
        ch = getch();
        switch (ch)
        {
            case '1' :
            {
                // string name;
                Person p;
                cout << "Please input your name:" ;
                cin >> p.name;
                if(enQueue(q, p))
                {
                    cout << "Hello " << p.name << endl;
                    cout << "You are successful! press any key to continue......";
                }
                else
                {
                    cout << "queue full! press any key to continue......";
                }
                break;
            }

            case '2':
            {
                Person p;
                if(delQueue(q, p)) //ɾ���ɹ�
                {
                    cout << "name: " << p.name << endl;
                    cout << "ticket success! press any key to continue......" ;
                }
                else    //����Ϊ��
                {
                    cout << "failed! There is no person is waiting! press any key to continue......";
                }
                break;
            }

            case '3':
            {
                show(q);
                cout << " press any key to continue......";
                break;
            }

            case '4':
            {
                exit(0);
                break;
            }

            default:
                cout << "input error, press any key to continue......" << endl;
                break;
        }
        ch = getch();
        system("cls");
    }
    return 0;
}
