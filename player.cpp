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
	float s = 0.25;
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
}

void Player::display() {
	int index;
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
	mat4 scale = glm::scale(glm::mat4(1.0), vec3(0.01f, 0.01f, 0.01f));
	mat4 y_z = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, 0));
	mat4 rot = glm::rotate(glm::mat4(1.0), 3.14f, vec3(0.0, 0.0, 1.0)) * glm::rotate(glm::mat4(1.0), 1.57f*mul, vec3(0.0, 0.0, 1.0));
	mat4 final_mat = per_look * trans*rot* y_z *scale;// *rot * scale;
	vec4 vec_color;

	index = (4 - jump) % 4;
	if (gun == true) {
		int g_index = GUN;
		gun = false;
		mat4 gun_trans = glm::translate(glm::mat4(1.0), hand_loc) *glm::scale(glm::mat4(1.0), vec3(3.0f, 3.0f, 3.0f));
		mat4 gun_final_mat = final_mat * gun_trans;
		vec4 vec_color = GUN_COLOR;
		glBindVertexArray(vao[g_index]);
		glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &gun_final_mat[0][0]);
		glUniform4fv(vColor, 1, &vec_color[0]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, vao_size[g_index]);
		index = P_GUN;
	}
	glBindVertexArray(vao[index]);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	
	vec_color = BACK_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);

	vec_color = PLAYER_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);

	if (jump != 0) {
		jump--;
		this->move();
	}
}
int Player::get_life() {
	return life;
}
void Player::die() {
	if (life > 0)life--;
}