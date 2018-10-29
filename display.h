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
using namespace glm;

extern GLuint program;
extern GLint ctmParam;
extern glm::mat4 ortho_mat;
extern GLint vColor;
extern mat4 model_view;

class treenode {
public:
	mat4 m;
	mat4 s;
	mat4 jump1;
	mat4 jump2;
	mat4 jump3;
	mat4 gun;
	vec4 color;
	bool is_gun;
	void(*f)(mat4 s);
	treenode * sibling;
	treenode * child;
	treenode() {
		sibling = NULL;
		child = NULL;
		jump1 = glm::mat4(1.0);
		jump2 = glm::mat4(1.0);
		jump3 = glm::mat4(1.0);
		gun = glm::mat4(1.0);
		is_gun = false;
	}
};

extern treenode * player_down;
extern treenode * player_up;
extern treenode * player_left;
extern treenode * player_right;

void make_player();
void traverse(treenode* root,int state);
