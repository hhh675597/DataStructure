#include <iostream>
#include <stack>

using namespace std;

typedef enum {AVAIBLE, ROUTE, BACKTRACKED, WALL} Status; //迷宫单元状态
//原始可用的，位于路径上的，所有方向均尝试失败后回溯的，不可使用的

typedef enum {UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} Direction; //单元的相对邻接方向
//未定(未被搜索过而仍处于avaible状态的节点邻接方向未知)，东，南，西，北，无路可通

inline Direction nextDire(Direction dire) {
    return Direction(dire + 1);
} //依次转入下一邻接方向

struct Cell {
    int x, y; //坐标
    Status status; //类型
    Direction incoming, outgoing; //进入，走出方向
}; //格点类

#define MAZE_MAX 24 //最大尺寸
Cell maze[MAZE_MAX][MAZE_MAX]; //迷宫棋盘

inline Cell* neighbour(Cell* cell) {
    switch(cell->outgoing) {
        case EAST: return cell + MAZE_MAX;
        case SOUTH: return cell + 1;
        case WEST: return cell - MAZE_MAX;
        case NORTH: return cell - 1;
        default: exit(-1);
    }
} //查询相邻格点

inline Cell* advance(Cell* cell) {
    Cell* next;

    switch(cell->outgoing) {
        case EAST: next = cell + MAZE_MAX; next->incoming = WEST; break; //向东
        case SOUTH: next = cell + 1; next->incoming = NORTH; break; //向南
        case WEST: next = cell - MAZE_MAX; next->incoming = EAST; break; //向西
        case NORTH: next = cell - 1; next->incoming = SOUTH; break; //向北
        default: exit(-1);
    }

    return next;
} //转入相邻格点

bool mazefindPath(Cell Maze[MAZE_MAX][MAZE_MAX], Cell* s, Cell* t) {
    stack<Cell*> path; //记录通路的栈
    
    if (s->status != AVAIBLE || t->status != AVAIBLE)
        return false; //s和t不能访问(退化情况),无解
    
    s->incoming = UNKNOWN; s->status = ROUTE;
    path.push(s); //设置起点

    do {
        Cell* c = path.top(); //当前位置,即栈顶元素
        if (c == t)
            return true; //到达目的地
        else {
            while ((c->outgoing = nextDire(c->outgoing)) < NO_WAY) //逐一检查所有方向 
                if (neighbour(c)->status == AVAIBLE) //试图寻找尚未试探过的方向
                    break;
            
            if(c->outgoing < NO_WAY) {
                path.push(c = advance(c)); //向前试探一步
                c->outgoing = UNKNOWN; c->status = ROUTE; //调整新格点状态
            } else { //若所有方向均被试探过
                c->status = BACKTRACKED; //将c标记为 所有方向均试探失败后回溯过的
                path.pop(); //向前回溯一步
            }
        }
    } while (!path.empty());
    return false;
} //在格单元s和t之间找出一条通路(若存在),但不一定最短


int main(int, char**) {
    Cell maze[MAZE_MAX][MAZE_MAX];

    int size;
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            scanf("%d", &maze[i][j].status);
        }
    }

    int sx, sy, tx, ty;
    scanf("%d%d%d%d", &sx, &sy, &tx, &ty);

    printf("%d\n", mazefindPath(maze, &maze[sx][sy], &maze[tx][ty]));
    return 0;
}