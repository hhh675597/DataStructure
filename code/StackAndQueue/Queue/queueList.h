#include "/home/hhh/DataStructure/code/list/list.h"

template <typename T> class Queue: public List<T> {
public: //.size(), .empty()接口可直接使用
    void enqueue(T const& e) {
        insertAsLast(e);
    } //入队，在列表尾部插入
    T dequeue() {
        return remove(first());
    }
    T& front() {
        return first()->data;
    }
};