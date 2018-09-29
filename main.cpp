#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <cstdio>
#include "time.h"
#include "map.h"
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include <string>
#include <fstream>
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


int LoadBMP(const char* location, GLuint &texture) {
	
	unsigned char* pixels; //[number of lines][number of columns *3 (because in row is bytes (3 per pixel))]
	unsigned char* datBuff[2] = { nullptr, nullptr }; // Header buffers

	BITMAPFILEHEADER* bmpHeader = nullptr; // Header
	BITMAPINFOHEADER* bmpInfo = nullptr; // Info 

	ifstream file(location, ios::binary);
	if (!file)
	{
		std::cout << "Failure to open bitmap file.\n";
		return 0;
	}

	datBuff[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

	bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
	bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

	if (bmpHeader->bfType != 0x4D42)
	{
		std::cout << "File \"" << location << "\" isn't a bitmap file\n";
		return 0;
	}
	pixels = new unsigned char[bmpInfo->biHeight*bmpInfo->biWidth * 3];
	file.read((char*)pixels, bmpInfo->biHeight*bmpInfo->biWidth * 3);
	// Set width and height to the values loaded from the file
	int width = bmpInfo->biWidth;
	int height = bmpInfo->biHeight;
	for (int i = 0; i < width*height*3; i += 3)
	{
		unsigned char tmp = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = tmp;
	}
	cout << " COMPLETED. " << endl;
	// Set width and height to the values loaded from the file
	GLuint w = bmpInfo->biWidth;
	GLuint h = bmpInfo->biHeight;

	glGenTextures(1, &texture);             // Generate a texture
	glBindTexture(GL_TEXTURE_2D, texture); // Bind that texture temporarily

	GLint mode = GL_RGB;                   // Set the mode

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, pixels);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	// Output a successful message
	std::cout << "Texture \"" << location << "\" successfully loaded.\n";

	// Delete the two buffers.
	return 0; // Return success code 
	
}
/*
void displa2() {
	
	LoadBMP("resource/bullet.bmp", texture);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	int w = 100;
	int h = 100;
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
	glTexCoord2f(1.0, 0.0); glVertex2f(w, 0);
	glTexCoord2f(1.0, 1.0); glVertex2f(w, h);
	glTexCoord2f(0.0, 1.0); glVertex2f(0, h);
	glEnd();

	glutSwapBuffers();
}*/
int main(int argc, char **argv) {
	srand((unsigned)time(NULL));
	//newmap = Map();
	glutInit(&argc, argv);
//	LoadBMP("resource/RAY.bmp", texture);
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
	int view_size = newmap.get_map_size() / 8;
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
	glColor3f(1.0, 1.0, 1.0);
	for (vector<Bullet>::iterator it = bull_vec.begin(); it != bull_vec.end(); it++) {
		pair<int, int> pos = it->get_position();
		int x = pos.first;
		int y = pos.second;
		GLuint texture;
		LoadBMP("resource/bullet.bmp", texture);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		int w = 100;
		int h = 100;
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex2f(x, y);
			glTexCoord2f(1.0, 0.0); glVertex2f(x+1, y);
			glTexCoord2f(1.0, 1.0); glVertex2f(x+1, y+1);
			glTexCoord2f(0.0, 1.0); glVertex2f(x, y+1);
		glEnd();
		//glRectf(x, y + 1, x + 1, y);
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
		if (newmap.get_win()) {
			print(x + view_size, y + view_size, "You Win");
		}
		else {
			print(x + view_size, y + view_size, "You Lose");
		}
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