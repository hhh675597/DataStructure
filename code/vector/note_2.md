数据结构:数据项之间的逻辑次序 线性/半线性/非线性
线性：sequence = vector(物理存放位置与逻辑次序完全吻合，此时逻辑次序称为rank) + list(间接定址，物理存放位置未必相邻，封装位置position)
2.1数组
    2.1.1数组
    prefix: all predecessors;suffix: all successors
    如何理解通过数组可“直接”“访问”某一元素？直接：one addition plus one multiplication in 常数时间 A(起始地址) + i(subscript) * s
    2.1.2向量
    call-by-rank：若元素e的前驱元素共有r个，则其秩就是r.
    抽象后，同一向量中的各元素不一定属于同一类型，不一定可比->有序向量：引入 通用比较器 或 重载 对应的操作符（under the assumption that 各元素具有大小可比性）
2.2接口
    