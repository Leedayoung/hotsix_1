#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Enemy.h"
#include "display.h"
using namespace std;

Enemy::Enemy(int _pos_x, int _pos_y) {
	pos_x = (float)_pos_x;
	pos_y = (float)_pos_y;
	direc = direction::down;
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
void Enemy::display() {

	int index = 7;
	glBindVertexArray(vao[index]);
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
	mat4 scale = glm::scale(glm::mat4(1.0), vec3(0.1f, 0.05f, 0.1f));
	mat4 y_z = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, -0.5));
	//mat4 scale = glm::scale(glm::mat4(1.0), vec3(1.0f, 0.01f, 1.0f));
	mat4 rot = glm::rotate(glm::mat4(1.0), 1.57f*mul, vec3(0.0, 0.0, 1.0));
	mat4 final_mat = per_look * trans * rot * y_z * scale;// *rot * scale;
	vec4 vec_color = vec4(1.0, 0.0, 1.0, 0.5);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);	/*treenode * enemy_direc;
	switch (direc) {
	case direction::down:
		enemy_direc = enemy_down;
		break;
	case direction::up:
		enemy_direc = enemy_up;
		break;
	case direction::left:
	case direction::right:
		enemy_direc = enemy_left;
		break;
	default:
		enemy_direc = player_down;
		break;
	}
	if (direc == direction::right)
		model_view = ortho_mat * glm::translate(mat4(1.0), glm::vec3(pos_x+1, pos_y, 0))*scale(glm::mat4(1.0), vec3(-1, 1, 0));
	else
		model_view = ortho_mat * glm::translate(mat4(1.0), glm::vec3(pos_x, pos_y, 0));// *scale(glm::mat4(1.0), vec3(2, 2, 0));
	
	if (jump != 0) {
		traverse(enemy_direc, jump);
		jump--;
		this->move();
	}
	else {
		traverse(enemy_direc, 0);
	}*/
	/*mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, 0));
	mat4 final_mat = ortho_mat * trans;
	vec4 vec_color = vec4(0.0, 1.0, 1.0, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	*/
	/*glBindTexture(GL_TEXTURE_2D, texture[image::enemy_u + direc]);
	Entity::display(pos_x, pos_y, pos_x + 1, pos_y + 1);*/
}