#include <iostream>
#include <fstream>
using namespace std;
/*
������(i,j)�ó���Ӧѹ�������и�λ�õ�ֵ
*/
int ij2num(int i, int j, int *a)
{
    return a[i*(i-1)/2+j];
}
/*
����Cij��ֵ��x��y��Cxy��aΪ���˾���bΪ�˾���
*/
int mul_matrix(int x, int y, int *a, int *b)
{
    int sum = 0;
    for(int k = y; k <= x; k++)//����C(x, y)��ֵ
        sum = sum + ij2num(x, k, a) * ij2num(k, y, b);
    return sum;
}

void print_matrix(int *c, int n)//��ӡ�����Ǿ���
{
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= i; j++)
            cout << c[++cnt] << "  ";
        cout << endl;
    }
}
int main()
{
    ifstream cin("input.txt");
    int n, length;
    int cnt = 0;
    int *a, *b, *c;
    cin >> n;
    length = n * (n + 1) / 2;
    a = new int[length+1];
    b = new int[length+1];
    c = new int[length+1];
    for(int i=1; i <= length; i++)
        cin >> a[i];
    for(int i=1; i <= length; i++)
        cin >> b[i];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
        {
            c[++cnt] = mul_matrix(i, j, a, b);
        }
    print_matrix(a, n);
    print_matrix(b, n);
    print_matrix(c, n);
    return 0;
}
