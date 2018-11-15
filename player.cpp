#pragma once
#include <iostream>
#include "Entity.h"
#include "player.h"
#include "display.h"
#include <vector>
using namespace std;

Player::Player() {}
Player::Player(int _pos_x, int _pos_y) {
	pos_x = (float)_pos_x;
	pos_y = (float)_pos_y;
	num_i = 0;
	direc = direction::down;
}
int Player::get_num_i() {
	return num_i;
}
void Player::add_num_i() {
	num_i++;
}
void Player::move() {
	float s = 1;
	switch (direc) {
	case direction::up:
		pos_y += s;
		break;
	case direction::down:
		pos_y -= s;
		break;
	case direction::left:
		pos_x -= s;
		break;
	case direction::right:
		pos_x += s;
		break;
	}
	printf("Move : %lf %lf\n", pos_x, pos_y);
}

void Player::display() {
	glBindVertexArray(vao[0]);
	float mul;
	switch (direc) {
		case direction::up:
			mul = 2;
			break;
		case direction::down:
			mul = 0;
			break;
		case direction::left:
			mul = 3;
			break;
		case direction::right:
			mul = 1;
			break;
	}
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, -5));
	mat4 scale = glm::scale(glm::mat4(1.0), vec3(0.1f, 0.01f, 0.1f));
	mat4 rot = glm::rotate(glm::mat4(1.0), 1.57f*mul, vec3(0.0, 0.0, 1.0))*glm::rotate(glm::mat4(1.0), 1.57f, vec3(1.0, 0.0, 0.0));
	mat4 final_mat = per_look * trans * rot * scale;
	vec4 vec_color = vec4(1.0, 0.0, 0.0, 0.5);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[0]);

	/*treenode * player_direc;
	switch (direc) {
	case direction::down:
		player_direc = player_down;
		break;
	case direction::up:
		player_direc = player_up;
		break;
	case direction::left:
	case direction::right:
		player_direc = player_left;
		break;
	default:
		player_direc = player_down;
		break;
	}
	if (direc == direction::right)
		model_view = ortho_mat * glm::translate(mat4(1.0), glm::vec3(pos_x + 1.5, pos_y, 0))* scale(glm::mat4(1.0), vec3(-2, 2, 0));
	else
		model_view = ortho_mat * glm::translate(mat4(1.0), glm::vec3(pos_x-0.5, pos_y, 0))*scale(glm::mat4(1.0), vec3(2, 2, 0));
	if (gun == true) {
		gun = false;
		traverse(player_direc, 4);
	}
	else if (jump != 0) {
		traverse(player_direc, jump);
		jump--;
		this->move();
	}
	else {
		traverse(player_direc, 0);
	}

	*/
}
int Player::get_life() {
	return life;
}
void Player::die() {
	if (life > 0)life--;
}