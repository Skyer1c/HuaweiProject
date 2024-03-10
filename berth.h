#ifndef BERTH_H
#define BERTH_H

class Berth
{
public:
    int x;
    int y;
    int transport_time;
    int loading_speed;
    int val; //当前泊位货物价值
    Berth(){}
    Berth(int x, int y, int transport_time, int loading_speed) {
        this -> x = x;
        this -> y = y;
        this -> transport_time = transport_time;
        this -> loading_speed = loading_speed;
    }
};

#endif // BERTH_H
