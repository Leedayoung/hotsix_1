#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
#include <string>
#include <fstream>
#include "time.h"
#include "map.h"
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "display.h"
#include "sphere.h"
using namespace std;
using namespace glm;

#define BUFFER_OFFSET( offset ) ((GLvoid*) (offset))
const int NumPoints = 4;
void display();
vector<glm::vec4> vertices;
void reshape(int w, int h);
void display();
vector < glm::vec4 > load_obj_files(string file_path,int type,int index);
void init();
void player_move_3d(unsigned char key, int x, int y);
static char* readShaderSource(const char* shaderFile);
GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
void move_enemies(int v);
void makedelay(int x);
Map newmap;
void mouse_bullet(int button, int state, int x, int y);
void move_bullets(int v);
void restart(unsigned char key, int x, int y);


int main(int argc, char **argv) {

	srand((unsigned)time(NULL));
	newmap = Map();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);//창 크기 설정
	glutCreateWindow("GAME");
	glutMouseFunc(mouse_bullet);

	glewInit();
	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(player_move_3d);
	glutMouseFunc(mouse_bullet);
	glutTimerFunc(1000, move_enemies, 1);
	glutTimerFunc(150, move_bullets, 1);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
	return 0;
}
void init() {
	vec4 rect[4] = {
		vec4(0, 0,0, 1), vec4(1, 0,0,1), vec4(1,1,0,1), vec4(0, 1,0,1)
	};
	vec4 heart[6] = {
		vec4(0.5, 0.75, 0.0, 1.0), vec4(0.25, 1.0, 0.0, 1.0), vec4(0.0, 0.75, 0.0, 1.0)
		, vec4(0.5, 0.0, 0.0, 1.0), vec4(1.0, 0.75, 0.0, 1.0), vec4(0.75, 1.0, 0.0, 1.0) };
	
	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);
	ctmParam = glGetUniformLocation(program, "ctm");
	vColor = glGetUniformLocation(program, "color");

	load_obj_files("OBJ files/cu.txt", 0, P_0);

	load_obj_files("OBJ files/cu.txt", 0, P_1);
	load_obj_files("OBJ files/cu.txt", 0, P_2);
	load_obj_files("OBJ files/cu.txt", 0, P_3);
	load_obj_files("OBJ files/cu.txt", 0, P_GUN);

	load_obj_files("OBJ files/cu.txt", 0, E_0);
	load_obj_files("OBJ files/cu.txt", 0, E_1);
	load_obj_files("OBJ files/cu.txt", 0, E_2);
	load_obj_files("OBJ files/cu.txt", 0, E_3);


	load_obj_files("OBJ files/cu.txt", 0, BULL);
	load_obj_files("OBJ files/cu.txt", 0, WALL);


	/*
	load_obj_files("OBJ files/dummy_obj_walk_pose_0.obj", 0, P_0	);
	load_obj_files("OBJ files/dummy_obj_walk_pose_1.obj", 0, P_1);
	load_obj_files("OBJ files/dummy_obj_walk_pose_2.obj", 0, P_2);
	load_obj_files("OBJ files/dummy_obj_walk_pose_3.obj", 0, P_3);
	load_obj_files("OBJ files/dummy_obj_gun.obj", 0, P_GUN);
	
	load_obj_files("OBJ files/Skeleton_pose0.obj", 0, E_0);
	load_obj_files("OBJ files/Skeleton_pose1.obj", 0, E_1);
	load_obj_files("OBJ files/Skeleton_pose2.obj", 0, E_2);
	load_obj_files("OBJ files/Skeleton_pose3.obj", 0, E_3);

	
	load_obj_files("OBJ files/bullet.obj", 0, BULL);
	load_obj_files("OBJ files/cu.txt", 0, WALL);
	*/

	glGenVertexArrays(1, &vao[RECT]);
	glBindVertexArray(vao[RECT]);
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glGenVertexArrays(1, &vao[HEART]);
	glBindVertexArray(vao[HEART]);
	buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(heart), heart, GL_STATIC_DRAW);
	loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

}
void reshape(int w, int h)
{
	//창이 아주 작을 때, 0 으로 나누는 것을 예방합니다.
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	glViewport(0, 0, w, h);
	
}
void display() {
	newmap.display();
	return;
	
	mat4 look_at = glm::lookAt(glm::vec3(2.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	mat4 perspec = glm::perspective(glm::radians(90.0f), 1.0f, 0.001f, 1000.0f);
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, float(0.7137), float(0.7568));
	glLineWidth(1);
	glPointSize(1.0f);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	mat4 final_mat = perspec * look_at;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[0]);
	glutSwapBuffers();
	return;
}
vector < glm::vec4 > load_obj_files(string file_path,int type, int index) {
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec2 > temp_uvs;
	vector< glm::vec3 > temp_normals;

	FILE * file = fopen(&file_path[0], "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return vector<glm::vec4>();
	}
	int num = 0;
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);

		}
		else if (strcmp(lineHeader, "f") == 0) {
			if (num == 0) num = 1;
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			
			if (type == 0) {
				int v3, t;
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2],&v3,&t,&t);
				if (matches == 9){
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
				}
				else if (matches == 12) {
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);

					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(v3);
				}else{
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return vector<glm::vec4>();
				}
				
			}
			else {
				int v1, v2, v3, v4;
				int t;
				int matches = fscanf(file, "%d/%d %d/%d %d/%d %d/%d\n", &v1, &t, &v2, &t, &v3, &t, &v4, &t);
				if (matches == 8) {
					vertexIndices.push_back(v1);
					vertexIndices.push_back(v2);
					vertexIndices.push_back(v3);

					vertexIndices.push_back(v2);
					vertexIndices.push_back(v3);
					vertexIndices.push_back(v4);
				}
				else if (matches == 6) {
					vertexIndices.push_back(v1);
					vertexIndices.push_back(v2);
					vertexIndices.push_back(v3);
				}
				
			}
		}
	}
	std::vector < glm::vec4 > out_vertices;
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 t = temp_vertices[vertexIndex - 1];
		glm::vec4 vertex = glm::vec4(t.x, t.y, t.z, 1.0);
		out_vertices.push_back(vertex);
	}
	
	
	glGenVertexArrays(1, &vao[index]);
	glBindVertexArray(vao[index]);
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(vec4), &out_vertices[0], GL_STATIC_DRAW);
	vao_size[index] = out_vertices.size();
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	return out_vertices;
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
void makedelay(int x)
{
	if (x == 0) return;
	glutPostRedisplay();
	glutTimerFunc(100, makedelay, x - 1);
}
void player_move_3d(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		newmap.valid_move_3d();
		break;
	case 'a':
		newmap.rotate_3d(-1);
		break;
	case 'd':
		newmap.rotate_3d(1);
		break;
	case ' ':
		newmap.change_mode();
	}
	if (newmap.isEnd()) {
		glutMouseFunc(NULL);
		glutKeyboardFunc(restart);
		glutPostRedisplay();
	}
	glutPostRedisplay();
	glutTimerFunc(100, makedelay, 3);
}
void move_enemies(int v) {
	newmap.update_enemies();
	newmap.timer();
	if (newmap.get_end()) {
		glutSpecialFunc(NULL);
		glutMouseFunc(NULL);
		glutKeyboardFunc(restart);
		glutPostRedisplay();
		return;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, move_enemies, 1);
	return;
}
void mouse_bullet(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			newmap.create_bullet();
			glutPostRedisplay();
		}
	}
}
void move_bullets(int v) {
	if (newmap.get_end())
		return;
	newmap.update_bullets();
	glutPostRedisplay();
	glutTimerFunc(147, move_bullets, 1);
	return;
}
void restart(unsigned char key, int x, int y) {
	if (key == 'r' || key == 'R') {
		newmap = Map();
		glutMouseFunc(mouse_bullet);
		glutKeyboardFunc(player_move_3d);
		glutTimerFunc(150, move_bullets, 1);
		glutTimerFunc(1000, move_enemies, 1);
	}
}