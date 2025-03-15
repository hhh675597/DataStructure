#ifndef GRAPH_H
#define GRAPH_H
#include <stack>
#include <climits>

#define stack std::stack

typedef enum {UNDISCOVERED, DISCOVERED, VISITED} VStatus; //顶点状态
typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWORD} EType; //边在遍历树中的类型

template <typename Tv, typename Te> class Graph {
private:
    void reset() { 
        for (int i = 0; i < n; i++) { //所有顶点
            status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1; //状态，时间标签 
            parent(i) = -1; priority(i) = INT_MAX; //在遍历树中的父节点，权重
            for (int j = 0; j < e; j++)
                if (exists(i, j)) //如果存在边ij
                    type(i, j) = UNDETERMINED;
        }
    } //所有顶点，边的辅助信息复位
//连通域中的
    void BFS(int, int&); //宽搜
    void DFS(int, int&); //深搜
    void BCC(int, int&, stack<int>&); //基于DFS的双连通分量分解算法
    bool Tsort(int, int&, stack<Tv>*); //基于DFS的拓扑排序算法
    template <typename PU> void PFS(int, PU); //优先级搜索框架
public:
//顶点
    int n; //顶点总数
    virtual int insert(Tv const& ) = 0; //插入顶点，返回编号
    virtual Tv remove(int ) = 0; //删除顶点及其关联边，返回该顶点信息
    virtual Tv& vertex(int ) = 0; //顶点v的数据（该顶点的确存在）
    virtual int inDegree(int ) = 0; //顶点v的入度（该顶点的确存在）
    virtual int outDegree(int ) = 0; //顶点v的出度（该顶点的确存在）
    virtual int firstNbr(int ) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr(int, int) = 0; //顶点v(相对顶点j)的下一个邻接顶点
    virtual VStatus& status(int ) = 0; //顶点v的状态
    virtual int& dTime(int ) = 0; //顶点v的时间标签dTime
    virtual int& fTime(int ) = 0; //顶点v的时间标签fTime
    virtual int& parent(int ) = 0; //在遍历树中的父亲顶点
    virtual int& priority(int ) = 0; //在遍历树中的优先级数
//边(规定将无向图中的每条边都看成方向互逆的一对有向边)
    int e; //总边数
    virtual bool exists(int, int ) = 0; //边(u, v)是否存在
    virtual void insert(Te const&, int, int, int) = 0; //在u和v之间插入权重为w的边e
    virtual Te remove(int, int ) = 0;//删除顶点v和u之间的顶点e, 返回该边信息
    virtual EType& type(int, int) = 0; //边(v, u)的类型
    virtual Te& edge(int, int) = 0; //边(v, u)的数据(该边的确存在)
    virtual int& weight(int, int) = 0; //(v, u)的权重
//算法
    void bfs(int);
    void dfs(int);
    void bcc(int); //基于深搜的双连通分量分解算法
    stack<Tv>* tSort(int); //基于深搜的拓扑排序算法
    void prim(int); //最小生成树prim算法
    void Dijkstra(int); //最短路dijkstra
    template <typename PU> void pfs(int, PU); //优先级搜索框架
}; //图ADT操作接口


#endif //GRAPH_H