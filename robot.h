#ifndef ROBOT_H
#define ROBOT_H
#include <deque>
using namespace std;

class Robot
{
public:
    int x, y, goods, id, bid, goods_value;
    int searching, index; //是否正在逆序寻找货物 0否 1前往泊位精确格子 2正在逆序 index: 当前方向
    int status;
    int mbx, mby; //泊位目标格子
    deque<int> search_dir;
    Robot() {}
    Robot(int startX, int startY) {
        x = startX;
        y = startY;
    }
    int move();
    void getgoods();
    void pullgoods();
    void start_searching(int gx, int gy); //获得逆序货物路径
    void update(); //更新寻路状态
};

#endif // ROBOT_H
