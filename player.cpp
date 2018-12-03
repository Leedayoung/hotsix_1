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

	point_light_loc = vec3(pos_x, pos_y, 1.0);
	point_light_dir = vec3(0.0, 1.0, 0.0);
}
int Player::get_num_i() {
	return num_i;
}
void Player::add_num_i() {
	num_i++;
}
void Player::use_all_jump() {
	switch (direc) {
	case direction::up:
		pos_y += jump * 0.25;
		break;
	case direction::down:
		pos_y -= jump * 0.25;
		break;
	case direction::left:
		pos_x -= jump * 0.25;
		break;
	case direction::right:
		pos_x += jump * 0.25;
		break;
	}
	jump = 0;
	return;
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
	//point_light_loc = vec3(pos_x, pos_y, 1.0);
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
	glUseProgram(light_program);

	mat4 scale = glm::scale(glm::mat4(1.0), vec3(0.01f, 0.01f, 0.01f));
	mat4 y_z = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, 0));
	mat4 rot = glm::rotate(glm::mat4(1.0), 3.14f, vec3(0.0, 0.0, 1.0)) * glm::rotate(glm::mat4(1.0), 1.57f*mul, vec3(0.0, 0.0, 1.0));
	mat4 view_mat = rot* y_z;
	mat4 view_mat_pos = trans * rot * y_z * scale;
	mat4 final_mat = per_look * trans * rot * y_z * scale;// *rot * scale;
	vec4 vec_color = vec4(0.225, 0.9, 0.9, 1.0);
	vec4 ambient_color = vec4(0.06, 0.24, 0.24, 1.0);
	mat4 inv_view_mat = inverse(view_mat_pos);
	mat4 MVI = transpose(inv_view_mat);
	mat3 normal_mtx = mat3(MVI);

	index = (4 - jump) % 4;
	if (gun == true) {
		int g_index = GUN;
		gun = false;
		mat4 gun_trans = glm::translate(glm::mat4(1.0), hand_loc) *glm::scale(glm::mat4(1.0), vec3(3.0f, 3.0f, 3.0f));
		mat4 gun_rot = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, -1.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
		mat4 gun_view_mtx = view_mat_pos*gun_trans* gun_rot;
		mat4 gun_final_mat = final_mat * gun_trans* gun_rot;
		mat4 gun_inv_view_mat = inverse(gun_view_mtx);
		mat4 gun_MVI = transpose(gun_inv_view_mat);
		mat3 gun_normal_mtx = mat3(gun_MVI);
		vec4 vec_color_ = GUN_COLOR;
		vec4 ambient_color_ = 0.1f * GUN_COLOR;
		glBindVertexArray(vao[g_index + DEBUG]);
		glUniformMatrix4fv(light_ctm, 1, GL_FALSE, &gun_final_mat[0][0]);
		glUniformMatrix4fv(light_view, 1, GL_FALSE, &gun_view_mtx[0][0]);
		glUniformMatrix3fv(light_normal, 1, GL_FALSE, &gun_normal_mtx[0][0]);

		glUniform4fv(light_diffuse, 1, &vec_color_[0]);
		glUniform4fv(light_ambient, 1, &ambient_color_[0]);
		glUniform4fv(light_specular, 1, &vec_color_[0]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, vao_size[g_index]);
		index = P_GUN;
	}
	glBindVertexArray(vao[index + DEBUG]);
	glUniformMatrix4fv(light_ctm, 1, GL_FALSE, &final_mat[0][0]);
	glUniformMatrix4fv(light_view, 1, GL_FALSE, &view_mat_pos[0][0]);
	glUniformMatrix3fv(light_normal,1,GL_FALSE,&normal_mtx[0][0]);

	glUniform4fv(light_diffuse, 1, &vec_color[0]);
	glUniform4fv(light_ambient, 1, &ambient_color[0]);
	glUniform4fv(light_specular, 1, &vec_color[0]);
	//glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	/*
	vec_color = BACK_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	*/
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);
	/*
	vec_color = PLAYER_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);
	*/

	if (jump != 0) {
		jump--;
		this->move();
	}
	glUseProgram(program);
}
int Player::get_life() {
	return life;
}
void Player::die() {
	if (life > 0)life--;
}