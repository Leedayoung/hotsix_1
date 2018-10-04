#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
using namespace std;

class Enemy : public Entity {
private:
	bool player;
public:
	Enemy(int _pos_x, int _pos_y);
	void set_player(bool _player);
	void move(int direc);
	bool check_chase(pair<int, int> player_pos);
	void display();
};