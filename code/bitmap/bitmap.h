#include <cstring>
#include <iostream>


class Bitmap {
private:
    char* M; 
    int N; //比特图所存放的空间M[], 容量为N*sizeof(char)*8位
protected:
    void init(int n) {
        M = new char[N = (n + 7) / 8];
        memset(M, 0, N); //This line effectively initializes a block of memory starting at address M with 0s, for a length of N bytes.
    }
public:
    Bitmap(int n = 128) {
        init(n);
    } //按规定或默认规模创建位图
    Bitmap(char* file, int n = 128) {
        init(n);
        FILE* fp = fopen(file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
    } //按指定或默认规模从指定文件中读取位图
    ~Bitmap() {
        delete[] M;
        M = NULL;
    }

    void set(int k) {
        expand(k);
        M[k >> 3] |= (0x80 >> (k & 0x07));
    } //将第k个位置设置为true,即将整数k加入当前集合
/*
这行代码利用位运算在字符数组 M 的适当位置上“置 1”，其本质目的是将第 k 个比特位设置为 1。下面详细说明它的各部分含义：

M[k >> 3]

表示数组 M 中的第 k/8 个字节（k >> 3 等价于 k 除以 8，舍去余量）。
因为一个 char 有 8 位，第 k 个比特对应于第 k/8 个 char 中的某一位。
(0x80 >> (k & 0x07))

0x80（十六进制）表示二进制 1000 0000.(仅含最高位一个1!!!)
k & 0x07 计算的是 k 的低 3 位，相当于 k % 8，即 k 在所在字节中的位偏移。
将 0x80 右移 (k % 8) 位后，就得到一个仅在相应位置上为 1，其余为 0 的掩码。例如：
如果 k%8 == 0，则 (0x80 >> 0) 为 1000 0000；
如果 k%8 == 3，则 (0x80 >> 3) 为 0001 0000。

|= 运算符
是按位或赋值运算符，将 M[k >> 3] 与右侧的掩码进行按位或运算，并将结果存回 M[k >> 3]。
这样可以保证仅将目标位置 1，而其他位保持不变。
综合起来，这行代码的作用就是：

找到 M 数组中第 k/8 个字节，
生成一个仅在 k%8 所示位为 1 的掩码，
然后将该字节与掩码进行 OR 运算，从而将对应的比特位置 1。
这种操作常用于位图（Bitmap）中标记某个位置的存在状态
*/
    void clear(int k) {
        expand(k);
        M[k >> 3] &= ~(0x80 >> (k & 0x07));
    } //将第k个位置设置为false,即从当前集合删除整数i
    bool test(int k) {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07));
    } //检查第k个位置是否为true, 即判断整数k是否处于当前集合

    void expand(int k) { //若被访问的Bitmap[k]已出界，则需扩容
        if (k < 8 * N)
            return; //仍在界内无需扩容
        int oldN = N;
        char* oldM = M;
        init(2 * k);//与向量类似的加倍策略

        for (int i = 0; i < oldN; i++) {
            M[i] = oldM[i];
        } //编译器找不到memcpy_s函数，用一个for loop替代

        delete[] oldM;
    }

    char* bits_to_string(int n) {
        expand(n - 1); //此时可能被访问的最高位为bitmap[n - 1]
        char* s = new char[n + 1];
        s[n] = '\0';
        for (int i = 0; i < n; i++)
            s[i] = test(i) ? '1' : '0';
        return s;
    } //将前n位转换为字符串

    void dump(char* file) {
        FILE* fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    } //将生成的位图M导出至指定的文件，以便对此后的新位图批量初始化

    /*void Print() {
        for (int i = 0; i < strlen(M); i++)
            printf("%c ", M[i]);
        printf("\n");
    }//调试用
    */
};