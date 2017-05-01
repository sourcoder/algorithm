#include <iostream>
#include <stack>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//2 3 n  5 * 3 4 - / +  12+(-3)*5/(3-4) = 17
//�ж��ַ�c�Ƿ�Ϊһ��������������򷵻�true�����򷵻�false
bool isOperator(char c)
{
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}
/**
����a, bΪ�������� cΪ��������
*/
int compute(int a, int b, char c) //����acb��ֵ,����a=1, b=2, c ='-' �����a-b=1-2=-1
{
    switch(c)
    {
        case '+':
            return a + b;
            break;
        case '-':
            return a - b;
            break;
        case '*':
            return a * b;
            break;
        case '/':
            return a / b;
            break;
    }
}

int compute_RPM()//�����׺���ʽ������
{
 //   ifstream cin("input.txt");
    FILE *fp = fopen("input.txt", "r");
    stack <int> s;
    int a, b;
    int result = 0;
    char c;
 //   cin >> noskipws >> c;
    c = fgetc(fp);
    while(c !=EOF)
    {
        if(isOperator(c))   //����������
        {
            b = s.top();    //����ջ��������Ԫ�أ�����������
            s.pop();
            a = s.top();
            s.pop();
            if(c == '/' && b == 0)  //�Ƿ���0����
            {
                cout << "Error!Divided bu zero!";
                exit(0);
            }
            result = compute(a, b, c);
            s.push(result);         //��������ջ
        }
        else if(c == 'n')   //һԪ�����Ϊ����
        {
            a = s.top();    //ȡջ��Ԫ��
            s.pop();        //����
            s.push(-a);     //��ջ
        }else if(isdigit(c))//cΪ���ֲ�����
        {
            result = c - '0';
            c = fgetc(fp);
            while(isdigit(c))
            {
                result = result * 10 + (c - '0');
                c = fgetc(fp);
            }
            s.push(result);
            continue;
        }
        c = fgetc(fp);
    }
    return s.top();
}
int main()
{
    cout << "The computing res is:";
    cout << compute_RPM() << endl;
    return 0;
}
