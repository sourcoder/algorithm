#include <iostream>
using namespace std;
int Search(int a[], int key, int left, int right)
{
    int mod;

    while(left <= right)
    {   mod = (left + right)/2;
        if(mod-1 < 0)
            return -1;
        if(a[mod-1] < key && a[mod] >= key)
            return mod;
        else if(a[mod] < key)
            left = mod + 1;
        else
            right = mod -1;
    }
    return -1;
}
int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int key = 0;
    cout << Search(a, key, 0, 9) << endl;
    return 0;
}
