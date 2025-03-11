#include "BinNode.h"


template <typename T> class BinTree {
protected:
    int _size; //规模
    BinNodePosi(T) _root; //指向根节点的指针
    virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
    Bintree() : _size(0), _root(NULL) {} //构造函数
    ~BinTree() {
        if (_size > 0)
            remove(_root); //析构函数
    }
    int size() const { return _size; } //规模
    bool empty() const { return !_root; } //判空
    BinNodePosi(T) root() { return _root; } //树根

    BinNodePosi(T) insertAsRoot(T const& e); //插入根节点
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //将e作为x的左孩子插入
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //将e作为x的右孩子插入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x的left-subtree接入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x的right-subtree接入
    
    int remove(BinNodePosi(T) x); //删除以 指针x所指向的节点 为根的子树,返回该子树原先的规模
    BinTree<T>* secede(BinNodePosi(T) x); //将子树x从当前树中摘除，并将其转化为一棵独立子树
    
    template <typename VST> void traLevel(VST& visit) {
        if (_root)
            _root->travLevel(visit);
    } //层次遍历
    template <typename VST> void travPre(VST& visit) {
        if (_root)
            _root->travPre(visit);
    } //先序遍历
    template <typename VST> void travIn(VST& visit) {
        if (_root)
            _root->travIn(visit);
    } //中序遍历
    template <typename VST> void traPost(VST& visit) {
        if (_root)
            _root->travPost(visit);
    } //后序遍历

    bool operator<(BinTree<T> const& t) {
        return _root && t._root && (_root < t._root);
    } //比较器
    bool operator==(BinTree<T> const& t) {
        return _root && t._root && (_root == t._root);
    } //判等器
}; //BinTree模板class

template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc)); //max函数的具体规则因树而异
} //更新节点x高度