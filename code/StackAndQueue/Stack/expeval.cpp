//问题描述：表达式求值，必须考虑运算优先级
#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

#define N_OPTR 9
typedef enum{ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator; //运算符集合
//+, -, *, /, ^, !, (, ), 终止符
const char pri[N_OPTR][N_OPTR] = { //运算符优先等级[栈顶][当前]
/*            |-------------当前运算符-------------*/
/*            +    -    *    /    ^    !    (    )    \0*/
/*-- + */    '>', '>', '<', '<', '<', '<', '<', '>', '>', 
/*|  - */    '>', '>', '<', '<', '<', '<', '<', '>', '>', 
/*栈 * */    '>', '>', '>', '>', '<', '<', '<', '>', '>', 
/*顶 / */    '>', '>', '>', '>', '<', '<', '<', '>', '>', 
/*运 ^ */    '>', '>', '>', '>', '<', '<', '<', '>', '>',  //pri['^']['^']不用向左优先结合律，例如,2^3^5应该被理解为2^(3^5).
/*算 ! */    '>', '>', '>', '>', '>', '>', ' ', '>', '>', 
/*符 ( */    '<', '<', '<', '<', '<', '<', '<', '=', ' ', 
/*|  ) */    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/*-- \0*/    '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};
//又漏传引用!!!
void readNumber(char*& p, stack<float>& stk) { //将起始于p的子串解析为数据(允许操作数含有多个数位,甚至小数),并压入操作数栈
    stk.push((*p - '0')); //当前位置的数字入栈

    while (isdigit(*(++p))) { //p的下一个位置仍然是数字,也就是多个数位的情况
        float p0pnd = stk.top();
        stk.pop();
        stk.push(p0pnd * 10 + (*p - '0'));
    }

    if ('.' != *p) return; //下一位非小数点,当前数解析完成
    else { //否则，意味着还有小数部分
        float fraction = 1;
        float p0pnd = stk.top();
        stk.pop();
        stk.push(p0pnd + (*p - '0') * (fraction = fraction / 10));
    }
}

Operator optr_to_rank(char op) { //将运算符转译为编号
    switch(op) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '(': return L_P;
        case ')': return R_P;
        case '!': return FAC;
        case '^': return POW;
        case '\0': return EOE;
        default: exit(-1); //未知符号, 异常状态退出
    }
}
char orderBetween(char op1, char op2) { //判定运算符之间的优先级关系
    return pri[optr_to_rank(op1)][optr_to_rank(op2)];
} //判定栈顶运算符与当前运算符之间的关系

void append(char*& RPN, float opnd) {
    int n = strlen(RPN); //RPN当前长度,(以'\0'结尾,长度为n + 1)
    char buf[64];

    if (opnd != (float)(int)opnd) 
        sprintf(buf, "%.2f ", opnd); //浮点格式
    else sprintf(buf, "%d ", (int)opnd); //整数格式

    RPN = (char*) realloc(RPN, sizeof(char) * (n + strlen(buf) + 1)); //re allocate动态地扩充RPN表达式容量, recall: MemoryALLOCate(sizeof(??))
    strcat(RPN, buf); //RPN加长
} //数
void append(char*& RPN, char optr) {
    int n = strlen(RPN);

    RPN = (char*) realloc(RPN, sizeof(char) * (n + 3));
    sprintf(RPN + n, "%c ", optr); //RPN + n: pointer
    
    RPN[n + 2] = '\0';
} //运算符
//将数或者运算符接至ReversePolishNotation末尾

float calcu(char op, float n) {
    float ans = 1;
    for (int i = 1; i <= n; i++) ans = ans * i;
    return ans;
}

float calcu(float n1, char op, float n2) {
    switch(op) {
        case '+':
            return n1 + n2;
            break;
        case '-':
            return n1 - n2;
            break;
        case '*':
            return n1 * n2;
            break;
        case '/':
            return n1 / n2;
            break;
        case '^': {
            float ans = 1;
            for (int i = 1; i <= n2; i++) 
                ans = ans * n1;
            return ans;
            break;
        }
        default: exit(-1); //语法错误直接退出
    }
}

float evaluate(char* s, char* rpn) {
    stack<float> opnd;
    stack<char> optr;
    optr.push('\0'); //尾哨兵'\0'也作为头哨兵先入栈

    while (!optr.empty()) {
        if (isdigit(*s)) {
            readNumber(s, opnd);
            append(rpn, opnd.top());
        }

        else {
            //printf("*s points to %c\n", *s);
            switch(orderBetween(optr.top(), *s)) { //比较栈顶运算符和当前运算符的优先级顺序
                case '<': //栈顶优先级更低
                    optr.push(*s); //计算推迟，当前运算符入栈
                    s++;
                    break;
                case '=': //当前运算符为右括号')'或尾部哨兵'\0'
                    optr.pop(); //脱括号
                    s++; //接收下一个符号
                    break;
                case '>': { //栈顶运算符优先级更高
                    char op = optr.top(); optr.pop(); //栈顶运算符弹出栈
                    append(rpn, op); //并接续至rpn结尾
                    if (op == '!') { //唯一的一元运算符!
                        float p0pnd = opnd.top(); opnd.pop();//取出一个栈顶操作数
                        opnd.push(calcu(op, p0pnd));
                    }

                    else  { //其他均为二元运算符
                        float p0pnd2 = opnd.top(); opnd.pop(); //注意这里的1和2，若反过来会引起减法或除法错误
                        float p0pnd1 = opnd.top(); opnd.pop();
                        //printf("p0pnd2 = %02f, p0pnd1 = %02f\n", p0pnd2, p0pnd1);
                        opnd.push(calcu(p0pnd1, op, p0pnd2));
                    }
                    break;
                }
                default: exit(-1); //语法错误直接退出
            }
        }
    }

    return opnd.top();
}

int main(int, char**) {
    char exp[64]; //assert:输入的rpn表达式符合语法
    int length = 0;

    if (fgets(exp, 64 - 1, stdin) != NULL ) {
        length = strlen(exp);
        if (exp[length - 1] == '\n' && length > 0) {
            exp[--length] = '\0';
        }
    }
    //printf("exp = %s ,leng = %d\n", exp, length);
    char* postfix = (char*)malloc(sizeof(char) * 100);

    printf("This expression equals %02f.\n", evaluate(exp, postfix));
    printf("The postfix edition of this infix one is %s\n.", postfix);
    
    return 0;
}