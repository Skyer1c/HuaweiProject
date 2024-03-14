#include "boat.h"
#include "data.h"

int Boat::current_capacity() {//返回当前时刻船上的货物数量
	return curgoods;
}

void Boat::load(int x) {//装载货物
	sumval += x;
	curgoods += 1;
}

void Boat::filled() {
	if (curgoods == boat_capacity) {
		if_filled = true;
	}
	else {
		if_filled = false;
	}
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

bool Boat::working() {
	if (status==0) {//目的地为虚拟点且装载货物 或 目的地为泊位且未装载货物
		return true;
	}
	else return false;
}

void Boat::start_ship(int x) {
	for (int i = 0; i < berth_num; i++) { //泊位
		if (!occupy[i] && berth[i].val) {//泊位上没船且有货
			for (int j = 0; j < 5; j++) {
				if (boat[j].pos != i) {//没有其他船正在前往这个泊位，保证没有冲突
					pos = i;
					berth[i].cur_ship = num;//视为该泊位已被这艘船占据
					status = 0;
					arrival_time = x + berth[i].transport_time;//记录预计到达目的地的时刻
				}
			}
		}
	}
}

void Boat::start_go(int x) {
	if (curgoods == boat_capacity && status == 1) {//刚好在泊位处装满货物
		status = 0;//变为航行
		berth[pos].cur_ship = -1;//泊位空出
		pos = -1;//目的地为虚拟点
		arrival_time = x + berth[pos].transport_time;//记录预计到达时间
	}
}

void Boat::update(int x) {
	if (x == arrival_time) {//判断是否到达
		status = 1;//从航行状态变成正常运行状态
		if (pos != -1) {//到达泊位
			berth[pos].cur_ship = num;//占据泊位
		}
		else {
			money += sumval;//到达了虚拟点，瞬间产生价值
			sumval = 0;
			curgoods = 0;//清空货物
		}
	}
}
