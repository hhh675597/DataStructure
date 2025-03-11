#include <iostream>
#include <queue>

using namespace std;

struct Customer {
    int window; //所属窗口(排哪队?)
    unsigned int time;
}; //顾客类

int best_window(queue<Customer> windows[], int n_win) {
    int minsize = windows[0].size();
    int opti_win = 0;
    for (int i = 1; i < n_win; i++) {
        if (minsize > windows[i].size()) {
            minsize = windows[i].size();
            opti_win = i;
        }
    }
    return opti_win;
} //查找目前最短队列

void serve(int n_win, int servtime) {
    queue<Customer>* windows = new queue<Customer>[n_win]; //开一个数组(指针)，为每个窗口建一个队列
    for (int now = 0; now < servtime; now++) {
        if (rand() % (n_win + 1)) { //新顾客以n_win / n_win+1 的概率到达
            Customer c;
            c.time = 1 + rand() % 97; //时长随机

            c.window = best_window(windows, n_win);
            windows[c.window].push(c); //新顾客进入相应的队列
        }
    }

    for (int i = 0; i < n_win; i++) {
        if (!windows[i].empty()) { //若第i个窗口非空
            if (--windows[i].front().time <= 0) //队首成员时间逐渐减少，至小于等于0时
                windows[i].pop(); //首个顾客完成服务，出队
        }
    }

    delete[] windows; //释放所有队列
}

int main(int, char**) {

    
}