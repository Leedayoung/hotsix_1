#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

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
};