#pragma once
#include <iostream>
using namespace std;
enum direction { up = 0, down, left, right };

class Entity {
public:
	int pos_x;
	int pos_y;
	int get_x() {
		return pos_x;
	}
	int get_y() {
		return pos_y;
	}
	pair<int, int> get_position() {
		return make_pair(pos_x, pos_y);
	}
	pair<int, int> move_test(int direc) {
		switch (direc) {
			case direction::up:
				return make_pair(pos_x, pos_y + 1);
			case direction::down:
				return make_pair(pos_x, pos_y - 1);
			case direction::left:
				return make_pair(pos_x - 1, pos_y);
			case direction::right:
				return make_pair(pos_x + 1, pos_y);
		}
		return make_pair(-1, -1);
	}
	void move(int direc) {
		switch (direc) {
			case direction::up:
			pos_y++;
			break;
			case direction::down:
			pos_y--;
			break;
			case direction::left:
			pos_x--;
			break;
			case direction::right:
			pos_x++;
			break;
		}
	}
};