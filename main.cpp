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
#include <string>
using namespace std;

Map newmap;
void player_move_func(int key, int x, int y);
void bullet_make(unsigned char key, int x, int y);
void move_enemies(int v);
void move_bullets(int v);
void display();
void reshape(int w, int h);
void endstate();
int print_result = 0;

int main(int argc, char **argv) {
	srand((unsigned)time(NULL));
	newmap = Map();
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800, 800);//창 크기 설정
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("GAME");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(player_move_func);
	glutKeyboardFunc(bullet_make);
	glutTimerFunc(150, move_bullets, 1);
	glutTimerFunc(1000, move_enemies, 1);
	glutIdleFunc(endstate);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
	return 0;
}

void reshape(int w, int h) {
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, newmap.get_map_size(), 0, newmap.get_map_size());
}
void print(int x, int y, string string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	//loop to display character by character
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
};
void display() {
	
	pair<int, int> pos = newmap.get_player().get_position();
	int x = pos.first, y = pos.second;
	int map_size = newmap.get_map_size();
	int view_size = newmap.get_map_size() / 4;
	x -= view_size;
	y -= view_size;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + 2*view_size > map_size) x = map_size - 2*view_size;
	if (y + 2*view_size > map_size) y = map_size - 2*view_size;
	
	glLoadIdentity();
	gluOrtho2D(x, x+ 2 * view_size, y, y+2*view_size);
	
	if (print_result) return;
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
	pos = player.get_position();
	int p_x = pos.first;
	int p_y = pos.second;
	glRectf(p_x, p_y + 1, p_x + 1, p_y);
	
	//item inventory
	int item_size = view_size / 4;
	int item_num = player.get_num_i();
	string s = "item";
	glColor3f(1.0, 1.0, 0.0);
	int display_num = item_num > 3 ? item_num : 3;
	display_num = display_num * 2 +1;
	glRectf(x+7*item_size, y, x+8*item_size, y+display_num);
	glColor3f(0.0, 0.0, 0.0);
	print(x + 7 * item_size, y+display_num+1, "Item List");
	for (int i = 1; i <= item_num; i++)
		print(x + 7 * item_size + 2, y + display_num - 2 * i, s + to_string(i));

	//Enemy Kills
	int enemy_numb = newmap.get_numb_enemy();
	int killed = enemy_numb-newmap.get_enem_vec().size();
	string ss = "Killed Enemy ";
	string dash = "/";
	print( x+ 1, y+2*view_size-3, ss+to_string(killed)+dash+to_string(enemy_numb));

	if (newmap.isEnd()) {
		print(x+view_size, y +view_size, "You Lose");
		print_result = 1;
	}
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
	if (!newmap.isEnd()) 
		glutTimerFunc(1000, move_enemies, 1);
	return;
}	
void move_bullets(int v) {
	newmap.update_bullets();
	glutPostRedisplay();
	if (!newmap.isEnd())
		glutTimerFunc(150, move_bullets, 1);
	return;
}
void endstate() {
	if (newmap.isEnd()) {
		glutSpecialFunc(NULL);
		glutKeyboardFunc(NULL);
		glutIdleFunc(NULL);
	}
}