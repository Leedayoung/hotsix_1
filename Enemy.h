#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
using namespace std;

class Enemy : public Entity {
public:
	Enemy(int _pos_x, int _pos_y);
	int s = 1;
	void move() {
		switch (direc) {
		case direction::up:
			pos_y += s;
			break;
		case direction::down:
			pos_y -= s;
			break;
		case direction::left:
			pos_x -= s;
			break;
		case direction::right:
			pos_x += s;
			break;
		}
	}
	bool check_chase(pair<int, int> player_pos);
	void display();
};