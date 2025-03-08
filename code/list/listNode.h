#include <iostream>

typedef int Rank;
#define ListNodePosi(T) ListNode<T>* //列表节点的地址(position)

template <typename T> struct ListNode {
//成员
    T data; //数值
    ListNodePosi(T) pred; ListNodePosi(T) succ; //前驱，后继
//构造函数
    ListNode() {} //对于首尾header,tailer的构造
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        :data(e), pred(p), succ(s) {} //默认构造器
//操作接口
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};
