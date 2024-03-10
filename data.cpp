#include "data.h"

char ch[N][N];
int money, boat_capacity;
int gds[N][N][2];
int vis[N][N];
int occupy[berth_num + 10];
int direction[N][N][berth_num + 10][2]; //预处理每个格子到泊位的最短路径以及距离
int mx[4] = {0, 0, -1, 1}, my[4] = {1, -1, 0, 0};
int cnt;

Robot robot[robot_num + 10];
Berth berth[berth_num + 10];
Boat boat[10];
Place mygoods[150015];

bool check(int x, int y) {
    if (x < 0 || x >= 200 || y < 0 || y >= 200) return false;
    else if (vis[x][y] || ch[x][y] == '#' || ch[x][y] == '*') return false;
    return true;
}

void add(int x, int y, int val) { //储存货物信息
    int head = mygoods[0].nxt;
    mygoods[++cnt] = Place(x, y, val, 0, head);
    mygoods[0].nxt = mygoods[head].pre = cnt;
    gds[x][y][0] = val, gds[x][y][1] = cnt; //在地图上记录信息
}

void del(int id) { //删除货物信息
    mygoods[mygoods[id].pre].nxt = mygoods[id].nxt;
    mygoods[mygoods[id].nxt].pre = mygoods[id].pre;
    gds[mygoods[id].x][mygoods[id].y][0] = 0; //在地图上删除货物信息
}
