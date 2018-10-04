#pragma once
#include <iostream>
using namespace std;
enum direction { up = 0, down, left, right };

class Entity {
public:
	int pos_x;
	int pos_y;
	int get_x();
	int get_y();
	pair<int, int> get_position();
	pair<int, int> move_test(int direc);
	void move(int direc);
};