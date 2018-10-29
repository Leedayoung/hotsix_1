#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <math.h>
#include <cstdio>
#include "time.h"
#include "map.h"
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "display.h"
#include <string>
#include <fstream>
#include <mutex>
using namespace std;
using namespace glm;

#define BUFFER_OFFSET( offset ) ((GLvoid*) (offset))
const int NumPoints = 4;
int call_state = 0;
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
void init(void);
GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
std::mutex mtx_lock;

int main(int argc, char **argv) {
	srand((unsigned)time(NULL));
	Player::image_setting();
	newmap = Map();
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA );
	glutInitWindowPosition(0,0);
	glutInitWindowSize(700, 700);//창 크기 설정
	glutCreateWindow("GAME");

	glewInit();
	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(player_move_func);
	glutKeyboardFunc(bullet_make);
	glutTimerFunc(147, move_bullets, 1);
	glutTimerFunc(1000, move_enemies, 1);
	glutIdleFunc(endstate);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//load_images();
	glutMainLoop();
	return 0;
}

void init(void) {
	vec4 points[NumPoints] = {
		vec4(0, 0,0, 1), vec4(1, 0,0,1), vec4(1,1,0,1), vec4(0, 1,0,1)
	};
	vec4 item_points[6] = {
		vec4(0.5, 0.75, 0.0, 1.0), vec4(0.25, 1.0, 0.0, 1.0 ), vec4(0.0, 0.75, 0.0, 1.0)
		, vec4( 0.5, 0.0, 0.0, 1.0), vec4(1.0, 0.75, 0.0, 1.0), vec4(0.75, 1.0, 0.0, 1.0)};

	vec4 bullet_points[12] = {
		vec4(1.0, 0.5, 0.0, 1.0), vec4(0.7, 1.0, 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0)
		, vec4(0.2, 0.8, 0.0, 1.0), vec4(0.0, 0.7, 0.0, 1.0), vec4(0.2, 0.6, 0.0, 1.0)
		, vec4(0.0, 0.5, 0.0, 1.0), vec4(0.2, 0.4, 0.0, 1.0), vec4(0.0, 0.3, 0.0, 1.0)
		, vec4(0.2, 0.2, 0.0, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.7, 0.0, 0.0, 1.0) };

	//Vertex array object
	
	glGenVertexArrays(1, &vao[0]);
	glBindVertexArray(vao[0]);

	GLuint buffer;
	//Create and initialize a buffer obj
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	ctmParam = glGetUniformLocation(program, "ctm");
	vColor = glGetUniformLocation(program, "color");
	
	glGenVertexArrays(1, &vao[1]);
	glBindVertexArray(vao[1]);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(item_points), item_points, GL_STATIC_DRAW);
	loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glGenVertexArrays(1, &vao[2]);
	glBindVertexArray(vao[2]);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_points), bullet_points, GL_STATIC_DRAW);
	loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vao[0]);
	glClearColor(1.0, 1.0, 0.0, 1.0);

	make_player();
	call_state = 0;
}

static char* readShaderSource(const char* shaderFile)
{
	FILE* fp;
	fopen_s(&fp, shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

GLuint InitShader(const char* vShaderFile, const char* fShaderFile)
{
	struct Shader {
		const char*  filename;
		GLenum       type;
		GLchar*      source;
	}  shaders[2] = {
		{ vShaderFile, GL_VERTEX_SHADER, NULL },
		{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
	};

	GLuint program = glCreateProgram();

	for (int i = 0; i < 2; ++i) {
		Shader& s = shaders[i];
		s.source = readShaderSource(s.filename);
		if (shaders[i].source == NULL) {
			std::cerr << "Failed to read " << s.filename << std::endl;
			exit(EXIT_FAILURE);
		}

		GLuint shader = glCreateShader(s.type);
		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
		glCompileShader(shader);

		GLint  compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			std::cerr << s.filename << " failed to compile:" << std::endl;
			GLint  logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			exit(EXIT_FAILURE);
		}

		delete[] s.source;

		glAttachShader(program, shader);
	}

	/* link  and error check */
	glLinkProgram(program);

	GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cerr << "Shader program failed to link" << std::endl;
		GLint  logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		exit(EXIT_FAILURE);
	}

	/* use program object */
	glUseProgram(program);
	return program;
}

void reshape(int w, int h) {
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, newmap.get_map_size(), 0, newmap.get_map_size());
}
void display() {
	newmap.display(program);
}
void makedelay(int x)
{
	if (x == 0) return;
	glutPostRedisplay();
	glutTimerFunc(100, makedelay, x-1);
	
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
	glutTimerFunc(100, makedelay, 3);
}
void bullet_make(unsigned char key, int x, int y) {
	if (key == 32) newmap.create_bullet();
	glutPostRedisplay();
	Sleep(200);
	glutPostRedisplay();
}
void move_enemies(int v) {
	if (newmap.isEnd())
		return;
	newmap.update_enemies();
	glutPostRedisplay();
	glutTimerFunc(1000, move_enemies, 1);
	return;
}	
void move_bullets(int v) {
	if (newmap.isEnd())
		return;
	newmap.update_bullets();
	glutPostRedisplay();
	glutTimerFunc(147, move_bullets, 1);
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