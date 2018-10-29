#pragma once
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

extern GLuint program;
extern GLint ctmParam;
extern glm::mat4 ortho_mat;
extern GLint vColor;

typedef struct treenode {
	mat4 m;
	mat4 s;
	vec4 color;
	void(*f)(mat4 s);
	struct treenode * sibling;
	struct treenode * child;
} treenode;


treenode * player_down;
treenode * player_up;
treenode * player_left;
treenode * player_right;

void draw(mat4 s,vec4 color) {
	mat4 final_mat = model_view * s;
	
	vec4 vec_color = vec4(1.0, 1.0, 0.0, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}
void make_player_down() {
	//torso
	treenode * torso = player_down = new treenode;
	player_down -> m = glm::translate(glm::mat4(1.0), vec3(0.0, 0.4, 0.0));
	player_down -> s = glm::scale(glm::mat4(1.0), vec3(1.0, 0.4, 0.0));
	torso->color = vec4(0.0, 0.0, 1.0, 1.0);
	torso->sibling = NULL;
	
	//head
	treenode * head = torso->child = new treenode;
	head -> m = glm::translate(glm::mat4(1.0), vec3(0.0, 0.4, 0.0));
	head -> s = glm::scale(glm::mat4(1.0), vec3(1.0, 0.2, 0.0));
	head->color = vec4(0.0, 0.3, 0.7, 1.0);
	head->child = NULL;

	//left upper_leg
	treenode * left_upper_leg = head->sibling = new treenode;
	left_upper_leg -> m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_upper_leg -> s = glm::scale(glm::mat4(1.0), vec3(0.25, 0.2, 0.0));
	left_upper_leg->color = vec4(0.0, 0.3, 0.7, 1.0);
	left_upper_leg->sibling = NULL;

	//left lower_leg
	treenode * left_lower_leg = left_upper_leg->child = new treenode;
	left_lower_leg -> m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_lower_leg -> s = glm::scale(glm::mat4(1.0), vec3(0.25, 0.2, 0.0));
	left_lower_leg->color = vec4(0.0, 0.3, 0.7, 1.0);
	left_lower_leg->child = NULL;

}
mat4 model_view;
vector<mat4> stack_mat;
void traverse(treenode* root) {
	if (root == NULL) return;
	stack_mat.push(model_view);
	model_view = model_view * root->m;
	root->f(root->s);
	if (root->child != NULL)
		traverse(root->child);
	model_view = stack_mat.back();
	stack_mat.pop();
	if (root->sibling != NULL)
		traverse(root->sibling);
	return;
}