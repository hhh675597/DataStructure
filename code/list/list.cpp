#include "list.h"
#include <iostream>

using namespace std;

int main(int, char**)
{
    int nums[5] = {1, 3, 4, 2, 5};
    List<int> l;
    

    for (int i = 0; i < 5; i++)
        l.insertAsLast(nums[i]);
    
    for (int i = 0; i < 5; i++)
        printf("%d ", l[i]);
    printf("\n");
    
    l.sort();
    for (int i = 0; i < 5; i++)
        printf("%d ", l[i]);
    printf("\n");

    l.insertA(l.first(), 100);
    printf("%d\n", l[1]); //输出为100

    l.reverse();
    for (int i = 0; i < l.size(); i++)
        printf("%d ", l[i]);
    printf("\n");

    printf("%p\n", l.find(3));
    l.remove(l.find(3));
    for (int i = 0; i < l.size(); i++)
        printf("%d ", l[i]);
    printf("\n");

    return 0;
}
