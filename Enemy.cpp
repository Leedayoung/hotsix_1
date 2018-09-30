#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Enemy.h"
using namespace std;

Enemy::Enemy(int _id, int _pos_x, int _pos_y) {
	id = _id;
	pos_x = _pos_x;
	pos_y = _pos_y;
	player = false;
	direc = direction::down;
}
int Enemy::get_id() {
	return id;
}
void Enemy::set_player(bool _player) {
	player = _player;
}
void Enemy::move(int _direc) {
	direc = _direc;
	Entity::move(_direc);
}
int  Enemy::get_direction() {
	return direc;
}
bool Enemy::check_chase(pair<int, int> player_pos) {
	int player_x = player_pos.first;
	int player_y = player_pos.second;
	int chase_distance = 5;
	if (abs(player_x - pos_x) < chase_distance || abs(player_y - pos_y) < chase_distance) 
		return true;
	else 
		return false;
}
