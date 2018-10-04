#pragma once
#include <iostream>
#include "Entity.h"
#include "Bullet.h"
using namespace std;

Bullet::Bullet(int _pos_x, int _pos_y, int _direction, int _length) {
	pos_x = _pos_x;
	pos_y = _pos_y;
	direc = _direction;
	move();
	length = _length + 1;
}
pair<int, int> Bullet::move_test() {
	return Entity::move_test(direc);
}
bool Bullet::move() {
	if (length == 0) return false;
	Entity::move(direc);
	length--;
	return true;
}
void Bullet::display() {
	glBindTexture(GL_TEXTURE_2D, texture[bullet_u + direc]);
	Entity::display(pos_x, pos_y, pos_x + 1, pos_y + 1);
}