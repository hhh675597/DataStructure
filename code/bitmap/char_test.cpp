#include <iostream>

using namespace std;

int main(int, char**) {
    printf("%c\n", 'a');
    printf("%d\n", 'a');
    printf("%d\n", (int)'a');
    printf("%c\n", 97);
    printf("%c\n", '0' + 3);
    return 0;
}