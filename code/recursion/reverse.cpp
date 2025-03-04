#include <iostream>

using namespace std;
void reverse(int* , int, int); //重载的倒置算法原型
void reverse(int* A, int n)
{
    reverse(A, 0, n - 1); //由重载的入口启动算法
} //数组倒置(算法的初始入口，调用的可能是reverse()递归版或迭代版)

void reverse(int* A, int lo, int hi)
{
    if (lo < hi) {
        swap(A[lo], A[hi]);
        reverse(A, lo + 1, hi - 1); //递归地倒置除这两个元素以外的部分
    }
} //多递归基递归版, O(hi - lo + 1)

void reverse2(int*A, int lo, int hi)
{
    while (lo < hi)
        swap(A[lo++], A[hi--]);
} //由递归版等效转化而来的迭代版

int main(int, char**)
{
    int nums[] = {1, 3, 9, 7, 6};
    reverse(nums, 5);

    for (int i = 0; i < 5; i++)
        printf("%d ", *(nums + i));
    
    reverse(nums, 5);
    for (int i = 0; i < 5; i++)
        printf("%d ", *(nums + i));

    return 0;
}