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
int LoadBMP(const char* location, GLuint &texture);
void load_images();

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
	glutTimerFunc(147, move_bullets, 1);
	glutTimerFunc(1000, move_enemies, 1);
	glutIdleFunc(endstate);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	load_images();
	glutMainLoop();
	return 0;
}

void reshape(int w, int h) {
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, newmap.get_map_size(), 0, newmap.get_map_size());
}
void display() {
	newmap.display();
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
	glutPostRedisplay();
}
void bullet_make(unsigned char key, int x, int y) {
	if (key == 32) newmap.create_bullet();
	glutPostRedisplay();
}
void move_enemies(int v) {
	newmap.update_enemies();
	if (!newmap.isEnd())
		glutTimerFunc(1000, move_enemies, 1);
	glutPostRedisplay();
	
	return;
}	
void move_bullets(int v) {
	newmap.update_bullets();
	if (!newmap.isEnd())
		glutTimerFunc(147, move_bullets, 1);
	glutPostRedisplay();	
	return;
}
void endstate() {
	if (newmap.isEnd()) {
		glutSpecialFunc(NULL);
		glutKeyboardFunc(NULL);
		glutIdleFunc(NULL);
	}
}
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
	for (int i = 0; i < width*height * 3; i += 3)
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

	delete datBuff[0];
	delete datBuff[1];
	delete pixels;
	// Delete the two buffers.
	return 0; // Return success code 

}
void load_images() {
	//load bullet images
	LoadBMP("resource/bullet_up.bmp", texture[bullet_u]);
	LoadBMP("resource/bullet_down.bmp", texture[bullet_d]);
	LoadBMP("resource/bullet_right.bmp", texture[bullet_r]);
	LoadBMP("resource/bullet_left.bmp", texture[bullet_l]);

	//load player images
	LoadBMP("resource/player_u.bmp", texture[player_u]);
	LoadBMP("resource/player_d.bmp", texture[player_d]);
	LoadBMP("resource/player_l.bmp", texture[player_l]);
	LoadBMP("resource/player_r.bmp", texture[player_r]);

	//load item image
	LoadBMP("resource/item_p.bmp", texture[image::item_p]);
	LoadBMP("resource/wall.bmp", texture[image::wall_p]);

	//load enemy images
	LoadBMP("resource/enemy_u.bmp", texture[image::enemy_u]);
	LoadBMP("resource/enemy_d.bmp", texture[image::enemy_d]);
	LoadBMP("resource/enemy_l.bmp", texture[image::enemy_l]);
	LoadBMP("resource/enemy_r.bmp", texture[image::enemy_r]);

}