#include "bitmap.h"
#include <cstring>
#include <iostream>

using namespace std;

string deduplicateASCII(const char* str) {
    // 创建位图，只需128位即可表示所有ASCII字符
    Bitmap bm(128);
    string result = "";
    
    for(int i = 0; i < strlen(str); i++) {
        bm.set(str[i]);  // 将ASCII码值对应的位置置1
    }
    
    for(int i = 0; i < 128; i++) {
        if (bm.test(i)) {
            printf("%d\n", i);
            result += (char)i;
        }
    }
    
    return result;
}

int main() {
    const char* test = "Hello world";
    string result = deduplicateASCII(test);
    cout << "Original: " << test << endl;
    cout << "After deduplication: " << result << endl;
    return 0;
}
