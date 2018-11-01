#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Bullet : public Entity {
private:
	int length;
public:
	Bullet(float _pos_x, float _pos_y, int _direction, int _length);
	pair<int, int> move_test();
	bool move();
	void display();
};