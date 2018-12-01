#pragma once
#include <iostream>
#include "Entity.h"
#include "display.h"
using namespace std;

class Player : public Entity {
private:
	int num_i;
	int life = 3;
	bool gun = false;
public:
	Player();
	void move();
	Player(int _pos_x, int _pos_y);
	int get_num_i();
	void add_num_i();
	void use_all_jump();
	void set_life(int _life) {
		life = _life;
	}
	int get_life();
	void die();
	void display();
	void set_gun(bool _gun) {
		gun = _gun;
	}
	bool get_gun() {
		return gun;
	}
	void set_direction(int direc) {
		Entity::set_direction(direc);

		switch (direc) {
		case direction::up:
			point_light_dir = vec3(0.0, 1.0, 0.0);
			break;
		case direction::down:
			point_light_dir = vec3(0.0, -1.0, 0.0);
			break;
		case direction::left:
			point_light_dir = vec3(-1.0, 0.0, 0.0);
			break;
		case direction::right:
			point_light_dir = vec3(1.0, 0.0, 0.0);
			break;

		}
	}
};

