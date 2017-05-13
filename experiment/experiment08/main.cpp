#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
using namespace std;
#define N 100
typedef struct
{
    int parent, lchild, rchild; //双亲下标，左儿子，又儿子
    double w;                   //节点权值
}HF_BTNode;                     //码树节点类型

typedef struct
{
    int n;                  //实际符号数
    char s[N];              //符号表
    double weight[N];       //符号权重表
    char code[N][N+1];      //编码表
    HF_BTNode hf[2*N-1];    //码树
}HFT;
typedef struct
{
    char c;                 //实际字符
    int cnt;                //出现的次数
    int length = 0;         //编码后的长度
}CH;                        //单个字符
CH ch[N];
void analyzeInput(HFT &a)//对输入的字符串进行分析处理
{
    int n = 0, len = strlen(a.s), cur = 0;
    //扫描字符串，统计单词出现的次数
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
    //赋值到Huffman树
    a.n = cur;
    for(int i = 0; i < cur; i++)
        a.weight[i] = ch[i].cnt;
}
void createHF(HFT &a)//创建Huffman树
{
    int m = 2*a.n - 1;
    for(int i = 0; i < m; i++)
        a.hf[i].parent = a.hf[i].lchild = a.hf[i].rchild = -1;
    for(int i = 0; i < a.n; i++)
        a.hf[i].w = a.weight[i];
    //构造Huffman二叉树，生成a.hf[n..m-1]
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
    //以下生成code数组
    for(int i = 0; i < a.n; i++)
    {
        int j = i;
        char *q, *p = a.code[i];//j从第i个叶子出发上溯至根节点
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
        p--;//字符串逆序
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
void encode(HFT &a, unsigned char *receive) //通过Huffman编码规则将输入的字符串编码，压缩按位存储
{
    int cur = 7, re = 0;
    for(int i = 0; i < strlen(a.s); i++)    //朴素算法扫描整个字符串
    {

        for(int j = 0; j < a.n; j++)        //每个字符找到相应的编码
        {
            if(a.s[i] == ch[j].c)
            {
                for(int k = 0; k < ch[j].length; cur--, k++)//按编码进行位赋值
                {
                    if(cur == -1)
                    {
                        re++;
                        cur = 7;
                    }
                    if(a.code[j][k] == '1')
                        receive[re] |= (1 << cur);  //对位置cur赋值为1
                    else
                        receive[re] &= ~(1 << cur); //对位置cur赋值为0
                }
                break;
            }
        }
    }
}
void decode(HFT &a, unsigned char receive[], char decoded[], int total)//译码
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
             m = (receive[i/8] & (1 << cur)) >> cur;//不停地取二进制位，得到Huffman编码
             i++;
             os << m;//将编码输出到文件
             cur--;
             if(m == 1)
                k = a.hf[k].lchild;
             else
                k = a.hf[k].rchild;
        }
        if(k < a.n)
            decoded[j++] = ch[k].c;//输出一个符号，若k < a.n，则k指向一个叶子节点
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
    int total;                  //字符的总个数
    double bitrate = 0.0;       //压缩率
    for(int i = 0; i < a.n; i++)
        bitrate += ch[i].cnt * ch[i].length;
    total = (int)bitrate;
    cout << bitrate/(double)strlen(a.s)/((double)log(a.n)/(double)log(2)) << endl;
    encode(a,receive);                 //编码
    decode(a, receive, decoded, total);//译码
    ofstream cout("output1.txt");
    cout << decoded << endl;
    return 0;
}
