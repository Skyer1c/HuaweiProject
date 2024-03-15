#include "boat.h"
#include "data.h"
#include <iostream>

int Boat::current_capacity() {//返回当前时刻船上的货物数量
	return curgoods;
}

void Boat::load(int x) {//装载货物
	sumval += x;
	curgoods += 1;
}

void Boat::filled() {
	if_filled = true;
}

bool Boat::filled_flag() {
	if (if_filled) {
		return true;
	}
	else return false;
}

bool Boat::available() {
	if (curgoods == 0 && pos == -1) {//刚送完上一单，货物已结算但目标仍是虚拟点
		return true;
	}
	else return false;
}

bool Boat::working(int x) {
	// printf("working: %d %d %d %d\n", num, x, arrival_time, curgoods);
	if (x <= arrival_time) {//目的地为虚拟点且装载货物 或 目的地为泊位且未装载货物
		return true;
	}
	else return false;
}

void Boat::start_ship(int x) {
	int maxgoods = -114514, bid;
	for (int i = 0; i < berth_num; i++) { //泊位
		if (berth[i].boat_flag() == -1 && berth[i].goods_flag()) {//泊位上没船且有货
			int flag = 1;
			for (int j = 0; j < 5; j++) {
				if (boat[j].pos == i) {//没有其他船正在前往这个泊位，保证没有冲突
					flag = 0;
					break;
				}
			}
			if (flag && berth[i].tot_val > maxgoods) {
				maxgoods = berth[i].tot_val;
				bid = i;
			}
		}
	}
	if (maxgoods != -114514) {
		pos = bid;
		status = 0;
		arrival_time = x + berth[bid].transport_time;//记录预计到达目的地的时刻
		printf("ship %d %d\n", num, pos);
	}
}

void Boat::start_go(int x) {
	status = 0;//变为航行
	berth[pos].update_boat();//泊位空出
	arrival_time = x + berth[pos].transport_time;//记录预计到达时间
	pos = -1;//目的地为虚拟点
}

void Boat::update(int x) {
	//printf("update_boat: %d %d\n", x, arrival_time);
	if (x == arrival_time) {//判断是否到达
		status = 1;//从航行状态变成正常运行状态
		if (pos != -1) {//到达泊位
			berth[pos].update_boat(num);//占据泊位
			if_filled = false;
		}
		else {
			money += sumval;//到达了虚拟点，瞬间产生价值
			sumval = 0;
			curgoods = 0;//清空货物
		}
	}
}
