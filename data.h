#ifndef DATA_H
#define DATA_H
#include "robot.h"
#include "berth.h"
#include "boat.h"

const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;

extern char ch[N][N];
extern int money, boat_capacity;
extern int gds[N][N][2];
extern int vis[N][N];
extern int occupy[berth_num + 10];
extern int direction[N][N][berth_num + 10][2]; //预处理每个格子到泊位的最短路径以及距离
extern int mx[4], my[4];
extern int cnt;

extern Robot robot[robot_num + 10];
extern Berth berth[berth_num + 10];
extern Boat boat[10];

bool check(int x, int y);

struct Place {
    int x, y, dis, tim, pre, nxt;
    Place(int xx, int yy, int dd) {
        x = xx, y = yy, dis = dd;
        tim = pre = nxt = 0;
    }
    Place(int xx, int yy, int dd, int pp, int nn) {
        tim = 1000; //持续1000帧时间
        x = xx, y = yy, dis = dd, pre = pp, nxt = nn;
    }
    Place() {}
};

extern Place mygoods[150015];

void add(int x, int y, int val); //储存货物信息

void del(int id); //删除货物信息


#endif // DATA_H
