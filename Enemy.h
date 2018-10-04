#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
using namespace std;

class Enemy : public Entity {
public:
	Enemy(int _pos_x, int _pos_y);
	void move(int direc);
	bool check_chase(pair<int, int> player_pos);
	void display();
};