//问题描述：任给十进制整数n, 将其转换为lambda进制的表示形式
#include <iostream>
#include "stackVector.h"

using namespace std;
void convert(Stack<char>& S, long long n, int base) { //不要漏传引用& !!!
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}; //2 <= base <= 16, 新进制下的数字

    if (n > 0) {
        S.push(digit[n % base]); //长度不定的逆序线性序列，后进先出
        //n = n / base; //忘记写成递归了
        convert(S, n / base, base);
    }
} //递归版

void convert_iteration(Stack<char>& S, long long n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    while (n > 0) {
        S.push(digit[n % base]);
        n = n / base;
    }
} //迭代版

int main(int, char**)
{
    long long n;
    int base;
    Stack<char> ans, ans_iteration;

    scanf("%lld%d", &n, &base);

    convert(ans, n, base);
    
    int oldSize = ans.size();

    for (int i = 0; i < oldSize; i++)
        printf("%c", ans.pop());
    printf("\n");

    convert_iteration(ans_iteration, n, base);
    int oldSize_iteration = ans_iteration.size();

    for (int i = 0; i < oldSize_iteration; i++)
        printf("%c", ans_iteration.pop());
    printf("\n");
    return 0;
}
/*
    
    printf("%c\n", ans.pop());
    printf("%c\n", ans.pop());
    printf("%c\n", ans.pop());输出2 3 1正确...bug:ans.size() is changing as you pop out the elem at the top.
*/