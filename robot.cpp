#include "robot.h"
#include "data.h"
#include <bits/stdc++.h>

int Robot::move() {
    if (goods) {
        int min_dis = 114514, dir;
        for (int i = 0; i < berth_num; i++) { //找最近的泊位
            if (direction[x][y][i][1] < min_dis) {
                min_dis = direction[x][y][i][1];
                dir = direction[x][y][i][0];
            }
        }
        //printf("goods: %d %d\n", dir, check(x + mx[dir], y + my[dir]));
        if (check(x + mx[dir], y + my[dir])) {
            vis[x + mx[dir]][y + my[dir]] = 1;
            return dir;
        }
        else {
            for (int i = 0; i < 4; i++) {
                if (i == dir) continue;
                if (check(x + mx[i], y + my[i])) {
                    vis[x + mx[i]][y + my[i]] = 1;
                    return i;
                }
            }
        }
    }
    else {
        int min_dis = 114514, dir_x = -1, dir_y = -1, nx, ny;
        int tot = 0;
        for (int i = mygoods[0].nxt; i; i = mygoods[i].nxt) { //遍历货物
            tot++;
            int cx = mygoods[i].x, cy = mygoods[i].y;
            int cd = abs(cx - x) + abs(cy - y);
            if (cd < min_dis) {
                min_dis = cd, nx = cx - x, ny = cy - y;
                dir_x = (cx - x) < 0 ? 2 : 3;
                dir_y = (cy - y) < 0 ? 1 : 0;
                if (cx - x == 0) dir_x = -1;
                if (cy - y == 0) dir_y = -1;
            }
        }
        //printf("nowgoods: %d %d %d %d\n", dir_x, dir_y, nx, ny);
        int where = rand() % 2;
        if (dir_x != -1 && check(x + mx[dir_x], y + my[dir_x]) && !where) {
            vis[x + mx[dir_x]][y + my[dir_x]] = 1;
            return dir_x;
        }
        else if (dir_y != -1 && check(x + mx[dir_y], y + my[dir_y]) && where) {
            vis[x + mx[dir_y]][y + my[dir_y]] = 1;
            return dir_y;
        }
        else {
            for (int i = 0; i < 4; i++) {
                if (i == dir_x || i == dir_y) continue;
                if (check(x + mx[i], y + my[i])) {
                    vis[x + mx[i]][y + my[i]] = 1;
                    return i;
                }
            }
        }
    }
    return -1; //不移动
}

void Robot::getgoods() { //捡起货物
    if (goods) return;
    if (gds[x][y][0]) {
        goods = gds[x][y][0];
        printf("get %d\n", id);
        del(gds[x][y][1]);
    }
}

void Robot::pullgoods() { //放下货物
    if (goods && ch[x][y] == 'B') {
        int idd = -1;
        for (int i = 0; i < berth_num; i++) {
            int cx = berth[i].x, cy = berth[i].y;
            if (cx <= x && x <= cx + 3 && cy <= y && y <= cy + 3) {
                idd = i; break;
            }
        }
        berth[idd].val += goods;
        goods = 0;
        printf("pull %d\n", id);
    }
}
