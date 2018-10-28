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
	life = 3;
	direc = direction::down;
}
int Player::get_num_i() {
	return num_i;
}
void Player::add_num_i() {
	num_i++;
}
int Player::get_life() {
	return life;
}
void Player::die() {
	if(life > 0)life--;
}
void Player::display() {
	glBindTexture(GL_TEXTURE_2D, texture[player_u + direc]);
	Entity::display(pos_x, pos_y, pos_x + 1, pos_y + 1);
}