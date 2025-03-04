#include <iostream>

using namespace std;
long long fib(int n)
{
    return (2 > n) ?
        (long long) n 
        : fib(n - 1) + fib(n - 2); 
} //二分递归版, 指数级的时间复杂度

long long fib_linear(int n, long long& prev)
{
    if (n == 0) {
        prev = 1;
        return 0;
    }
    else {
        long long prevPrev;
        //cout << "prev = "  << prev << " " << "prevPrev = " << prevPrev << endl; 
        prev = fib_linear(n - 1, prevPrev);
        cout << "prev = "  << prev << " " << "prevPrev = " << prevPrev << endl; 
        return prevPrev + prev;
    }
} //线性递归版

long long fibI(int n)
{
    long long f = 1, g = 0;
    while (n-- > 0) {
        g += f;
        f = g - f; //记录当前的一对相邻Fibonacci数
    }
    return g;
} //DP版，从递归基出发，按规模自小而大求解各子问题.

int main(int, char**)
{
    printf("%lld\n", fib(11));
    long long prev;
    printf("%lld\n", fib_linear(11, prev));
    printf("%lld\n", fibI(11));
    return 0;
}