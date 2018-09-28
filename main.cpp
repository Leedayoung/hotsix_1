#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "map.cpp"
#include "player.h"
using namespace std;

Map newmap;

void main(int argc, char **argv) {
	newmap = Map();
	glutSpecialFunc(player_move_func);
	glutMainLoop();
}

void player_move_func(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		newmap.valid_move(direction::up);
		break;
	case GLUT_KEY_DOWN:
		newmap.valid_move(direction::down);
		break;
	case GLUT_KEY_RIGHT:
		newmap.valid_move(direction::right);
		break;
	case GLUT_KEY_LEFT:
		newmap.valid_move(direction::left);
		break;
	}
}