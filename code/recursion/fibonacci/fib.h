
#define ll long long

class Fib {
private:
    int f, g; //f = fib(k - 1), g = fib(k)
public:
    Fib(int n) {
        f = 1; g = 0;
        while (g < n)
            next(); 
    } //初始化为不小于n的最小斐波那契项
    int get() {return g; } //获取当前Fibonacci项
    int next() {g += f; f = g - f; return g; } //转至下一Fibonacci项
    int prev() {f = g - f; g -= f; return g; } //转至上一Fibonacci项
};