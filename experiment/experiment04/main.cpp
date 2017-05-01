#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
/*
测试样例：
abaabcacabaabcac
abaabcac
2

aaaaaaaaa
aa
8

abcdefg
cd
*/
/**
得到next数组
**/
void get_next(char *t, int next[])
{
    int j, k;
    next[0] = k = -1;
    j = 0;
    while(t[j])
    {
        if(k == -1 || t[j] == t[k])
            next[++j] = ++k;
        else
            k = next[k];

    }
}
/*
得到nextval数组
*/
void get_nextval(char *t, int nextval[])
{
    int j, k;
    nextval[0] = k = -1;
    j = 0;
    while(t[j])
    {
        if(k == -1 || t[j] == t[k])
        {
            if(t[++k] == t[++j])
                nextval[j] = nextval[k];
            else
                nextval[j] = k;
        }
        else
            k = nextval[k];

    }
}
int getLength(char *a)  //得到一个字符串的长度
{
    int length = 0;
    while(a[length])
    {
        length++;
    }
    return length;
}

/**
累计子字符串在文件中出现的次数，指针不需要回溯
**/
int cnt_kmp(FILE *fp, char t[], int nextval[], int length)
{
    int k0 = nextval[length];
    int c = 0;
    int ch = getc(fp);
    int j = 0;
    while(1)
    {
        while(ch != -1 && (j == -1 || t[j]))
        {
            if(j == -1 || ch == t[j])
            {
                ch = fgetc(fp);j++;
            }else{
                j = nextval[j];
            }

        }
        if(!t[j])
        {
            j = k0;
         //   ch = getc(fp);老师代码出现这句，错误
            c++;
        }
        if(ch == -1)break;
    }
    return c;
}
int main()
{
    char filename[100], t[100];
    int nextval[100];
    int length;
    cout << "请输入文件名:";
    cin >> filename;
    FILE *fp;
    while(1)
    {
        fp = fopen(filename, "r");
        if(!fp)
        {
            cout << "不存在此文件，请重新输入:";
            cin >> filename;
        }
        else
            break;
    }

    cout << "请输入子串:";
    cin >> t;
    length = getLength(t);
    get_nextval(t, nextval);
    cout << "next数组(包括最后\\0位置的值):" << endl;
    for(int i = 0; i <= length; i++)
        cout << nextval[i] << "  ";
    cout << endl;
    cout << "子字符串在文件中成功匹配的次数：" << cnt_kmp(fp, t, nextval, length) << endl;
    return 0;
}
