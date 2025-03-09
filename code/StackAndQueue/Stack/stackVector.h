#include "/home/hhh/DataStructure/code/vector/vector.h"


template <typename T> class Stack: public Vector<T> {
public: //size(), empty()以及其他public接口均可直接沿用.若忘记了请自己去查
    void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); } //e入栈等效于将新元素作为向量的末元素插入
    T pop() {
        return Vector<T>::remove(Vector<T>::size() - 1);
    } //将栈顶元素弹出,等效于删除向量的末元素
    T& top() {
        return (*this)[Vector<T>::size() - 1];
    } //访问栈顶元素
};