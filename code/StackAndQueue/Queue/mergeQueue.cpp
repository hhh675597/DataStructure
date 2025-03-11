#include <iostream>
#include <queue>

using namespace std;

queue<int> merge_queue(queue<int>& a, queue<int>& b) {
    queue<int> q;

    while (a.size() > 0 || b.size() > 0) {
        if (a.empty() || a.front() >= b.front()) {
            //printf("a.front%d >= b.front%d\n", a.front(), b.front());
            q.push(b.front());
            b.pop();
        } else if (b.empty() || b.front() > a.front()) {
            //printf("a.front%d < b.front%d\n", a.front(), b.front());
            q.push(a.front());
            a.pop();
        }
    }
    return q;
}

int main(int, char**) {
    queue<int> q1, q2;

    for (int i = 0; i < 10; i += 2) 
        q1.push(i);

    for  (int j = 1; j < 17; j += 3) 
        q2.push(j);
    
    queue<int> ans = merge_queue(q1, q2);
    int oldSize = ans.size();
    for (int i = 0; i < oldSize; i++) { //这里不能打成ans.size()，一直在变
        printf("%d ", ans.front());
        ans.pop();
    }
}