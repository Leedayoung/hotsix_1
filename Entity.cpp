#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;
GLuint texture[16];

int Entity::get_x() {
	return pos_x;
}
int Entity::get_y() {
	return pos_y;
}
pair<int, int> Entity::get_position() {
	return make_pair(pos_x, pos_y);
}
pair<int, int> Entity::move_test(int direc) {
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
void Entity::move(int direc) {
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
void Entity::display(int x1, int y1, int x2, int y2) {
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(x1, y1);
	glTexCoord2i(1, 0); glVertex2i(x2, y1);
	glTexCoord2i(1, 1); glVertex2i(x2, y2);
	glTexCoord2i(0, 1); glVertex2i(x1, y2);
	glEnd();
}