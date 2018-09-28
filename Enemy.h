#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
using namespace std;

extern int chase_distance;

class Enemy : public Entity {
private:
	int id;
	bool player;
	int chase_distance;
public:
	Enemy(int _id, int _pos_x, int _pos_y);
	int get_id();
	void set_player(bool _player);
	void move(int direc);
	bool check_chase(pair<int, int> player_pos);
};