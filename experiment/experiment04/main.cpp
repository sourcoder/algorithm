#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
/*
����������
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
�õ�next����
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
�õ�nextval����
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
int getLength(char *a)  //�õ�һ���ַ����ĳ���
{
    int length = 0;
    while(a[length])
    {
        length++;
    }
    return length;
}

/**
�ۼ����ַ������ļ��г��ֵĴ�����ָ�벻��Ҫ����
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
         //   ch = getc(fp);��ʦ���������䣬����
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
    cout << "�������ļ���:";
    cin >> filename;
    FILE *fp;
    while(1)
    {
        fp = fopen(filename, "r");
        if(!fp)
        {
            cout << "�����ڴ��ļ�������������:";
            cin >> filename;
        }
        else
            break;
    }

    cout << "�������Ӵ�:";
    cin >> t;
    length = getLength(t);
    get_nextval(t, nextval);
    cout << "next����(�������\\0λ�õ�ֵ):" << endl;
    for(int i = 0; i <= length; i++)
        cout << nextval[i] << "  ";
    cout << endl;
    cout << "���ַ������ļ��гɹ�ƥ��Ĵ�����" << cnt_kmp(fp, t, nextval, length) << endl;
    return 0;
}
