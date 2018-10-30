#pragma once
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
void draw_seven_seg(int num, int pos);
void draw_a(mat4 trans_mtx_base);
void draw_b(mat4 trans_mtx_base);
void draw_c(mat4 trans_mtx_base);
void draw_d(mat4 trans_mtx_base);
void draw_e(mat4 trans_mtx_base);
void draw_f(mat4 trans_mtx_base);
void draw_g(mat4 trans_mtx_base);
void draw_dots(mat4 trans_mtx_base);


