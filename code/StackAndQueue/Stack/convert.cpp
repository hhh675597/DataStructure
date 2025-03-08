//问题描述：任给十进制整数n, 将其转换为lambda进制的表示形式
#include <iostream>
#include "stackVector.h"

using namespace std;
void convert(Stack<char> S, long long n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}; //2 <= base <= 16, 新进制下的数字

    if (n > 0) {
        S.push(digit[n % base]); //长度不定的逆序线性序列，后进先出
        //n = n / base; //忘记写成递归了
        convert(S, n / base, base);
    }
}

int main(int, char**)
{
    long long n;
    int base;
    Stack<char> ans;

    scanf("%lld%d", &n, &base);

    convert(ans, n, base);
    for (int i = 0; i < ans.size(); i++)
        printf("%c", ans.pop());

    return 0;
}