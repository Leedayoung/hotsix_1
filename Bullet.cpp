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
	glUseProgram(light_program);
	glBindVertexArray(vao[index+DEBUG]);
	mat4 y_z = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos_x, pos_y, 0.5));
	mat4 scale = glm::scale(glm::mat4(1.0), vec3(0.4f, 0.4f, 0.4f));
	mat4 rot = glm::rotate(glm::mat4(1.0), 1.57f*mul, vec3(0.0, 0.0, 1.0));
	mat4 view_mat_pos = trans * rot * y_z * scale;
	mat4 final_mat = per_look * trans*rot * y_z* scale;//  * y_z * scale;// *rot * scale;
	vec4 ambient_color = vec4(0.2, 0.0, 0.2, 1.0);
	mat4 inv_view_mat = inverse(view_mat_pos);
	mat4 MVI = transpose(inv_view_mat);
	mat3 normal_mtx = mat3(MVI);


	vec4 vec_color = BULLET_COLOR;
	glUniformMatrix4fv(light_ctm, 1, GL_FALSE, &final_mat[0][0]);
	glUniformMatrix4fv(light_view, 1, GL_FALSE, &view_mat_pos[0][0]);
	glUniformMatrix3fv(light_normal, 1, GL_FALSE, &normal_mtx[0][0]);

	glUniform4fv(light_diffuse, 1, &vec_color[0]);
	glUniform4fv(light_ambient, 1, &ambient_color[0]);
	glUniform4fv(light_specular, 1, &vec_color[0]);
	glUniform1i(shading_mod, (int)shading_mode);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);

}