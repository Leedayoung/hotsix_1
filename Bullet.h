#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Bullet : public Entity {
private:
	int direction;
public:
	Bullet(int _pos_x, int _pos_y, int _direction) {
		pos_x = _pos_x;
		pos_y = _pos_y;
		direction = _direction;
		move();
	}
	int get_direction() {
		return direction;
	}
	pair<int, int> move_test() {
		return Entity::move_test(direction);
	}
	void move() {
		Entity::move(direction);
	}
};