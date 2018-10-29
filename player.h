#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Player : public Entity {
private:
	int num_i;
	
	bool gun = false;
public:
	Player();
	void move();
	Player(int _pos_x, int _pos_y);
	int get_num_i();
	void add_num_i();
	void display();
	void set_gun(bool _gun) {
		gun = _gun;
	}
	bool get_gun() {
		return gun;
	}
	
	static void image_setting() {
		cout << "???" << endl;
	}
};

