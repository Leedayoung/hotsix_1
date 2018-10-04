#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;

enum direction { up = 0, down, left, right };
enum image { bullet_u = 0, bullet_d, bullet_l, bullet_r, player_u, player_d, player_l, player_r, item_p, wall_p, enemy_u, enemy_d, enemy_l, enemy_r };
extern GLuint texture[16];

class Entity {
public:
	int pos_x;
	int pos_y;
	int direc;
	int get_direction();
	int get_x();
	int get_y();
	pair<int, int> get_position();
	pair<int, int> move_test(int direc);
	void move(int direc);
	void display(int x1, int y1, int x2, int y2);
	void set_direction(int direc);
};