#include <iostream>
#include <stack>

using namespace std;

int nSolu = 0; //n皇后问题解的总数
struct Queen {
    int x, y; //x行号,y列号
    Queen(int xx, int yy) {
        x = xx; y = yy;
    }

    bool operator==(Queen const& q) const {
        return x == q.x //行冲突(实际上不可能发生)
             ||y == q.y //列冲突
             ||x - y == q.x - q.y //对角线
             ||x + y == q.x + q.y; //反对角线
    }  //重载 == 判等操作符
    bool operator!=(Queen const& q) const {
        return !(*this == q);
    } //重载不等号
};

int find(stack<Queen> stk, Queen const& q) {
    int length = stk.size();
    while (length > 0) {
        if (stk.top() != q) {
            stk.pop();
            length--;
            //printf("length = %d\n", length);
        }
        else break;
    }
    return length;
}

void placeQueens(int n) {
    stack<Queen> solution; //存放部分解的栈
    Queen q(0, 0); //在原点位置放置第一个

    do {
        if (n <= solution.size() || n <= q.y) { //若已出界
            q = solution.top(); solution.pop(); //回溯到上一行
            q.y++; //probe下一列(目前列已经确认无解)
        }

        else {
            while (q.y < n && 0 < find(solution, q)) { //存在冲突的两个皇后
                q.y++; //探测下一列 
            }
            
            if (q.y < n) {
                solution.push(q);
                if (n <= solution.size()) //部分解已确认为全局解
                    nSolu++;
                q.x++; q.y = 0; //转入下一行，从第一列开始探测
            }
        }
    } while (q.x > 0 || q.y < n);
}

int main(int, char**) {
    int n;
    scanf("%d", &n);
    /*test:find(stack, Queen); operator ==
    stack<Queen> test;
    Queen q1(0, 0); test.push(q1);
    Queen q2(1, 2); test.push(q2);

    printf("%d", q1 == q2);
    Queen q3(2, 0);
    printf("%d\n", find(test, q3));
    */
    
    placeQueens(n);

    printf("ans = %d\n", nSolu);
    return 0;
}