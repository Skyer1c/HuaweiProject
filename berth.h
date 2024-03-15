#ifndef BERTH_H
#define BERTH_H
#include <queue>
using namespace std;


class Berth
{
public:
    int x;//泊位左上顶点的位置
    int y;
    int transport_time;//该泊位轮船运输到虚拟点的时间(虚拟点移动到泊位的时间同)，即产生价值的时间
    int loading_speed;//Velocity(1 <= Velocity <= 5)表示该泊位的装载速度，即每帧可以装载的物品数，单位是：个
    int cur_boat;//当前停靠船只的id,没有船则为-1
    int tot_val;
    queue<int> berth_value;//用来存储泊位当前存放货物价值
    int move_time;//泊位之间移动的用时，都为500帧，暂时没用
    Berth();
    Berth(int x, int y, int transport_time, int loading_speed) {
        this -> x = x;
        this -> y = y;
        this -> transport_time = transport_time;
        this -> loading_speed = loading_speed;
    }
    void update_goods(int val);
    void update_boat(int boat_id = -1);
    void loading();
    int boat_flag();
    int goods_flag();

};

#endif // BERTH_H
