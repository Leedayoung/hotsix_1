#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "map.h"
#include "player.h"
using namespace std;

Map newmap;

void main(int argc, char **argv) {
	newmap = Map();
	glutSpecialFunc(player_move_func);
	glutKeyboardFunc(bullet_make);
	glutTimerFunc(1000, move_default,1);
	glutMainLoop();
}

//Ŭ���� �ȿ��� �� �Լ��� �����ϸ� Error ��ȯ�ϱ⿡ ���⼭ ����.
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
void bullet_make(unsigned char key, int x, int y) {
	if(key == 32) newmap.create_bullet();
}
void move_default(int v) {
	//Have to implement
	glutTimerFunc(1000, move_default, 1);
}