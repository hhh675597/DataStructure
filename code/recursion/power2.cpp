#include <iostream>
#define ll long long

using namespace std;
ll sqr(ll a) {return a * a;}
ll power2(int n)
{
    if (n == 0) return 1; //递归基
    return (n & 1) ? sqr(power2(n >> 1)) << 1 : sqr(power2(n >> 1)); //按当前n的奇偶分别递归
} //O(logn) = O(r), r为输入指数n的比特位数.Brute-Force需要O(n) time complexity.

int main()
{
    return 0;
}