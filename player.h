#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Player : public Entity {
private:
	int num_i;
	int life;
public:
	Player();
	Player(int _pos_x, int _pos_y);
	int get_num_i();
	void add_num_i();
	int get_life();
	void die();
	void display();
	static void image_setting() {
		cout << "???" << endl;
	}
};

