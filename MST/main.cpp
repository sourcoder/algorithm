//#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory.h>
#include <math.h>
using namespace std;
typedef struct
{
    int from;
    int to;
    int weight;
}Edge;
int n, e,cnt = 0;//n:vertexes e:edge cnt:the minimum
vector <Edge> edge;
bool cmp(Edge a, Edge b)
{
    return a.weight < b.weight;
}
int Find(int *parent, int f)
{
    while(parent[f] > 0)
        f = parent[f];
    return f;
}

void MST()
{
    int n, m, i;
    int parent[1001];
    memset(parent, 0, sizeof(parent));
    for(i = 0; i < e; i++)
    {
        n = Find(parent, edge[i].from);
        m = Find(parent, edge[i].to);
        if(n != m)
        {
            parent[n] = m;
            printf("(%d, %d) %d\n", edge[i].from, edge[i].to, edge[i].weight);
            cnt += edge[i].weight;
        }
    }
    cout << "The minimum: " << cnt << endl;
}
int main()
{
    ifstream cin("input.txt");
    cin >> n >> e;
    for(int i = 0; i < e; i++)
    {
        Edge eg;
        cin >> eg.from >> eg.to >> eg.weight;
        edge.push_back(eg);
    }
    sort(edge.begin(), edge.end(), cmp);
    MST();
    return 0;
}
