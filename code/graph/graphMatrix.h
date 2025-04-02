#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include "graph.h"
#include <vector>

template <typename Tv> struct Vertex {
    Tv data; int inDegree, outDegree; VStatus status; //数据，入度， 出度， 状态
    int dTime, fTime; //时间标签
    int parent; int priority; //遍历树中的父亲顶点和优先级
    Vertex(Tv const& d = (Tv) 0) :
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {} //构造新顶点
}; //顶点结构体

template <typename Te> struct Edge {
    Te data; int weight; EType type; //数据，权重，类型
    Edge(Te const& d, int w) :
        data(d), weight(w), type(UNDETERMINED) {} //构造新边
}; //边结构体

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> { //class graph的派生类graphmatrix,基于邻接矩阵生成的图
private:
    std::vector<Vertex<Tv>> V; //顶点集,向量
    std::vector<std::vector<Edge<Te>*>> E; 
public:
    GraphMatrix() {
        Graph<Tv, Te>::n = Graph<Tv, Te>::e = 0;
    } //构造
    ~GraphMatrix() {
        for (int i = 0; i < Graph<Tv, Te>::n; i++)
            for (int j = 0; j < Graph<Tv, Te>::n; j++)
                delete E[i][j];
    } //析构
//顶点的基本操作：查询第i个顶点(0 <= i < n)
    virtual Tv& vertex(int i) {
        return V[i].data;
    } //数据
    virtual int inDegree(int i) {
        return V[i].inDegree;
    } //入度
    virtual int outDegree(int i) {
        return V[i].outDegree;
    } //入度
    virtual int firstNbr(int i) {
        return nextNbr(i, Graph<Tv, Te>::n);
    } //首个邻接顶点
    virtual int nextNbr(int i, int j) {
        while (-1 < j && !exists(i, --j)); //逆向线性试探
        return j;
    } //顶点i位于顶点j之后的首个顶点
    virtual VStatus& status(int i) {
        return V[i].status;
    } //状态
    virtual int& dTime(int i) {
        return V[i].dTime;
    }
    virtual int& fTime(int i) {
        return V[i].fTime;
    }
    virtual int& parent(int i) {
        return V[i].parent;
    } //遍历树中的父亲顶点
    virtual int& priority(int i) {
        return V[i].priority;
    } //遍历树里的优先级
//顶点的动态操作
    virtual int insert(Tv const& vertex) {
        for (int j = 0; j < Graph<Tv, Te>::n; j++) {
            E[j].push_back(NULL); //在向量末尾添加元素
            n++;
        }
    } //插入顶点，返回编号
    //test
};
#endif