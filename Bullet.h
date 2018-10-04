#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Bullet : public Entity {
private:
	int direction;
	int length;
public:
	Bullet(int _pos_x, int _pos_y, int _direction, int _length);
	int get_direction();
	pair<int, int> move_test();
	bool move();
};