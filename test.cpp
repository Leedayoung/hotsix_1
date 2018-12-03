#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <numeric>     
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
#include "stb_image.h"


using namespace std;
using namespace glm;

#define BUFFER_OFFSET( offset ) ((GLvoid*) (offset))
const int NumPoints = 4;
void display();
void reshape(int w, int h);
static char* readShaderSource(const char* shaderFile);
GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
void move_enemies(int v);
void makedelay(int x);
Map newmap;
void move_bullets(int v);
void restart(unsigned char key, int x, int y);

vector<glm::vec4> vertices;
void load_obj_files(string file_path, string texture_path, int type, int index);
void mouse_bullet(int button, int state, int x, int y);
void player_move_3d(unsigned char key, int x, int y);
void init();
void load_obj_files_normal(string file_path, int index);

int main(int argc, char **argv) {

	srand((unsigned)time(NULL));
	newmap = Map();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);//창 크기 설정
	glutCreateWindow("GAME");
	glutMouseFunc(mouse_bullet);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(player_move_3d);
	glutMouseFunc(mouse_bullet);
	glutTimerFunc(1000, move_enemies, 1);
	glutTimerFunc(150, move_bullets, 1);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	init();
	
	
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
	
	normal_program = InitShader("light_vertex_normal.glsl", "light_frag_normal.glsl");
	normal_ctm = glGetUniformLocation(normal_program, "ctm");
	normal_normal_model = glGetUniformLocation(normal_program, "normal_model");
	normal_view_model = glGetUniformLocation(normal_program, "view_model");
	normal_cam = glGetUniformLocation(normal_program, "cam");
	normal_player = glGetUniformLocation(normal_program, "player");
	normal_diffuse = glGetUniformLocation(normal_program, "diffuse");
	normal_ambient = glGetUniformLocation(normal_program, "ambient");
	normal_specular = glGetUniformLocation(normal_program, "specular");
	normal_shine = glGetUniformLocation(normal_program, "shiness");
	normal_dir = glGetUniformLocation(normal_program, "l_dir");
	normal_power1 = glGetUniformLocation(normal_program, "light_power1");
	normal_power2 = glGetUniformLocation(normal_program, "light_power2");
	normal_power3 = glGetUniformLocation(normal_program, "light_power3");
	normal_player_dir = glGetUniformLocation(normal_program, "dir");


	light_program = InitShader("light_vertex.glsl", "light_frag.glsl");
	light_ctm = glGetUniformLocation(light_program, "ctm");
	light_view = glGetUniformLocation(light_program, "view_model");
	light_normal = glGetUniformLocation(light_program, "normal_mtx");
	light_diffuse = glGetUniformLocation(light_program, "diffuse");
	light_ambient = glGetUniformLocation(light_program, "ambient");
	light_specular = glGetUniformLocation(light_program, "specular");
	light_shine = glGetUniformLocation(light_program, "shiness");
	light_dir = glGetUniformLocation(light_program, "l_dir");
	light_color = glGetUniformLocation(light_program, "LightColor");
	light_cam = glGetUniformLocation(light_program, "cam");
	shading_mod = glGetUniformLocation(light_program, "flat");
	player_parsing = glGetUniformLocation(light_program, "player");
	light_power1 = glGetUniformLocation(light_program, "light_power1");
	light_power2 = glGetUniformLocation(light_program, "light_power2");
	light_power3 = glGetUniformLocation(light_program, "light_power3");
	light_player_dir = glGetUniformLocation(light_program, "dir");

	program = InitShader("vshader1.glsl", "fshader1.glsl");
	ctmParam = glGetUniformLocation(program, "ctm");
	vColor = glGetUniformLocation(program, "color");
	
	//glUseProgram(light_program);

	//load_obj_files("OBJ files/cu.txt", 0, WALL);
	load_obj_files("OBJ files/dummy_obj_walk_pose_0.obj","OBJ files/dummy_red.jpg", 0, P_0);
	load_obj_files("OBJ files/dummy_obj_walk_pose_1.obj","OBJ files/dummy_red.jpg", 0, P_1);
	load_obj_files("OBJ files/dummy_obj_walk_pose_2.obj","OBJ files/dummy_red.jpg", 0, P_2);
	load_obj_files("OBJ files/dummy_obj_walk_pose_3.obj","OBJ files/dummy_red.jpg", 0, P_3);
	load_obj_files("OBJ files/dummy_obj_gun.obj", "OBJ files/dummy_red.jpg", 2, P_GUN);
	
	
	load_obj_files("OBJ files/Skeleton_pose0.obj","OBJ files/dummy_wood.jpg", 0, E_0);
	load_obj_files("OBJ files/Skeleton_pose1.obj","OBJ files/dummy_wood.jpg", 0, E_1);
	load_obj_files("OBJ files/Skeleton_pose2.obj","OBJ files/dummy_wood.jpg", 0, E_2);
	load_obj_files("OBJ files/Skeleton_pose3.obj","OBJ files/dummy_wood.jpg", 0, E_3);
	

	load_obj_files("OBJ files/M1911.obj","OBJ files/M1911-RIGHT.jpg", 0, GUN);
	load_obj_files("OBJ files/bullet.obj","OBJ files/bullet.jpg", 0, BULL);
	load_obj_files("OBJ files/cu.txt", "OBJ files/bullet.jpg", 0, ITEM);
	load_obj_files_normal("OBJ files/cube.obj", WALL);



	glUseProgram(program);

	glGenVertexArrays(1, &vao[RECT]);
	glBindVertexArray(vao[RECT]);
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	vao_size[RECT] = 4;
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glGenVertexArrays(1, &vao[HEART]);
	glBindVertexArray(vao[HEART]);
	vao_size[HEART] = 6;
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
}
void load_obj_files(string file_path, string texture_path, int type, int index) {
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(&file_path[0], "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return ;
	}
	int num = 0;
	int m_num = 1;
	bool hand_check = false;
	vector<glm::vec3> rhand;
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			if (num == 1) {
				m_num++;
				num = 0;
			}
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			if (num == 0) num = 1;
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];

			if (type == 0 || type == 2) {
				int v3, uv3, t;
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
				if (matches == 9) {
					if (type == 2 && m_num == 17) {
						hand_loc = temp_vertices[vertexIndex[0] - 1];
						rhand.push_back(temp_vertices[vertexIndex[0] - 1]);
						rhand.push_back(temp_vertices[vertexIndex[1] - 1]);
						rhand.push_back(temp_vertices[vertexIndex[2] - 1]);
					}
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[1]);
					uvIndices.push_back(uvIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				}
				else if (matches == 12) {
					if (type == 2 && m_num == 17) {
						hand_loc = temp_vertices[vertexIndex[0] - 1];
						rhand.push_back(temp_vertices[vertexIndex[0] - 1]);
						rhand.push_back(temp_vertices[vertexIndex[1] - 1]);
						rhand.push_back(temp_vertices[vertexIndex[2] - 1]);
						rhand.push_back(temp_vertices[vertexIndex[3] - 1]);
					}
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[1]);
					uvIndices.push_back(uvIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);

					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[2]);
					uvIndices.push_back(uvIndex[3]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[2]);
					normalIndices.push_back(normalIndex[3]);
				}
				else {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return;
				}
			}
			else {
				int v1, v2, v3, v4;
				int uv1, uv2, uv3, uv4;
				int t;
				int matches = fscanf(file, "%d/%d %d/%d %d/%d %d/%d\n", &v1, &uv1, &v2, &uv2, &v3, &uv3, &v4, &uv4);
				if (matches == 8) {
					vertexIndices.push_back(v1);
					vertexIndices.push_back(v2);
					vertexIndices.push_back(v3);
					uvIndices.push_back(uv1);
					uvIndices.push_back(uv2);
					uvIndices.push_back(uv3);

					vertexIndices.push_back(v2);
					vertexIndices.push_back(v3);
					vertexIndices.push_back(v4);
					uvIndices.push_back(uv2);
					uvIndices.push_back(uv3);
					uvIndices.push_back(uv4);
				}
				else if (matches == 6) {
					vertexIndices.push_back(v1);
					vertexIndices.push_back(v2);
					vertexIndices.push_back(v3);
					uvIndices.push_back(uv1);
					uvIndices.push_back(uv2);
					uvIndices.push_back(uv3);
				}

			}
		}
	}
	vec3 hand_loc = accumulate(rhand.begin(), rhand.end(), glm::vec3(0.0, 0.0, 0.0));
	hand_loc = vec3(hand_loc.x / rhand.size(), hand_loc.y / rhand.size(), hand_loc.z / rhand.size());
	std::vector < glm::vec4 > out_vertices;
	std::vector <glm::vec2> out_uv_map;
	std::vector <glm::vec3> out_normal_map, out_normal_map_flat;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 t = temp_vertices[vertexIndex - 1];
		glm::vec4 vertex = glm::vec4(t.x, t.y, t.z, 1.0);
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 t = temp_uvs[uvIndex - 1];
		out_uv_map.push_back(t);
	}
	glm::vec3 sum_vec = vec3(0.0, 0.0, 0.0);
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normal_map.push_back(normal);
		sum_vec += normal;
		
		if (i % 3 == 2) {
			sum_vec /= 3;
			out_normal_map_flat.push_back(sum_vec);
			out_normal_map_flat.push_back(sum_vec);
			out_normal_map_flat.push_back(sum_vec);
			sum_vec = vec3(0.0, 0.0, 0.0);
		}
	}
	
	glGenVertexArrays(1, &vao[index]);
	glBindVertexArray(vao[index]);
	GLuint buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(vec4), &out_vertices[0], GL_STATIC_DRAW);
	vao_size[index] = out_vertices.size();
	loc = glGetAttribLocation(light_program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));	

	//vertex normal setting
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, out_normal_map.size() * sizeof(glm::vec3), &out_normal_map[0], GL_STATIC_DRAW);
	GLuint vNormal = glGetAttribLocation(light_program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(
		vNormal,                          // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		BUFFER_OFFSET(0)                  // array buffer offset
	);
	
	//flat shading setting
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, out_normal_map_flat.size() * sizeof(glm::vec3), &out_normal_map_flat[0], GL_STATIC_DRAW);
	GLuint vNormal_flat = glGetAttribLocation(light_program, "vNormal_flat");
	glEnableVertexAttribArray(vNormal_flat);
	glVertexAttribPointer(
		vNormal_flat,                          // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		BUFFER_OFFSET(0)                  // array buffer offset
	);
	return;
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


	GLint mode = GL_RGB;                   // Set the mode

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, pixels);

	// Output a successful message
	std::cout << "Texture \"" << location << "\" successfully loaded.\n";

	delete datBuff[0];
	delete datBuff[1];
	delete pixels;
	// Delete the two buffers.
	return 0; // Return success code 

}
GLuint loadTGA_glfw(const char * imagepath) {

	glUseProgram(normal_program);
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned int width, height;
	LoadBMP(imagepath, textureID);
	return textureID;
}
void load_obj_files_normal(string file_path, int index) {
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(&file_path[0], "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;
	}
	int num = 0;
	int m_num = 1;
	bool hand_check = false;
	vector<glm::vec3> rhand;
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			if (num == 1) {
				m_num++;
				num = 0;
			}
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	std::vector < glm::vec4 > out_vertices;
	std::vector <glm::vec2> out_uv_map;
	std::vector <glm::vec3> out_normal_map, out_normal_map_flat;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 t = temp_vertices[vertexIndex - 1];
		glm::vec4 vertex = glm::vec4(t.x, t.y, t.z, 1.0);
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 t = temp_uvs[uvIndex - 1];
		out_uv_map.push_back(t);
	}
	glm::vec3 sum_vec = vec3(0.0, 0.0, 0.0);
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normal_map.push_back(normal);
		sum_vec += normal;

		if (i % 3 == 2) {
			sum_vec /= 3;
			out_normal_map_flat.push_back(sum_vec);
			out_normal_map_flat.push_back(sum_vec);
			out_normal_map_flat.push_back(sum_vec);
			sum_vec = vec3(0.0, 0.0, 0.0);
		}
	}
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	for (int i = 0; i < out_vertices.size(); i += 3) {

		// Shortcuts for vertices
		glm::vec4 & v0 = out_vertices[i + 0];
		glm::vec4 & v1 = out_vertices[i + 1];
		glm::vec4 & v2 = out_vertices[i + 2];

		// Shortcuts for UVs
		glm::vec2 & uv0 = out_uv_map[i + 0];
		glm::vec2 & uv1 = out_uv_map[i + 1];
		glm::vec2 & uv2 = out_uv_map[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = vec3((v1 - v0).x, (v1 - v0).y, (v1 - v0).z);
		glm::vec3 deltaPos2 = vec3((v2 - v0).x, (v2 - v0).y, (v2 - v0).z);

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		// Same thing for binormals
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
	}
	//position
	glGenVertexArrays(1, &vao[index]);
	glBindVertexArray(vao[index]);
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(vec4), &out_vertices[0], GL_STATIC_DRAW);
	vao_size[index] = out_vertices.size();
	GLuint loc = glGetAttribLocation(normal_program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//uv
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, out_uv_map.size() * sizeof(vec2), &out_uv_map[0], GL_STATIC_DRAW);
	loc = glGetAttribLocation(normal_program, "_uv");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//normal
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, out_normal_map.size() * sizeof(vec3), &out_normal_map[0], GL_STATIC_DRAW);
	loc = glGetAttribLocation(normal_program, "vNormal");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//tangent
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(vec3), &tangents[0], GL_STATIC_DRAW);
	loc = glGetAttribLocation(normal_program, "tangent");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//bitangent
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, bitangents.size() * sizeof(vec3), &bitangents[0], GL_STATIC_DRAW);
	loc = glGetAttribLocation(normal_program, "bitangent");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


	GLuint NormalTexture = loadTGA_glfw("OBJ files/wall/normal.bmp");
	GLuint NormalTextureID = glGetUniformLocation(normal_program, "NormalTextureSampler");
	glUniform1i(NormalTextureID, 0);
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
		break;
	case 'c':
		newmap.change_shading_mode();
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
	if (newmap.isEnd()) {
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