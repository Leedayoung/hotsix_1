#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Bullet : public Entity {
private:
	int direction;
	int length;
public:
	Bullet(int _pos_x, int _pos_y, int _direction,int _length) {
		pos_x = _pos_x;
		pos_y = _pos_y;
		direction = _direction;
		move();
		length = _length+1;
	}
	int get_direction() {
		return direction;
	}
	pair<int, int> move_test() {
		return Entity::move_test(direction);
	}
	bool move() {
		if (length == 0) return false;
		Entity::move(direction);
		length--;
		return true;
	}
};