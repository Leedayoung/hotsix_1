#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
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
using namespace std;
using namespace glm;

enum direction { up = 0, right, down, left};
enum image { bullet_u = 0, bullet_d, bullet_l, bullet_r, player_u, player_d, player_l, player_r, item_p, wall_p, enemy_u, enemy_d, enemy_l, enemy_r };
extern GLuint texture[16];

class Entity {
public:
	float pos_x;
	float pos_y;
	int direc;
	int jump = 0;
	int get_direction();
	float get_x();
	float get_y();
	pair<float, float> get_jump_position();
	void add_jump(int _jump) {
		jump += _jump;
	}
	int get_jump() {
		return 0;
		
		return jump;
		
	}
	pair<float, float> get_position();
	pair<int, int> move_test(int direc);
	pair<int, int> move_test2(int direc);
	void move(int direc);
	void display(int x1, int y1, int x2, int y2);
	void set_direction(int direc);
};