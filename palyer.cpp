#pragma once
#include <iostream>
#include "Entity.h"
#include "player.h"
#include "display.h"
using namespace std;

Player::Player() {}
Player::Player(int _pos_x, int _pos_y) {
	pos_x = _pos_x;
	pos_y = _pos_y;
	num_i = 0;
	direc = direction::down;
}
int Player::get_num_i() {
	return num_i;
}
void Player::add_num_i() {
	num_i++;
}
void Player::draw_down() {
	/*int pos_x;
	int pos_y;*/
	//glm::mat4 myMatrix = glm::translate(glm::mat4(), glm::vec3(pos_x, pos_y, 0.0f));

}
void Player::display() {
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, 0));
	mat4 final_mat = ortho_mat * trans;
	vec4 vec_color = vec4(0.0, 0.0, 1.0, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	/*
	glBindTexture(GL_TEXTURE_2D, texture[player_u + direc]);
	Entity::display(pos_x, pos_y, pos_x + 1, pos_y + 1);*/
	//enum direction { up = 0, down, left, right };
	/*switch (direc) {
		case direction::up:
			break;
		case direction::down:
			draw_down();
			break;
		case direction::left:
			break;
		case direction::right:
			break;
	}*/
}