#include <iostream>
using namespace std;

enum direction {up = 0, down, left, right};
//enum map_info { wall, empty, item };
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
		up:return make_pair(pos_x, pos_y+1);
		down:return make_pair(pos_x, pos_y-1);
		left:return make_pair(pos_x-1, pos_y);
		right:return make_pair(pos_x+1, pos_y);
		}
		return make_pair(0, 0);
	}
	void move(int direc) {
		switch (direc) {
		up:
			pos_y++;
			break;
		down:
			pos_y--;
			break;
		left:
			pos_x--;
			break;
		right:
			pos_x++;
			break;
		}
	}
};
class Player : public Entity {
private:
	int direction;
	int num_i;
public:
	Player(int _pos_x, int _pos_y) {
		pos_x = _pos_x;
		pos_y = _pos_y;
		num_i = 0;
		direction = direction::down;
	}
	int get_direction() {
		return direction;
	}
	int get_num_i() {
		return num_i;
	}
	void add_num_i() {
		num_i++;
	}
};
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