#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
using namespace std;

class Enemy : public Entity {
public:
	Enemy(int _pos_x, int _pos_y);
	void move() {
		switch (direc) {
		case direction::up:
			pos_y += 0.25;
			break;
		case direction::down:
			pos_y -= 0.25;
			break;
		case direction::left:
			pos_x -= 0.25;
			break;
		case direction::right:
			pos_x += 0.25;
			break;
		}
	}
	bool check_chase(pair<int, int> player_pos);
	void display();
};