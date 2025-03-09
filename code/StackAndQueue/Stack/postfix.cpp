//reverse Polish notation evaluation
//缺陷：仅能进行10以内的计算.解决：参见expeval中的readNumber()函数
#include <iostream>
#include "stackVector.h"
#include <cstring>

using namespace std;

int factorial(int n) {
    int fact = 1;
    for (int i = 2; i <= n; i++) fact = fact * i;
    return fact;
}

int rpnEval(const char* s, int n) {
    Stack<int> nums;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if ('0' <= s[i] && '9' >= s[i]) { //s[i] 是操作数
            nums.push(s[i] - '0'); //将s[i]压入栈中
        }

        else {
            switch(s[i]) {
                case '+' : {
                    int buff = nums.pop();
                    int add = nums.pop() + buff;
                    nums.push(add);
                    break;
                }
                case '-' : {
                    int buff = nums.pop();
                    int sub = nums.pop() - buff;
                    nums.push(sub);
                    break;
                }
                case '*' : {
                    int buff = nums.pop();
                    int mul = buff * nums.pop();
                    nums.push(mul);
                    break;
                }
                case '/' : {
                    int buff = nums.pop();
                    int div = nums.pop() / buff;
                    nums.push(div);
                    break;
                }
                case '!': {
                    nums.push(factorial(nums.pop()));
                    break;
                }
                case '^': {
                    int expon = nums.pop();
                    int base = nums.pop();
                    int pow = 1;
                    for (int j = 1; j <= expon; j++) {
                        pow = pow * base;
                    }
                    nums.push(pow);
                    break;
                }
                default: break;
            }
        }
    } 
    return nums.top();
}

int main(int, char**) {
    char exp[100]; //assert:输入的rpn表达式符合语法
    int length = 0;

    if (fgets(exp, 100 - 1, stdin) != NULL ) {
        length = strlen(exp);
        if (exp[length - 1] == '\n' && length > 0) {
            exp[--length] = '\0';
        }
    }
    
    printf("%d\n", rpnEval(exp, length));
    return 0;
}

//样例 23*5-23^4/+