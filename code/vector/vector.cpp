#include <iostream>

using namespace std;

typedef int Rank; // 秩
#define DEFAULT_CAPACITY  3 //默认的初始容量，可以更大

template <typename T> class Vector
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
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { 
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _size++)
            _elem[_size] = v;
    }//容量为c, 规模为s, 所有元素初始化为v, s <= c
    Vector(T const* A, Rank n) {
        copyFrom(A, 0, n); 
    }//数组整体复制
    Vector(T const* A, Rank lo, Rank hi) {
        copyFrom(A, lo, hi); 
    }//区间复制
    Vector(Vector<T> const& V) {
        copyFrom(V._elem, V._size); 
    }//向量整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) {
        copyFrom(V._elem, lo, hi); 
    }//区间复制
//析构函数
    ~Vector() {
        delete []  _elem; 
    } //释放内部空间
//只读访问接口
    Rank size() const {
        return _size; 
    } //规模
    bool empty() const {
        return !_size;
    } //判空
    int disordered() const; //判断向量是否已排序
    Rank find(T const& e) const {
        return find(e, 0, _size);
    } //无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const;//无序向量区间查找
    Rank search(T const& e) const {
        return ( _size <= 0) ? -1 : search(e, 0, _size);
    } //有序向量整体查找
    Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找
//可写访问接口
    T& operator[] (Rank r) const; //重载 下标 操作符， 可以类似于数组形式引用各元素
    Vector<T> & operator= (Vector<T> const&); //重载赋值操作符, 以便直接克隆向量
    T remove(Rank r); //删除秩为r的元素
    int remove(Rank lo, Rank hi); //删除秩在[lo, hi)之间的元素
    Rank insert(Rank r, T const& e); //插入元素
    Rank insert(T const& e) {
        return insert(_size, e);
    } //默认在末尾插入新元素
    void sort(Rank lo, Rank hi); //对[lo,hi)排序
    void sort() {
        sort(0, _size);
    } //整体排序
    void unsort(Rank lo, Rank hi); //对[lo,hi)置乱
    void unsort() {
        unsort(0, _size);
    } //整体置乱
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
//遍历
    void traverse(void (* ) (T&)); //使用函数指针, 只读或局部性修改
    template <typename VST> void traverse (VST&); //遍历，使用函数对象，可全局性修改
}; //Vector

template <typename T> void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)]; //分配空间， 规模清零
    _size = 0;
    while (lo < hi) {
        _elem[_size] = A[lo];
        _size++;
        lo++;
    } //以数组区间A[lo, hi)为蓝本复制向量
} //基于复制的向量构造方法

template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V)
{
    if (_elem) 
        delete[] _elem; //释放原有内容
    copyFrom(V._elem, 0, V.size()); //整体复制,size()为一个只读访问接口
    return *this; 
}

template <typename T> void Vector<T>::expand()
{
    if (_size < _capacity) return; //尚未满员，不需要扩容
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //不低于最小容量
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //申请一个容量更大的数组
    for (int i = 0; i < _size; i++) 
        _elem[i] = oldElem[i]; //T为基本类型，或为已重载运算符"="
    delete[] oldElem; //释放原有空间
} //可扩容数组.注意每次在调用insert()接口之前都需要调用expand算法检查内部数组的可用容量

template <typename T> void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return; //装填因子小于0.25时考虑缩容，通常选用更低的阈值
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
} //underflow并非必须解决的问题

template <typename T> T& Vector<T>::operator[](Rank r) const
{   return _elem[r];} //重载向量操作符[],与数组类似地直接通过下标访问元素

template <typename T> void permute(Vector<T>& V)
{
    for (int i = V.size(); i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
} //用重载后的[]实现置乱算法

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi)
{
    T* V = _elem + lo; //将待置乱的子向量[lo, hi)视作另一向量[0, hi - lo)
    for (Rank i = hi - lo; i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
} //与上类似，对外提供的向量置乱接口unsort()，以便测试/比较各种向量算法

template <typename T> static bool lt(T& a, T& b) { return a < b; } //less than
template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } //less than指针版，按照被指对象的大小进行判断.对指针的数值即(被指对象的物理地址)的比较没有意义
template <typename T> static bool eq(T& a, T& b) { return a == b; } //equal
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal指针版

template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
    while ((lo < hi--) && (e != _elem[hi])); //从后向前，规定若有多个命中元素时返回其中秩最大者
    return hi; //若hi < lo, 则失败，约定返回lo - 1;
} //无序向量查找接口find()

template <typename T> Rank Vector<T>::insert(Rank r, T const& e)
{
    expand(); //先检查是否需要扩容
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1]; //自后向前，后继元素后移一个单元
    _elem[r] = e;
    _size += 1;
    return r;
} //向量元素插入接口insert()

template <typename T> int Vector<T>::remove(Rank lo, Rank hi) //必须满足0 << lo << hi <<_size
{
    if (lo == hi) return 0;
    while (hi < _size) 
        _elem[lo++] = _elem[hi++]; //[hi, size)中的元素顺次迁移hi - lo个单位
    _size = lo; //终止时,lo = lo + _size -hi
    shrink(); //若必要则缩容
    return hi - lo; //返回被删除元素的数目    
} //删除区间[lo, hi)

template <typename T> T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r+1); //调用上面的区间删除算法
    return e;
} //利用区间删除实现单个元素删除

template <typename T> int Vector<T>::deduplicate()
{
    int oldSize = _size; //记录原始规模
    Rank i =1; //从第二个元素开始
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i); //invariable: 在当前元素的前缀_elem[0,i)内，所有元素彼此互异
    return oldSize - _size; //被删除元素总数
} //无序向量删重

template <typename T>  void Vector<T>::traverse(void (*visit) (T&)) //函数指针
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]); //函数指针
}

template <typename T> template <typename VST> //元素类型，操作器
void Vector<T>::traverse(VST& visit) //函数对象
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

/*eg
template <typename T> struct Increase //函数对象：递增一个T类对象
{
    virtual void operator() (T& e) {e++;} //假设T可直接递增或已重载++
};

template <typename T> void increase(Vector<T>& V)
{
    V.traverse(Increase<T>()); //以Increase<T>()为基本操作进行遍历
} //统一递增向量中的各元素
*/

//有序向量:前提条件为，各元素之间必须能够比较大小（<,<=等操作符已重载）
template <typename T> int Vector<T>::disordered() const
{
    int cnt = 0; //计数器
    for (int i = 1; i < _size; i++) //检查(_size - 1)对 相邻元素
        if (_elem[i - 1] > _elem[i]) 
            cnt++;
    return cnt; //返回向量中逆序相邻元素对数，向量有序当且仅当n = 0.
} //有序向量鉴别接口disordered()

template <typename T> int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while (++j < _size) { //逐一扫描直到末元素
        if (_elem[i] != _elem[j]) //跳过雷同者
            _elem[++i] = _elem[j]; //将不同的元素直接移到前者右侧，同时开始看下一个
    }
    _size = ++i;
    shrink();
    return j - i; //返回被删除元素总数
} //高效版，利用“有序向量中相等元素必然前后相邻”，批量删除重复元素.

template <typename T> Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); //各按50%的概率采用二分查找或fibonacci查找.
} //在有序向量[lo, hi)区间内确定不大于e的最后一个节点的秩

template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
{
    while (lo < hi) {
        Rank mid = (lo + hi) >> 1;
        if (e < A[mid]) hi = mid; //去前半段
        else if (e > A[mid]) lo = mid + 1; //去后半段
        else return mid;  //直接命中
    } //查找成功，返回对应元素的秩
    return -1; //失败
} //二分查找版本A，有多个元素命中时不能保证返回秩最大的那一个；查找失败时不能指示失败时所处的位置


int main(int, char** )
{

    return 0;
}
