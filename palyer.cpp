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
	direc = direction::down;
}
void Player::set_direction(int dir) {
	direc = dir;
	return;
}
int Player::get_num_i() {
	return num_i;
}
void Player::add_num_i() {
	num_i++;
}
void Player::display() {
	glBindTexture(GL_TEXTURE_2D, texture[player_u + direc]);
	Entity::display(pos_x, pos_y, pos_x + 1, pos_y + 1);
}