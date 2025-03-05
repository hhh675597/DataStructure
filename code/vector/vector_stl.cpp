#include <iostream>
#include <vector> //包含STL中的vector容器

using namespace std;

int main(int, char**)
{
    vector<int> v;
    vector<int> v1(5);
    vector<int> v2(5, 10);
//添加元素
    v.push_back(1);
    v.push_back(4);
//访问元素
    cout << v[0] << " ";
    cout << v.at(1) << endl;
//获取大小
    int size = v.size();
//traverse
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    
    return 0;
}