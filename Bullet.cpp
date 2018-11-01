#pragma once
#include <iostream>
#include "Entity.h"
#include "Bullet.h"
#include "display.h"
using namespace std;
using namespace glm;

Bullet::Bullet(float _pos_x, float _pos_y, int _direction, int _length) {
	pos_x = (float)_pos_x;
	pos_y = (float)_pos_y;
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
	glBindVertexArray(vao[2]);
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, 0));
	mat4 rot;
	switch (direc) {
		case direction::down:
			rot = glm::translate(glm::mat4(1.0), glm::vec3(0, 2, 0))*glm::rotate(glm::mat4(1.0), -1.57f, vec3(0, 0, 1));
			break;
		case direction::up:
			rot = glm::translate(glm::mat4(1.0), glm::vec3(1, 0, 0))*glm::rotate(glm::mat4(1.0), +1.57f, vec3(0, 0, 1));
			break;
		case direction::left:
			rot = glm::translate(glm::mat4(1.0), glm::vec3(2, 0, 0))*glm::scale(glm::mat4(1.0), vec3(-1,1,0));
			break;
		default:
			rot = glm::mat4(1.0);
	}

	mat4 final_mat = ortho_mat * trans * rot;
	vec4 vec_color = vec4(0.4, 0.4, 1.0, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
	glBindVertexArray(vao[0]);

	//glBindTexture(GL_TEXTURE_2D, texture[bullet_u + direc]);
	//Entity::display(pos_x, pos_y, pos_x + 1, pos_y + 1);
}