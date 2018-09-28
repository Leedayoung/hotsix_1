#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
using namespace std;

int chase_distance = 5;

class Enemy : public Entity {
private:
	int id;
	bool player;
public:
	Enemy(int _id, int _pos_x, int _pos_y) {
		id = _id;
		pos_x = _pos_x;
		pos_y = _pos_y;
		player = false;
	}
	int get_id() {
		return id;
	}
	void set_player(bool _player) {
		player = _player;
	}
	void move(int direc) {
		Entity::move(direc);
	}
	bool check_chase(pair<int,int> player_pos) {
		int player_x = player_pos.first;
		int player_y = player_pos.second;
		if (abs(player_x - pos_x) < chase_distance && abs(player_y - pos_y) < chase_distance) return true;
		else return false;
	}
};