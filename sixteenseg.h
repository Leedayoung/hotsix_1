#pragma once
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

void draw_string(string str, double x, double y);
void draw_char(char ch, mat4 trans_mtx);
void draw_a1(mat4 trans_mtx_base);
void draw_a2(mat4 trans_mtx_base);
void draw_a3(mat4 trans_mtx_base);
void draw_a4(mat4 trans_mtx_base);
void draw_a5(mat4 trans_mtx_base);
void draw_a6(mat4 trans_mtx_base);
void draw_b1(mat4 trans_mtx_base);
void draw_b2(mat4 trans_mtx_base);
void draw_b3(mat4 trans_mtx_base);
void draw_b4(mat4 trans_mtx_base);
void draw_b5(mat4 trans_mtx_base);
void draw_b6(mat4 trans_mtx_base);
void draw_c1(mat4 trans_mtx_base);
void draw_c2(mat4 trans_mtx_base);
void draw_c3(mat4 trans_mtx_base);
void draw_c4(mat4 trans_mtx_base);

