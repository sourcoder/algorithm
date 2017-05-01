#include <iostream>
#include <stack>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//2 3 n  5 * 3 4 - / +  12+(-3)*5/(3-4) = 17
//判断字符c是否为一个运算符，若是则返回true，否则返回false
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
参数a, b为操作数， c为操作符，
*/
int compute(int a, int b, char c) //计算acb的值,比如a=1, b=2, c ='-' 则计算a-b=1-2=-1
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

int compute_RPM()//计算后缀表达式主函数
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
        if(isOperator(c))   //如果是运算符
        {
            b = s.top();    //弹出栈顶的两个元素，并计算出结果
            s.pop();
            a = s.top();
            s.pop();
            if(c == '/' && b == 0)  //非法除0操作
            {
                cout << "Error!Divided bu zero!";
                exit(0);
            }
            result = compute(a, b, c);
            s.push(result);         //计算结果入栈
        }
        else if(c == 'n')   //一元运算符为符号
        {
            a = s.top();    //取栈顶元素
            s.pop();        //弹出
            s.push(-a);     //入栈
        }else if(isdigit(c))//c为数字操作符
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
