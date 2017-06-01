#include <iostream>
#include <vector>
#include <stack>
#include <memory.h>
#include <fstream>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
typedef struct
{
    int to;//�ڵ��±�
    int w;  //Ȩֵ
}Graph;
int main()
{
    ifstream cin("input.txt");
    vector <Graph> G[100];
    double ve[100];//��������
    int from, to, w, n, e;
    cin >> n >> e;//nΪ�ڵ�������eΪ�ߵ�����
    while(e--)//�����ڽӱ�
    {
        cin >> from >> to >> w;//from��㣬to�յ㣬wȨֵ
        Graph g;
        g.to = to; g.w = w;
        G[from].push_back(g);
    }
    int *indegree = new int[n];//ÿ���ڵ���������
    int  cnt;
    stack <int> S, T;
    memset(indegree, 0, n*sizeof(int));
    rep(i, 0, n-1)//init indegree
    {
        for(unsigned j = 0; j < G[i].size(); j++)
        {
            indegree[G[i][j].to]++;
        }
    }
    rep(i, 0, n-1)
        ve[i] = 0;
    rep(i, 0, n-1)
        if(!indegree[i])
        {
            S.push(i);break;
        }
    cnt = 0;
    while(!S.empty())//������������
    {
       int  i = S.top();
        S.pop();
        T.push(i);
        cnt++;
        for(unsigned j = 0; j < G[i].size(); j++)
        {
            if(!(--indegree[G[i][j].to]))
                S.push(G[i][j].to);
            double w = ve[i] + G[i][j].w;
            if(ve[G[i][j].to] < w)
                ve[G[i][j].to] = w;
        }
    }
    ofstream cout("out.txt");
    delete []indegree;
    rep(i, 0, n-1)
        cout << "Node V"<< i << ":" << ve[i] << endl;
    return 0;
}
