#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "map.h"
#include "player.h"
using namespace std;

Map newmap;
void player_move_func(int key, int x, int y);
void bullet_make(unsigned char key, int x, int y);
void move_default(int v);
void display();
void reshape(int w, int h);

int main(int argc, char **argv) {
	newmap = Map();
	glutInit(&argc, argv);
	glutInitWindowPosition(-1,-1);
	glutInitWindowSize(500, 500);//â ũ�� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("GAME");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutSpecialFunc(player_move_func);
	glutKeyboardFunc(bullet_make);
	//glutTimerFunc(1000, move_default,1);
	glutMainLoop();

	return 0;
}
void reshape(int w, int h) {
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, newmap.get_map_size(), 0, newmap.get_map_size());
}
void display() {	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	int ** map_arr = newmap.get_map_arr();
	double wall_len = 1.0 / newmap.get_map_size();
	for (int y = 0; y < newmap.get_map_size(); y++) {
		for (int x = 0; x < newmap.get_map_size(); x++) {
			if (map_arr[y][x] == map_info::wall) {

			}
		}
	}
	glColor3f(0.0, 1.0, 0.0);
	glutSwapBuffers();
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