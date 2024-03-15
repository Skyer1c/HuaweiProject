#include <bits/stdc++.h>
#include "robot.h"
#include "data.h"
#include "berth.h"
using namespace std;

void check_goods() {
    for (int i = mygoods[0].nxt; i; i = mygoods[i].nxt) {
        mygoods[i].tim--;
        if (mygoods[i].tim <= 0) del(i);
    }
}

void bfs(int id) { //bfs预处理
    queue<Place> q;
    int x = berth[id].x, y = berth[id].y;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= 3; i++) {
        q.push(Place(x, y + i, 0)), q.push(Place(x + 3, y + i, 0));
        vis[x][y + i] = vis[x + 3][y + i] = 1;
    }
    for (int i = 1; i <= 2; i++) {
        q.push(Place(x + i, y, 0)), q.push(Place(x + i, y + 3, 0));
        vis[x + i][y] = vis[x + i][y + 3] = 1;
    }
    while (!q.empty()) {
        Place cur = q.front(); q.pop();
        int cx = cur.x, cy = cur.y, cd = cur.dis;
        for (int i = 0; i < 4; i++) {
            int nx = cx + mx[i], ny = cy + my[i], back_dir;
            if (i <= 1) back_dir = 1 - i;
            else back_dir = 5 - i;
            if (!check(nx, ny)) continue;
            vis[nx][ny] = 1, direction[nx][ny][id][0] = back_dir, direction[nx][ny][id][1] = cd + 1;
            q.push(Place(nx, ny, cd + 1));
            //printf("111\n");
        }
    }
}

void robot_to_berth() {
    static int flag = 0;
    if (flag) return;
    flag = 1;
    int choice[robot_num + 10], chosen[berth_num + 10];
    //试行版泊位挑选机器人
    for (int i = 0; i < robot_num; i++) {
        robot[i].id = i;
        int x = robot[i].x, y = robot[i].y;
        choice[i] = 0;
        for (int j = 0; j < berth_num; j++) {
            if (direction[x][y][j][1]) choice[i]++;
        }
    }
    for (int i = 0; i < berth_num; i++) chosen[i] = 0;
    int b = 0;
    while (b < berth_num) {
        int bid = 114514, mincost = 1919810;
        for (int i = 0; i < berth_num; i++) { //综合排序泊位
            if (chosen[i]) continue;
            int curcost = boat_capacity / berth[i].loading_speed + berth[i].transport_time;
            if (curcost < mincost) {
                mincost = curcost, bid = i;
            }
        }
        chosen[bid] = 1;
        int tot = 0;
        while (tot < 2) {
            int rid = 114514, minchoice = 1919810;
            for (int i = 0; i < robot_num; i++) {
                int x = robot[i].x, y = robot[i].y;
                if (robot[i].bid || !direction[x][y][bid][1]) continue;
                if (choice[i] < minchoice) { //让可选泊位少的机器人先选
                    rid = i, minchoice = choice[i];
                }
            }
            if (rid != 114514) {
                robot[rid].bid = bid;
                tot++;
            }
            else break;
        }
        b++;
    }
}

void Init()
{
    for(int i = 0; i < n; i ++) { //地图
        scanf("%s", ch[i]);
        //printf("%s\n", ch[i]);
    }
        
    for(int i = 0; i < berth_num; i ++) //泊位
    {
        int id;
        scanf("%d", &id);
        scanf("%d%d%d%d", &berth[id].x, &berth[id].y, &berth[id].transport_time, &berth[id].loading_speed);
        //printf("%d %d %d %d %d\n", id, berth[id].x, berth[id].y, berth[id].transport_time, berth[id].loading_speed);
        bfs(id);
    }
    scanf("%d", &boat_capacity); //船的容量
    for (int i = 0; i < 5; i++) boat[i].num = i;
    //cout << boat_capacity << ' ' << n << endl;
    char okk[100];
    scanf("%s", okk);
    //cout << okk << endl;
    printf("OK\n");
    fflush(stdout);
}

int Input() //每次交互输入
{
    int id;
    scanf("%d%d", &id, &money);
    int num;
    scanf("%d", &num);
    for(int i = 1; i <= num; i ++) //货物
    {
        int x, y, val;
        scanf("%d%d%d", &x, &y, &val);
        add(x, y, val);
    }
    for(int i = 0; i < robot_num; i ++) //机器人
    {
        int sts;
        scanf("%d%d%d%d", &robot[i].goods, &robot[i].x, &robot[i].y, &sts);
        vis[robot[i].x][robot[i].y] = 1;
    }
    robot_to_berth();
    for(int i = 0; i < 5; i ++) //船
        scanf("%d%d\n", &boat[i].status, &boat[i].pos);
    char okk[100];
    scanf("%s", okk);
    return id;
}

int main()
{
    // freopen("output.txt", "r", stdin);
    // freopen("test.txt", "w", stdout);
    Init();
    for(int zhen = 1; zhen <= 15000; zhen ++)
    {
        memset(vis, 0, sizeof(vis));
        
        int id = Input();
        // printf("id: %d\n", id);
        for(int i = 0; i < robot_num; i ++) {
            robot[i].getgoods(); //尝试获取货物
            robot[i].pullgoods(); //尝试放下货物
            robot[i].update();
            //printf("nowid: %d %d\n", i, robot[i].id);
            int dir = robot[i].move();
            if (dir != -1) printf("move %d %d\n", i, dir); //尝试移动
            robot[i].getgoods(); //尝试获取货物
            robot[i].pullgoods(); //尝试放下货物
            robot[i].update();
        }
        for (int i = 0; i < 5; i++) { // 遍历船只状态
            if (boat[i].working(zhen)) { //处于航行状态
                // printf("111\n");
                boat[i].update(zhen); //更新航行状态
                // printf("111_end\n");
            }
            else if (boat[i].available()) { //处于闲置状态
                // printf("222\n");
                boat[i].start_ship(zhen); //开始航行去往一个泊位
                // printf("222_end\n");
                //printf("cango\n");
            }
            else if (boat[i].filled_flag()) { //货物已装满
                // printf("333\n");
                boat[i].start_go(zhen);
                // printf("333_end\n");
                printf("go %d\n", i); //去运货
            }
            else { //处于装货状态
                // printf("wait_loading: %d %d\n", i, boat[i].current_capacity());
                if (15000 - (zhen + berth[boat[i].pos].transport_time) <= 5) { //最后一次运货判断
                    boat[i].start_go(zhen);
                    printf("go %d\n", i); //去运货
                }
            }
        }
        
        for (int i = 0; i < berth_num; i++) { //遍历泊位状态
            berth[i].loading(); //尝试运货
        }
        puts("OK");
        fflush(stdout);
        check_goods(); //更新货物信息
    }
    
    return 0;
}
