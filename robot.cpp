#include "robot.h"
#include "data.h"
#include <bits/stdc++.h>

void Robot::start_searching(int gx, int gy) {
    //printf("start! %d %d\n", gx, gy);
    search_dir.clear();
    while (direction[gx][gy][id][1]) {
        //printf("start: %d %d %d\n", gx, gy, direction[gx][gy][id][1]);
        int dir = direction[gx][gy][id][0];
        gx += mx[dir], gy += my[dir];
        if (dir <= 1) dir = 1 - dir;
        else dir = 5 - dir;
        search_dir.push_front(dir);
    }
    mbx = gx, mby = gy;
    searching = 1, index = 0;
}

void Robot::update() {
    if (goods) { //有货物就一切顺利
        searching = 0; //保证工作
        return;
    }
    if (ch[x][y] == 'B' && !searching) { //在泊位上但是没有货物，就搜索货物
        int mindis = 114514, idd = 1919810;
        int berthid = -1; //保证这是对应的泊位
        for (int i = 0; i < berth_num; i++) {
            int cx = berth[i].x, cy = berth[i].y;
            if (cx <= x && x <= cx + 3 && cy <= y && y <= cy + 3) {
                berthid = i; break;
            }
        }
        if (berthid != id) return;
        for (int i = mygoods[0].nxt; i; i = mygoods[i].nxt) {
            int gx = mygoods[i].x, gy = mygoods[i].y, tim = mygoods[i].tim;
            if (mygoods[i].dis == -1 || !direction[gx][gy][id][1]) continue; //货物被其他机器人预定，或无法到达
            //printf("check_dir\n");
            if (direction[gx][gy][id][1] + 16 <= tim && direction[gx][gy][id][1] < mindis) { //能够在刷新前取得货物
                mindis = direction[gx][gy][id][1];
                idd = i;
            }
        }
        mygoods[idd].dis = -1;
        start_searching(mygoods[idd].x, mygoods[idd].y);
    }
    if (searching == 1 && x == mbx && y == mby) { //已到达泊位起始点
        searching = 2;
    }
    if (searching == 2 && index == search_dir.size()) { //已走完逆向道路
        searching = 0;
    }
    //printf("robot_update: %d %d %d %d %d %d %c\n", id, goods, searching, search_dir.size(), x, y, ch[x][y]);
    //if (searching == 2) printf("searching: %d\n", search_dir.front());
}

int Robot::move() {
    vis[x][y] = 0;
    if (goods || !searching) { //有货物或者没目标，都是前往泊位再决定
        int min_dis = 114514, dir = direction[x][y][id][0]; //直接去对应的泊位
        //printf("goods: %d %d\n", dir, check(x + mx[dir], y + my[dir]));
        if (check(x + mx[dir], y + my[dir])) {
            vis[x + mx[dir]][y + my[dir]] = 1;
            return dir;
        }
        else {
            int rand_dir[5], rand_cnt = 0;
            for (int i = 0; i < 4; i++) {
                if (i == dir) continue;
                if (check(x + mx[i], y + my[i])) {
                    rand_dir[++rand_cnt] = i;
                }
            }
            if (rand_cnt) {
                int i = rand() % rand_cnt + 1;
                i = rand_dir[i];
                vis[x + mx[i]][y + my[i]] = 1;
                return i;
            }
        }
    }
    else if (searching == 1) { //正在前往目标泊位格子
        int delx = mbx - x, dely = mby - y;
        int dir_x = delx < 0 ? 2 : 3, dir_y = dely < 0 ? 1 : 0;
        if (delx == 0) dir_x = -1;
        if (dely == 0) dir_y = -1;
        if (dir_x != -1 && check(x + mx[dir_x], y + my[dir_x])) {
            vis[x + mx[dir_x]][y + my[dir_x]] = 1;
            return dir_x;
        }
        if (dir_y != -1 && check(x + mx[dir_y], y + my[dir_y])) {
            vis[x + mx[dir_y]][y + my[dir_y]] = 1;
            return dir_y;
        }
    }
    else if (searching == 2) { //正在逆序前往货物位置
        int dir = search_dir[index];
        if (check(x + mx[dir], y + my[dir])) {
            vis[x + mx[dir]][y + my[dir]] = 1;
            index++;
            return dir;
        }
        //如果碰壁，前面一定是机器人，此时选择往后退回溯到上一个位置（如果可以）让位
        if (index) { //可以让位
            dir = search_dir[index - 1];
            if (dir <= 1) dir = 1 - dir;
            else dir = 5 - dir;
            if (check(x + mx[dir], y + my[dir])) {
                vis[x + mx[dir]][y + my[dir]] = 1;
                index--;
                return dir;
            }
        }
    }
    vis[x][y] = 1; //不移动的话把这个位置占住
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
