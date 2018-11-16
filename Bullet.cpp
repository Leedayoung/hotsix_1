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
pair<float, float> Bullet::move_test() {
	return Entity::move_test(direc);
}
pair<int, int> Bullet::move_test2() {
	return Entity::move_test2(direc);
}
bool Bullet::move() {
	if (length == 0) return false;
	Entity::move(direc);
	length--;
	return true;
}
void Bullet::display() {

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
	int index = BULL;
	glBindVertexArray(vao[index]);
	//mat4 scale = glm::scale(glm::mat4(1.0), vec3(0.1f, 0.05f, 0.1f));
	mat4 y_z = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, 0.0));
	//mat4 scale = glm::scale(glm::mat4(1.0), vec3(1.0f, 0.01f, 1.0f));
	mat4 rot = glm::rotate(glm::mat4(1.0), 1.57f*mul, vec3(0.0, 0.0, 1.0));
	mat4 final_mat = per_look * trans*rot * y_z;//  * y_z * scale;// *rot * scale;
	vec4 vec_color = vec4(0.0, 0.0, 0.0, 0.5);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);
}