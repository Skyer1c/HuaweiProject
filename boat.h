#ifndef BOAT_H
#define BOAT_H
#include<stack>

class Boat
{
public:
    int num;//当前船只编号
    int pos, status;//目的地和状态
    int arrival_time;//预计到达目的地的时间点
    int sumval;//当前时刻船上货物总价值
    int curgoods;//当前时刻船上货物数量
    bool if_filled;//信号，真则船上装满货物
    
    void load(int x);//装载一个价值为x的货物
    int current_capacity();//返回当前时刻船上的货物数量 
    void filled();//改变船的状态，使其从未装满状态更新为装满状态
    bool filled_flag();//返回一个信号，真则船已经载满货物
    bool available();//返回一个信号，真则船处于空闲状态
    bool working(int x);//返回一个信号，真则船处于运输状态
    void start_ship(int x);//执行start_ship，读取执行start_ship指令的时间点
    void start_go(int x);//执行go_ship，读取执行go_ship指令的时间点
    void update(int x);//读取当前时刻，准备与arrival_time比较，更新航行状态
};

#endif // BOAT_H
