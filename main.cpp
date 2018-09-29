#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "time.h"
#include "map.h"
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include "Entity.h"
using namespace std;

Map newmap;
bool flag = false;
void player_move_func(int key, int x, int y);
void bullet_make(unsigned char key, int x, int y);
void move_enemies(int v);
void move_bullets(int v);
void display();
void reshape(int w, int h);
void endstate();

int main(int argc, char **argv) {
	srand((unsigned)time(NULL));
	newmap = Map();
	glutInit(&argc, argv);
	glutInitWindowPosition(-1,-1);
	glutInitWindowSize(500, 500);//창 크기 설정
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("GAME");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	if (!flag)
	{
		glutSpecialFunc(player_move_func);
		glutKeyboardFunc(bullet_make);
		glutTimerFunc(200, move_bullets, 1);
		glutTimerFunc(1000, move_enemies, 1);
		glutIdleFunc(endstate);
	}
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
				glColor3f(0.0, 0.0, 0.0);
				glRectf(x, y + 1, x + 1, y);
			}
			else if (map_arr[y][x] == map_info::item) {
				glColor3f(1.0, 0.0, 0.0);
				glRectf(x, y + 1, x + 1, y);
			}
		}
	}
	vector<Enemy> enem_vec = newmap.get_enem_vec();
	glColor3f(0.0, 1.0, 0.0);
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
		pair<int, int> pos = it->get_position();
		int x = pos.first;
		int y = pos.second;
		glRectf(x, y + 1, x + 1, y);
	}

	vector<Bullet> bull_vec = newmap.get_bullet_vec();
	glColor3f(0.0, 0.0, 1.0);
	for (vector<Bullet>::iterator it = bull_vec.begin(); it != bull_vec.end(); it++) {
		pair<int, int> pos = it->get_position();
		int x = pos.first;
		int y = pos.second;
		glRectf(x, y + 1, x + 1, y);
	}

	Player player = newmap.get_player();
	glColor3f(0.0, 1.0, 1.0);
	pair<int, int> pos = player.get_position();
	int x = pos.first;
	int y = pos.second;
	glRectf(x, y + 1, x + 1, y);

	glutSwapBuffers();
}
//클래스 안에서 본 함수를 선언하면 Error 반환하기에 여기서 선언.
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
	glutPostRedisplay();
}
void bullet_make(unsigned char key, int x, int y) {
	if (key == 32) newmap.create_bullet();
	glutPostRedisplay();
}
void move_enemies(int v) {
	newmap.update_enemies();
	glutPostRedisplay();
	glutTimerFunc(1000, move_enemies, 1);
}
void move_bullets(int v) {
	newmap.update_bullets();
	glutPostRedisplay();
	glutTimerFunc(200, move_bullets, 1);
}
void endstate() {
	if (newmap.isEnd()) flag = true;
}