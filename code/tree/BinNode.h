#define BinNodePosi(T) BinNode<T>* //二叉树节点的地址
#define stature(p) ((p) ? (p->height) : -1) //stature也是高度的意思,这里是为了与"规定空树高度为-1"相统一

typedef enum {RB_RED, RB_BLACK} RBColor; //红黑树节点颜色

template <typename T> struct BinNode {
//成员
    T data; //数值
    BinNodePosi(T) parent;
    BinNodePosi(T) lc; BinNodePosi(T) rc; //parent节点,left-child,right-child
    int height; //高度
    int npl; //???Null Path Length左式堆，也可直接用height代替
    RBColor color;//颜色
//构造函数
    BinNode():
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, 
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
//操作接口
    int size(); //当前节点后代总数，也就是以当前节点为root的subtree中node总数
    BinNodePosi(T) insertAsLC(T const&); //将某变量的引用作为当前节点的left child插入
    BinNodePosi(T) insertAsRC(T const&); //将某变量的引用作为当前节点的right child插入
    BinNodePosi(T) succ(); //取当前节点的直接后继
    template <typename VST> void travLevel(VST&); //子树层次遍历
    template <typename VST> void travPre(VST&); //travel prefix先序遍历
    template <typename VST> void travIn(VST&); //travel infix中序遍历
    template <typename VST> void travPost(VST&); //travel postfix后序遍历
//比较器,判等器
    bool operator< (BinNode const& bn) {
        return data < bn.data;
    }
    bool operator== (BinNode const& bn) {
        return data == bn.data;
    }
}; //二叉树节点 类模板
//基于BinNode的一些操作
/***************************** 
 * BinNode性质与状态的判断
 * **************************/
#define IsRoot(x) (! ((x).parent)) //某vertex为root节点当且仅当其parent = NULL
#define IsLChild(x) (! IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (! IsRoot(x) && (&(x) == (x).parent->rc))

#define HasParent(x) (! IsRoot())
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (! HasChild(x))

/***************************** 
 * 与BinNode有特定关系的节点及它们的指针
 * **************************/
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc) //兄弟
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc) //叔叔(写表达式用爷爷)
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc)) //来自父亲的引用

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
    return lc = new BinNode(e, this);
} //将元素e作为当前节点的left child插入
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
    return rc = new BinNode(e, this);
} //将元素e作为当前节点的right child插入

//定位直接后继，succ()接口的实现将在介绍完pre/in/postfix后给出

template <typename T> template <typename VST> void BinNode<T>::travIn(VST& visit) { //元素类型，操作器
    switch(rand() % 5) { //暂随机选择1/5
        case 1: travIn_I1(this, visit); break; //迭代版#1
        case 2: travIn_I2(this, visit); break; //迭代版#2
        case 3: travIn_I3(this, visit); break; //迭代版#3
        case 4: travIn_I4(this, visit); break; //迭代版#4
        default: travIn_R(this, visit); break; //递归版
    }
} //binary tree中infix traverse算法的统一入口