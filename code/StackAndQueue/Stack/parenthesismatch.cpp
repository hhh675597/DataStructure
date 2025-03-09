//问题描述：卡特兰数,栈混洗数,括号匹配
#include <iostream>
#include <cstring>
#include "stackVector.h"

#define MAXN 10000
using namespace std;

bool paren(const char s[], int lo, int hi) {
    Stack<char> buff;

    for (int i = lo; i <= hi; i++) {
        switch(s[i]) {
            case '(' :
                buff.push(s[i]); break;
            case '[' :
                buff.push(s[i]); break;
            case '{' :
                buff.push(s[i]); break;
            //遇到左括号,直接入栈
            case ')' :
                if (buff.top() == '(') {
                    buff.pop();
                    break;
                }
                else if (buff.top() != '(' || buff.empty()) {
                    return false;
                    break;
                }
            case ']' :
                if (buff.top() == '[') {
                    buff.pop();
                    break;
                }
                else if (buff.top() != '[' || buff.empty()) {
                    return false;
                    break;
                }
            case '}' :
                if (buff.top() == '{') {
                    buff.pop();
                    break;
                }
                else if (buff.top() != '{' || buff.empty()) {
                    return false;
                    break;
            }
            default: break;
        }
    }

    return buff.empty(); //如果栈空(无残余左括号),则匹配
}

int main(int, char**)
{
    char exp[MAXN];
    int length = 0;
    //fgets(exp, MAXN -1, stdin);
    if (fgets(exp, MAXN - 1, stdin) != NULL) {
        length = strlen(exp);
        if (length > 0 && exp[length - 1] == '\n') {
            exp[--length] = '\0';
        }
    }

    //printf("%s\n", exp);
    //printf("exp length = %d\n", length);
    printf("%d\n", paren(exp, 0, length));

    return 0;
}