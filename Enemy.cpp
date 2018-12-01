#pragma once
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Enemy.h"
#include "display.h"
using namespace std;
Enemy::Enemy() {

}
Enemy::Enemy(int _pos_x, int _pos_y) {
	id = id_num++;
	pos_x = (float)_pos_x;
	pos_y = (float)_pos_y;
	direc = rand()%4;
}

bool Enemy::check_chase(pair<float, float> player_pos) {
	float player_x = player_pos.first;
	float player_y = player_pos.second;
	float chase_distance = 5;
	if (abs(player_x - pos_x) < chase_distance || abs(player_y - pos_y) < chase_distance) 
		return true;
	else 
		return false;
}
void Enemy::update() {
	if (jump != 0) {
		jump--;
		this->move();
	}
}
void Enemy::display() {
	glUseProgram(light_program);
	int index = (4 - jump) % 4 + 4;
	glBindVertexArray(vao[index+DEBUG]);
	float mul;
	switch (direc) {
	case direction::up:
		mul = 0;
		break;
	case direction::down:
		mul = 2;
		break;
	case direction::left:
		mul = 1;
		break;
	case direction::right:
		mul = 3;
		break;
	}
	mat4 scale = glm::scale(glm::mat4(1.0), vec3(0.1f, 0.05f, 0.1f));
	mat4 y_z = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
	
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, -0.25));
	mat4 rot = glm::rotate(glm::mat4(1.0), 1.57f*mul, vec3(0.0, 0.0, 1.0));

	mat4 view_mat = rot* y_z;
	mat4 final_mat = per_look * trans * rot * y_z * scale;// *rot * scale;
	vec4 vec_color;
	float shiness = 0.5;
	vec3 lighting = vec3(1.0, 1.0, 1.0);
	glUniformMatrix4fv(light_ctm, 1, GL_FALSE, &final_mat[0][0]);
	glUniformMatrix4fv(light_view, 1, GL_FALSE, &view_mat[0][0]);
	vec_color = vec4(0.0, 0.0, 0.5, 1);
	glUniform4fv(light_diffuse, 1, &vec_color[0]);
	glUniform4fv(light_ambient, 1, &vec_color[0]);
	glUniform4fv(light_specular, 1, &vec_color[0]);
	glUniform1f(light_shine, shiness);
	glUniform3fv(light_dir, 1, &lighting[0]);

	glUniform4fv(light_color, 1, &vec_color[0]);
	/*
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	vec_color = BACK_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	*/
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);
	glUseProgram(program);
	/*
	glLineWidth(0.01);
	vec_color = ENEMY_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);
	*/
	/*glBindTexture(GL_TEXTURE_2D, texture[image::enemy_u + direc]);*/
}