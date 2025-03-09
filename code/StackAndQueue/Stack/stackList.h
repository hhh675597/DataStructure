#include "/home/hhh/DataStructure/code/list/list.h"

template <typename T> class Stack: public List<T> {
public: //size(), empty()等public接口均可直接使用
    void push(T const& e) {
        List<T>::insertAsLast(e);
    } //将某个元素压入栈中，等价于将该元素插入列表尾端
    T pop() {
        return List<T>::remove(List<T>::last());
    } //将栈顶元素弹出，等价于移走列表尾端元素并返回其data值
    T& top() {
        return List<T>::last()->data;
    }
}; //以List模板类派生出Stack类，栈顶/底为列表末/首端