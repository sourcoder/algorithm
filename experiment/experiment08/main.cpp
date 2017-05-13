#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
using namespace std;
#define N 100
typedef struct
{
    int parent, lchild, rchild; //˫���±꣬����ӣ��ֶ���
    double w;                   //�ڵ�Ȩֵ
}HF_BTNode;                     //�����ڵ�����

typedef struct
{
    int n;                  //ʵ�ʷ�����
    char s[N];              //���ű�
    double weight[N];       //����Ȩ�ر�
    char code[N][N+1];      //�����
    HF_BTNode hf[2*N-1];    //����
}HFT;
typedef struct
{
    char c;                 //ʵ���ַ�
    int cnt;                //���ֵĴ���
    int length = 0;         //�����ĳ���
}CH;                        //�����ַ�
CH ch[N];
void analyzeInput(HFT &a)//��������ַ������з�������
{
    int n = 0, len = strlen(a.s), cur = 0;
    //ɨ���ַ�����ͳ�Ƶ��ʳ��ֵĴ���
    for(int i = 0; i < len; i++)
    {
        int flag = 0;
        for(int j = 0; j < cur; j++)
            if(a.s[i] == ch[j].c)
            {
                ch[j].cnt++;
                flag = 1;
            }
        if(flag == 0)
        {
            ch[cur].cnt = 1;
            ch[cur++].c = a.s[i];
        }
    }
    //��ֵ��Huffman��
    a.n = cur;
    for(int i = 0; i < cur; i++)
        a.weight[i] = ch[i].cnt;
}
void createHF(HFT &a)//����Huffman��
{
    int m = 2*a.n - 1;
    for(int i = 0; i < m; i++)
        a.hf[i].parent = a.hf[i].lchild = a.hf[i].rchild = -1;
    for(int i = 0; i < a.n; i++)
        a.hf[i].w = a.weight[i];
    //����Huffman������������a.hf[n..m-1]
    for(int i = a.n; i < m; i++)
    {
        int j, j1, j2;
        for(j1 = 0; j1 < i; j1++)
            if( a.hf[j1].parent == -1)
                break;
        for(j = j1 + 1; j < i; j++)
            if(a.hf[j].parent == -1 && a.hf[j].w < a.hf[j1].w)
                j1 = j;
        a.hf[j1].parent = i;
        a.hf[i].lchild = j1;
        for(j2 = 0; j2 < i; j2++)
            if(a.hf[j2].parent == -1)
                break;
        for(j = j2 + 1; j < i; j++)
            if(a.hf[j].parent == -1 && a.hf[j].w < a.hf[j2].w)
                j2 = j;
        a.hf[j2].parent = i;
        a.hf[i].rchild = j2;
        a.hf[i].w = a.hf[j1].w + a.hf[j2].w;
    }
    //��������code����
    for(int i = 0; i < a.n; i++)
    {
        int j = i;
        char *q, *p = a.code[i];//j�ӵ�i��Ҷ�ӳ������������ڵ�
        while( a.hf[j].parent!= -1)
        {
            int child = j;
            j = a.hf[j].parent;
            if(a.hf[j].lchild == child)
                *p++ = '1';
            else
                *p++ = '0';
            ch[i].length++;
        }
        *p = '\0';
        q = a.code[i];
        p--;//�ַ�������
        char ch;
        while(q < p)
        {
            ch = *q;
            *q = *p;
            *p = ch;
            q++;
            p--;
        }
    }
}
void encode(HFT &a, unsigned char *receive) //ͨ��Huffman�������������ַ������룬ѹ����λ�洢
{
    int cur = 7, re = 0;
    for(int i = 0; i < strlen(a.s); i++)    //�����㷨ɨ�������ַ���
    {

        for(int j = 0; j < a.n; j++)        //ÿ���ַ��ҵ���Ӧ�ı���
        {
            if(a.s[i] == ch[j].c)
            {
                for(int k = 0; k < ch[j].length; cur--, k++)//���������λ��ֵ
                {
                    if(cur == -1)
                    {
                        re++;
                        cur = 7;
                    }
                    if(a.code[j][k] == '1')
                        receive[re] |= (1 << cur);  //��λ��cur��ֵΪ1
                    else
                        receive[re] &= ~(1 << cur); //��λ��cur��ֵΪ0
                }
                break;
            }
        }
    }
}
void decode(HFT &a, unsigned char receive[], char decoded[], int total)//����
{
    ofstream os("output.txt");
    int i =0,  j = 0, cur = 7, m;
    while(i < total)
    {
        int k = 2 * a.n - 2;
        while(k >= a.n && i < total)
        {
             if(cur == -1)
                cur = 7;
             m = (receive[i/8] & (1 << cur)) >> cur;//��ͣ��ȡ������λ���õ�Huffman����
             i++;
             os << m;//������������ļ�
             cur--;
             if(m == 1)
                k = a.hf[k].lchild;
             else
                k = a.hf[k].rchild;
        }
        if(k < a.n)
            decoded[j++] = ch[k].c;//���һ�����ţ���k < a.n����kָ��һ��Ҷ�ӽڵ�
    }
    decoded[j] = '\0';
}
int main()
{
    ifstream cin("input.txt");
    HFT a;
    unsigned char receive[101];
    char decoded[101];
    cin >> a.s;
    analyzeInput(a);
    createHF(a);
    int total;                  //�ַ����ܸ���
    double bitrate = 0.0;       //ѹ����
    for(int i = 0; i < a.n; i++)
        bitrate += ch[i].cnt * ch[i].length;
    total = (int)bitrate;
    cout << bitrate/(double)strlen(a.s)/((double)log(a.n)/(double)log(2)) << endl;
    encode(a,receive);                 //����
    decode(a, receive, decoded, total);//����
    ofstream cout("output1.txt");
    cout << decoded << endl;
    return 0;
}
