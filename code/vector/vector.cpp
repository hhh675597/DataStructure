#include <iostream>
#include "vector.h"

using namespace std;

int main(int, char** )
{
    int nums[] = {1, 10, 4, 4, 6, 9, 23, 5, 999};
    Vector vec(nums, 9);

    printf("23 is located at %d .\n", vec.find(23));

    vec.sort(0, 8);
    for (int i = 0; i < vec.size(); i++)
        printf("%d\n", vec[i]);
    
    vec.insert(2);
    printf("The new element 2 is located at %d .\n", vec.find(2));

    printf("I guess the search algo cannot detect where 2 is :%d .\nyabali", vec.search(2, 0, 9));
    return 0;
}
