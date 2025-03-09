#include "listNode.h"
#include <iostream>

using namespace std;

template <typename T> class List {
private:
    int _size; //规模
    ListNodePosi(T) header;
    ListNodePosi(T) trailer; //头哨兵，尾哨兵

protected:
    void init(); //创建初始化
    int clear(); //清除所有节点
    void copyNodes(ListNodePosi(T), int); //复制列表中自位置p起的n项
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int); //归并
    void mergeSort(ListNodePosi(T)&, int); //对从p开始的连续n个节点归并排序
    void selectionSort(ListNodePosi(T), int); //选择排序
    void insertionSort(ListNodePosi(T), int); //插入排序

public:
//构造函数
    List() { init(); } //默认
    List(List<T> const& L); //整体复制列表L
    List(List<T> const& L, Rank r, int n); //复制列表中第r项起的n项
    List(ListNodePosi(T) p, int n); //位置p起的n项
//析构函数
    ~List(); //释放所有节点，含首尾哨兵在内
//只读访问接口
    Rank size() { return _size; }
    bool empty() { return _size <= 0; }
    T& operator[] (Rank r) const; //重载[], 支持循秩访问，效率低
    ListNodePosi(T) first() const { return header->succ; } //头哨兵的下一个元素为首个元素
    ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
    bool valid(ListNodePosi(T) p) {
        return p && (header != p) && (trailer != p);
    } //判断位置p是否对外合法
    int disordered() const; //判断列表是否已经排序
    
    ListNodePosi(T) find(T const& e) const {
        return find(e, _size, trailer);
    } //无序列表查找
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; //无序区间查找
    ListNodePosi(T) search(T const& e) const {
        return search(e, _size, trailer);
    } //有序列表查找
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; //有序区间查找
    
    ListNodePosi(T) selectMax(ListNodePosi(T), int n); //在p及其n - 1个后继中选出最大者
    ListNodePosi(T) selectMax() {
        return selectMax(header->succ, _size);
    } //整体最大者
//可写访问接口
    ListNodePosi(T) insertAsFirst(T const& e); //将e当作首元素插入列表
    ListNodePosi(T) insertAsLast(T const& e); //将e当作末元素插入列表
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e); //将e当作p的后继插入, A:After
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e); //将e当作p的前驱插入, B:Before

    T remove(ListNodePosi(T) p); //删除合法位置p处的节点， 返回被删节点
    void merge(List<T>& L) {
        merge(first(), _size, L, L.first(), L._size);
    } //全列表归并
    void sort(ListNodePosi(T) p, int n); //列表区间排序
    void sort() {
        sort(first(), _size);
    } //全列表排序

    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置
//遍历
    void traverse(void (*) (T&)); //遍历，依次实施visit操作(函数指针， 只读或局部性修改)
    template <typename VST> //操作器
    void traverse(VST&); //遍历，依次实施visit操作(函数对象, 可全局性修改)
}; //list

template <typename T> void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = NULL;
    trailer->pred = header; trailer->succ = NULL;
    _size = 0;
} //初始化列表，仅含首尾哨兵，对外有效部分为空

template <typename T> T& List<T>::operator[](Rank r) const {
    ListNodePosi(T) p = first();
    while (0 < r--)
        p = p->succ; //从首节点出发，沿着指针前进r步
    return p->data; //返回目标节点所存的元素
} //重载[]操作符，从位置到秩, 效率较低

template <typename T> ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const {
    while (n--)
        if (e == (p = p->pred)->data)
            return p;
    return NULL; //p越出左边界，说明区间内不包含e,查找失败
} //在无序列表内节点p(可能是trailer)的n个最近的前驱中,找到等于e的最后者
//多种插入接口
template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const& e) {
    _size++;
    return header->insertAsSucc(e); //首哨兵的下一个元素是对外的首元素
} //将e作为首元素插入
template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const& e) {
    _size++;
    return trailer->insertAsPred(e); //尾哨兵的上一个元素是对外的尾元素
} //将e作为尾元素插入
template <typename T> ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e) {
    _size++;
    return p->insertAsSucc(e);
} //将e插在位置p之后的下一个位置
template <typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e) {
    _size++;
    return p->insertAsPred(e);
} //将e插在位置p之前的上一个位置
//典型的doubly linked list插入操作
template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
    ListNodePosi(T) x = new ListNode(e, pred, this); //请回到.h看ListNode的初始化方式，已经规定x->pred = pred, x->succ = this
    pred->succ = x;
    pred = x; //注意先后顺序问题
    return x;
}
template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
    ListNodePosi(T) x = new ListNode(e, this, succ); //请回到.h看ListNode的初始化方式，已经规定x->pred = pred, x->succ = this
    succ->pred = x;
    succ = x;
    return x;
}

template <typename T> void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init(); //创建头、尾节点哨兵并做初始化
    while (n--) //p为合法位置且至少有n - 1个真后继节点
        insertAsLast(p->data);
        p = p->succ;
}
template <typename T> List<T>::List(ListNodePosi(T) p, int n) {
    copyNodes(p, n);
} //复制列表中自位置p起的n项
template <typename T> List<T>::List(List<T> const& L) {
    copyNodes(L.first(), L._size);
} //整体复制列表L
template <typename T> List<T>::List(List<T> const& L, Rank r, int n) {
    copyNodes(L[r], n);
} //复制L中自第r项起的n项

template <typename T> T List<T>::remove(ListNodePosi(T) p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--; //释放空间，规模-1
    return e; //返回被删除元素备份的数值
}

template <typename T> List<T>::~List() {
    clear();
    delete header; delete trailer;
}
template <typename T> int List<T>::clear() {
    int oldSize = _size;
    while (0 < _size) 
        remove(header->succ); //反复删除首节点，直至列表变空
    return oldSize;
}

template <typename T> int List<T>::deduplicate() {
    if (_size < 2) 
        return 0; //仅0or1个元素
    int oldSize = _size;
    ListNodePosi(T)  p = header; Rank r = 0;
    while (trailer != (p = p->succ)) {
        ListNodePosi(T) q = find(p->data, r, p); //在p的r个(真)前驱中查找雷同者
        q ? remove(q) : r++; //若雷同者存在，删除；否则，秩加一
    } //invariable:循环过程中的任一时刻，p的所有前驱互不相同
    return oldSize - _size;
} //无序列表删重,O(n^2)

template <typename T> void List<T>::traverse(void(*visit)(T&)) {
    for(ListNodePosi(T) p = first(); p != trailer; p = p->succ)
        visit(p->data);
}
template <typename T> template <typename VST> //元素类型，操作器
void List<T>::traverse(VST& visit) {
    for(ListNodePosi(T) p = first(); p != trailer; p = p->succ)
        visit(p->data);
}
//有序列表
template <typename T> int List<T>::uniquify() {
    if (_size < 2) return 0;
    int oldSize = _size; Rank r = 0;
    ListNodePosi(T) p = first(); ListNodePosi(T) q;
    
    while (trailer != (q = p->succ)) { //仅需考查紧邻的节点对(p, q)
        if (p->data != q->data) 
            p = q; //若互异，转向下一区段
        else remove(q);
    }

    return oldSize - _size;
} //有序列表删重

template <typename T> ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const {
    while (0 <= n--) 
        if ((p = p->pred)->data <= e)
            break;
    return p; //返回查找终止的位置，可能命中、数组越界或范围越界
} //在节点p的n个(真)前驱中，找到不大于e的最后者

template <typename T> void List<T>::sort(ListNodePosi(T) p, int n) {
    switch (rand() % 3) {
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
} //统一的排序接口

template <typename T> void List<T>::insertionSort(ListNodePosi(T) p, int n) {
    for (int i = 0; i < n; i++) {
        insertA(search(p->data, i, p), p->data); //查找合适的位置：不大于p->data的最后者并插入其后
        p = p->succ;
        remove(p->pred); //更新为下一节点
    }
} //插入排序

template <typename T> void List<T>::selectionSort(ListNodePosi(T) p, int n) {
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; i++)
        tail = tail->succ;
    while (1 < n) {
        ListNodePosi(T) maxn = selectMax(head->succ, n);
        insertB(tail, remove(maxn));
        tail = tail->pred;
        n--;
    }
} //选择排序
template <typename T> ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
    ListNodePosi(T) maxn = p;
    ListNodePosi(T) cur = p;
    for (ListNodePosi(T) cur = p; 1 < n; n--) {
        if ((cur = cur->succ)->data >= maxn->data)
            maxn = cur;
    }
    return maxn;
} //selectMax遍历版，复杂度可以降至O(logn).

template <typename T> int List<T>::disordered() const{
    int cnt = 0;
    for (ListNodePosi(T) p = first(); p != trailer; p = p->succ)
        if (p->data > p->succ->data)
            cnt += 1;
    return cnt;
} //判断是否已排序

template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m) { //当前列表中自p起的n个元素，和列表L中自q起的m个元素merge
    ListNodePosi(T) pp = p->pred; //借助前驱(可以是header), 以便返回前...
    while (0 < m) {
        if ((0 < n) && (p->data <= q->data)) {
            p = p->succ; //p指向其后继位置
            if (q == p)
                break;
            n--;
        }
        else { //p已超出右边界或q的元素小于p的元素
            insertB(p, L.remove((q = q->succ)->pred)); //将q转移至p之前，
            m--;
        }
    }
    p = pp->pred; //方便起见，归并所得的有序列表依然起始于节点p
} //two-way merge

template <typename T> void List<T>::mergeSort(ListNodePosi(T)& p, int n) {
    if (2 > n) return;
    int m = n >> 1;
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++)
        q = q->succ; //花费O(n)时间将列表均分为两份，对比向量仅需消耗常量时间，原因在于循秩访问
    mergeSort(p, m); mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
} //归并排序

template <typename T> void List<T>::reverse() {
    ListNodePosi(T) p = header;
    ListNodePosi(T) q = trailer;
    for (int i = 0; i < _size; i = i + 2) {
        swap((p = p->succ)->data, (q = q->pred)->data);
    }
} //倒序
