#include <bits/stdc++.h>
#include "berth.h"
#include "robot.h"
#include "data.h"
//伪代码

Berth::Berth() { //初始化
    cur_boat = -1;
}

void Berth::update_goods(int val){
    berth_value.push(val);//将当前机器人货物的价值存入队列
    tot_val += val; //加入总价值
}

void Berth::update_boat(int boat_id){ //由船给它信息
    cur_boat = boat_id;
    // printf("update_boat_berth: %d\n", cur_boat);
}

void Berth::loading(){
    // printf("boat %d\n", cur_boat);
    if (cur_boat != -1) {//当前泊位有船
        Boat &cur = boat[cur_boat];
        // printf("cur_boat: %d %d\n", cur_boat, cur.current_capacity());
        for (int i = 1; i <= loading_speed; i++) {//每一帧按照泊位速度装载货物
            if (berth_value.empty()) break;                
            int temp_val=berth_value.front();
            if (cur.current_capacity() + 1 <= boat_capacity) {//轮船未满时就装载货物
                cur.load(temp_val);
                berth_value.pop();
                tot_val -= temp_val;
            }
            else {
                cur.filled(); //装满信号
                break;//此时船装满了，停止装载（可能要返回一些指示信息？）
            }
        }
        if (berth_value.empty()) cur.filled(); //没东西了让船先走
    }
}

int Berth::boat_flag() {
    return cur_boat;
}

int Berth::goods_flag() {
    return berth_value.size();
}

/*
想法：当时间快结束时在轮船未装满时提前让其离开，在计时结束之前产生价值避免浪费
*/

/*
你可以写一下泊位的货物存储，和当船来装货的时候的货物变化
逻辑是机器人到泊位后放下货物，应该要存下货物的价值，存到一个队列里，
然后船来装货的时候货物依次先进后出，装货是有cd的，就是多少帧搬一个，大概实现这些东西
*/

/*3.2轮船和泊位机制
轮船和泊位之间有到达、装载、驶离三种动作。每一帧在泊位处将依次执行到达、驶
离、装载三种动作。
当两个轮船在同一帧到达同一泊位时，先输入指令的轮船先进入泊位。对于另一艘轮
船，选手可以选择不输入指令，继续在泊位等待，当泊位空闲时到达泊位，也可以选
择输入移动、运输指令，移动到其他泊位或者移动到虚拟点。
由于不考虑轮船路径规划，我们假定泊位间的移动时间都是 500 帧(10s)，判题器将告
知选手轮船从每个泊位运输产生价值的时间。选手可以随时操控轮船进行运输或移
位。轮船结束运输产生价值的帧时刻，选手可以执行 ship 指令把轮船从虚拟点移动到
一个空闲的泊位上。
*/

/*
泊位数据是由 10 行 5 列数字组成。
每一行五个整数 id, x, y, time, velocity 表示一个泊位。id(0 <= id < 10)为该泊位的唯一标
号，(x,y)表示该泊位的左上角坐标,time(1 <= time <= 1000)表示该泊位轮船运输到虚拟
点的时间(虚拟点移动到泊位的时间同)，即产生价值的时间，时间用帧数表示。
Velocity(1 <= Velocity <= 5)表示该泊位的装载速度，即每帧可以装载的物品数，单位
是：个。保证对于每次提交全部泊位到虚拟点时间和相同。
*/