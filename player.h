#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Player : public Entity {
private:
	int direction;
	int num_i;
public:
	Player() {}
	Player(int _pos_x, int _pos_y) {
		pos_x = _pos_x;
		pos_y = _pos_y;
		num_i = 0;
		direction = direction::down;
	}
	int get_direction() {
		return direction;
	}
	int set_direction(int dir) {
		direction = dir;
	}
	int get_num_i() {
		return num_i;
	}
	void add_num_i() {
		num_i++;
	}
};

