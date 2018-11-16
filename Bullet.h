#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Bullet : public Entity {
private:
	int length;
public:
	Bullet() {}
	Bullet(float _pos_x, float _pos_y, int _direction, int _length);
	pair<float, float> move_test();
	pair<int, int> move_test2();
	bool move();
	void display();
};