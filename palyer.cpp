#pragma once
#include <iostream>
#include "Entity.h"
#include "player.h"
using namespace std;

Player::Player() {}
Player::Player(int _pos_x, int _pos_y) {
	pos_x = _pos_x;
	pos_y = _pos_y;
	num_i = 0;
	direction = direction::down;
}
int Player::get_direction() {
	return direction;
}
void Player::set_direction(int dir) {
	direction = dir;
	return;
}
int Player::get_num_i() {
	return num_i;
}
void Player::add_num_i() {
	num_i++;
}