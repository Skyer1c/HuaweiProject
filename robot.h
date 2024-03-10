#ifndef ROBOT_H
#define ROBOT_H

class Robot
{
public:
    int x, y, goods, id;
    int status;
    int mbx, mby;
    Robot() {}
    Robot(int startX, int startY) {
        x = startX;
        y = startY;
    }
    int move();
    void getgoods();
    void pullgoods();
};

#endif // ROBOT_H
