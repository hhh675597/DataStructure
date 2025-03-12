#include "BinNode.h"
#include <memory>
#include <stack>
#include <queue>

using namespace std;
template <typename T> class BinTree {
protected:
    int _size; //规模
    BinNodePosi(T) _root; //指向根节点的指针
    virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
    BinTree() : _size(0), _root(NULL) {} //构造函数
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
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &t); //T作为x的left-subtree接入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &t); //T作为x的right-subtree接入
    
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
    template <typename VST> void travPost(VST& visit) {
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
    return x->height = 1 + max(stature(x->lc), stature(x->rc)); //具体规则(如红黑树)因树而异
} //更新节点x高度
template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
    while (x) {
        if (x->height == updateHeight(x)) {
            break; //从某一节点开始高度不再发生变化，提前终止
        } else {
            x = x->parent;
        }
    } //自下而上更新所有祖先的高度
} //从x出发覆盖历代祖先的高度

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) {
    _size = 1;
    return _root = new BinNode<T>(e); //将e当作根节点
} //将第一个元素e插入空树，随即成为树根

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
} //将元素e作为x的左孩子插入
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
} //将元素e作为x的右孩子插入

template <typename T> BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &t) { //初始x->lc == NULL
    if (t->_root) {
        x->lc = t->_root;
        x->lc->parent = x;
    }
    _size += t->_size; updateHeightAbove(x); //更新全树规模

    t->_root = NULL;
    t->_size = 0;
    release(t);
    t = NULL; //释放原树
    return x; //返回起始位置
} //将t作为节点x的左子树插入，t本身置空
template <typename T> BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &t) { //初始x->lc == NULL
    if (t->_root) {
        x->rc = t->_root;
        x->rc->parent = x;
    }
    _size += t->_size; updateHeightAbove(x); //更新全树规模

    t->_root = NULL;
    t->_size = 0;
    release(t);
    t = NULL; //释放原树
    return x; //返回起始位置
} //将t作为节点x的右子树插入，t本身置空

template <typename T> int BinTree<T>::remove(BinNodePosi(T) x) {
    FromParentTo(*x) = NULL; //切断来自父节点的指针
    updateHeightAbove(x->parent); //更新祖先高度

    int n = removeAt(x); //删除子树x
    -size = _size - n;
    return n; //返回被删除的节点总数
} //删除以x为根的子树，更新树的规模及祖先高度，返回被删除节点数目

template <typename T> static int removeAt(BinNodePosi(T) x) { //断言x为二叉树中的合法位置
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc); //递归释放左右子树
    release(x->data);
    release(x);
    return n; //删除节点总数
} //删除二叉树中位置x处的节点及其后代，返回被删除的节点数目

template <typename T> BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) { //断言x为二叉树中的合法位置
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent); //与删除子树类似的操作

    BinTree<T>* NEW = new BinTree<T>; //开一棵新树
    NEW->_root = x; //新树以x为根 
    x->parent = NULL; //根节点没有父亲节点
    NEW->_size = x->size();

    _size = _size - NEW->_size; //更新原树的规模
    return NEW; //返回新树的指针
};

template <typename T, typename VST> void travPre_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return; //x不存在，直接返回(针对叶子节点无孩子的情形)

    visit(x->data);
    travPre_R(x->lc, visit); //类尾递归
    travPre_R(x->rc, visit); //典型的尾递归
} //递归定义preorder traversal先序遍历
template <typename T, typename VST> void travIn_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
} //递归定义inorder traversal
template <typename T, typename VST> void travPost_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
} //递归定义postorder traversal

template <typename T, typename VST> void travPre_I1(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> path;
    if (x) path.push(x);

    while (!path.empty) {
        x = path.top();
        path.pop();
        visit(x->data);

        if (HasRChild(*x)) path.push(x->rc); 
        if (HasLChild(*x)) path.push(x->lc); //注意入栈的先后顺序！因为栈"后进先出"，且需要遍历左子树，所以左孩子后入栈 
    }
} //递归版preorder中均为(类)尾递归，可以直接用迭代方式替代, 迭代版#1

template <typename T, typename VST> static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit,stack<BinNodePosi(T)>& stk) {
    while (x) {
        visit(x->data);
        if (x->rc) stk.push(x->rc); //若有右孩子，则入栈
        x = x->lc; //沿最左侧通路深入
    }
} //沿左分支不断深入

template <typename T, typename VST> void travPre_I2(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> stk;
    while (true) {
        visitAlongLeftBranch(x, visit, stk);
        if (stk.empty) break;
        x = stk.top(); //回溯
        stk.pop();
    }
} //先序遍历迭代版#2

template <typename T, typename VST> static void goAlongLeftBranch(BinNodePosi(T) x, stack<BinNodePosi(T)>& stk) {
    while (x) {
        stk.push(x);
        x = x->lc;
    }
} //向最左侧路径深入但不访问

template <typename T, typename VST> void travIn_I1(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> stk;
    while (true) {
        goAlongLeftBranch(x, stk);
        if (stk.empty()) break;

        x = stk.top(); //到底
        visit(x->data);
        stk.pop();
        x = x->rc; //转向右子树
    }
} //中序遍历迭代版#1

template <typename T> BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) s = this; //临时变量
    if (rc) { //目前节点有右孩子，则直接后继必然位于右子树中
        s = rc; //进right branch
        while (HasLChild(*s)) 
            s = s->lc; //向左侧深入
    } else { //当前节点无右孩子
        while (IsRChild(*s))
            s = s->parent;
        s = s->parent;
    }
} //定位某个节点的直接后继(按inorder)

template <typename T, typename VST> void travIn_I2(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> stk;

    while (true) {
        if (x) {
            stk.push(x);
            x = x->lc;
        } else if (!stk.empty()) {
            x = stk.top();
            visit(x->data);
            stk.pop();

            x = x->rc; //去右子树
        } else break;
    }
} //中序遍历迭代版#2，与#1仅有形式上的不同

template <typename T, typename VST> void travIn_I3(BinNodePosi(T) x, VST& visit) {
    bool backtracked = false; //回溯标记，判断前一步是否刚从右子树回溯

    while (true) {
        if (!backtracked && HasLChild(*x)) { //有左孩子
            x = x->lc; //持续向左子树深入
        } else { //无左子树(到达左侧最深) 或 刚开始回溯(左子树已经全部访问完，回到局部root)
            visit(x->data);
            if (HasRChild(*x)) { //有右孩子
                x = x->rc; //向右子树深入
                backtracked = false;
            } else {
                backtracked = true;
                if (!(x = x->succ()))
                    break;
            }
        }
    }
} //中序遍历迭代版#3，在#2基础上修改而来，放弃栈改用parent指针，空间复杂度下降、时间复杂度上升

template <typename T, typename VST> void travIn_I4(BinNodePosi(T) x, VST& visit) {
    while (true) {
        if (HasLChild(*x)) { //有左孩子
            x = x->lc; //持续向左子树深入
        } else { //无左子树(到达左侧最深)
            visit(x->data);

            while (!HasRChild(*x)) { //左侧最深节点无右孩子
                if (!(x = x->succ())) //向前回溯
                    return; //遇到末节点(唯一一个无后继),直接返回
                else visit(x->data); //此时x已经被更新为x的直接后继.这些点是位于中间的、第二个访问的"root"
            }
            x = x->rc; //左侧最深点有右孩子，进入右侧
        }
    }
} //中序遍历迭代版#4

template <typename T> static void gotoHLVFL(stack<BinNodePosi(T)>& stk) {
    while (BinNodePosi(T) x = stk.top()) {
        if (HasLChild(*x)) {
            if (HasRChild(*x))
                stk.push(x->rc);
            stk.push(x->lc);
        } else stk.push(x->rc);
    }
    stk.pop(); //最后一次操作会使得栈顶是NULL,需要pop出去
} //find Heighest Leaf Visible From Left(后序遍历开始的节点)

template <typename T, typename VST> void travPost_I(BinNodePosi(T) x, VST& visit) {
    stack<BinNodePosi(T)> stk;
    if (x) stk.push(x); //根节点入栈
    while (!stk.empty()) {
        if (stk.top() != x->parent)
            gotoHLVFL(stk);
        x = stk.top();
        stk.pop();
        visit(x->data);
    }
} //后序遍历迭代版

template <typename T> template <typename VST> void BinNode<T>::travLevel(VST& visit) {
    queue<BinNodePosi(T)> q;
    q.push(this); //根节点入队
    while(!q.empty()) { //只要队列非空
        BinNodePosi(T) x = q.front(); q.pop(); //取出并访问队首节点
        visit(x->data);
        if (x->lc) q.push(x->lc);
        if (x->rc) q.push(x->rc);
    }    
} //二叉树层次遍历，队列实现