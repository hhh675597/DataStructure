#include <iostream>

using namespace std;

typedef int Rank; // 秩
#define DEFAULT_CAPACITY  3 //默认的初始容量，可以更大

template <typename T> class vector
{
protected:
    Rank _size; //规模
    int _capacity; //容量
    T* _elem; //数据区
    void copyFrom(T const* A, Rank lo, Rank hi); //复制数组区间A[lo, hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    bool bubble(Rank lo, Rank hi); //扫描交换
    void bubbleSort(Rank lo, Rank hi);//冒泡排序
    Rank max(Rank lo, Rank hi); //选取最大元素
    void selectionSort(Rank lo, Rank hi); //选择排序
    void merge(Rank lo, Rank hi); //归并操作
    void mergeSort(Rank lo, Rank hi); //归并排序
    Rank partiton(Rank lo, Rank hi); //轴点构造算法？
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void heapSort(Rank lo, Rank hi); //堆排序？
public:
//构造函数
    
}; //Vector









int main(int, char** )
{

    return 0;
}