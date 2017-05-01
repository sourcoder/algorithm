#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
//单个人的信息
typedef struct person
{
    char name[10];    //排队人的名字
}Person;

typedef struct node
{
    Person *elem;
    int n;  //队列容量
    int f;  //队头指针
    int r;  //队尾指针
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
        return 0;   //队满，入队失败
    q.r = (q.r + 1) % q.n;
    q.elem[q.r] = e;
    return 1; //入队成功
}

int delQueue(SqQueue &q, Person &e)
{
    if(q.r == q.f)
        return 0;   //队列为空，出队失败
    q.f = (q.f + 1) % q.n;
    e = q.elem[q.f];
    return 1;   //出队成功返回1
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
    cout << "1.排队" << endl;
    cout << "2.售票" << endl;
    cout << "3.查看队列" << endl;
    cout << "4.结束" << endl;
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
                if(delQueue(q, p)) //删除成功
                {
                    cout << "name: " << p.name << endl;
                    cout << "ticket success! press any key to continue......" ;
                }
                else    //队列为空
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
