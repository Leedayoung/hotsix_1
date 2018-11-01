#include <vector>
#include "display.h"
#include "sixteenseg.h"
#include <iostream>
#include <math.h>

using namespace std;

mat4 scale_mtx_row_s;
mat4 scale_mtx_col_s;
double width1 = 0.02;
double height1 = 0.01;
double width2 = 0.01;
double height2 = 0.04;
float ang = (float)atan(width2 / width1);
double gap_s = width1 * 3 + 3*width2;
float gap_diag = 0.003;

void draw_string(string str, double x, double y) {
	scale_mtx_row_s = glm::scale(glm::mat4(1.0), glm::vec3(width1, height1, 0.0));
	scale_mtx_col_s = glm::scale(glm::mat4(1.0), glm::vec3(width2, height2, 0.0));
	mat4 trans_base_mtx = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0));
	mat4 trans_mtx;
	for (int i = 0; i < int(str.size()); i++) {
		trans_mtx = glm::translate(trans_base_mtx, glm::vec3(i*gap_s, 0, 0));
		draw_char(str[i], trans_mtx);
	}
}
void draw_char(char ch, mat4 trans_mtx) {
	switch (ch) {
	case 'A':
		draw_a1(trans_mtx);
		draw_a2(trans_mtx);
		draw_a4(trans_mtx);
		draw_a5(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'B':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a5(trans_mtx);
		draw_a6(trans_mtx);
		draw_b3(trans_mtx);
		draw_b4(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'C':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		break;
	case 'D':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a6(trans_mtx);
		draw_b3(trans_mtx);
		draw_b4(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'E':
		draw_a1(trans_mtx);
		draw_a2(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		break;
	case 'F':
		draw_a1(trans_mtx);
		draw_a2(trans_mtx);
		draw_a4(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		break;
	case 'G':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a5(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'H':
		draw_a2(trans_mtx);
		draw_a5(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'I':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a6(trans_mtx);
		draw_b3(trans_mtx);
		draw_b4(trans_mtx);
		break;
	case 'J':
		draw_a3(trans_mtx);
		draw_a6(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'K':
		draw_a2(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_c3(trans_mtx);
		draw_c4(trans_mtx);
		break;
	case 'L':
		draw_a3(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		break;
	case 'M':
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		draw_c1(trans_mtx);
		draw_c3(trans_mtx);
		break;
	case 'N':
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		draw_c1(trans_mtx);
		draw_c4(trans_mtx);
		break;
	case'O':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'P':
		draw_a1(trans_mtx);
		draw_a2(trans_mtx);
		draw_a4(trans_mtx);
		draw_a5(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		break;
	case 'Q':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		draw_c4(trans_mtx);
		break;
	case 'R':
		draw_a1(trans_mtx);
		draw_a2(trans_mtx);
		draw_a4(trans_mtx);
		draw_a5(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_c4(trans_mtx);
		break;
	case 'S':
		draw_a1(trans_mtx);
		draw_a2(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a5(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'T':
		draw_a1(trans_mtx);
		draw_a4(trans_mtx);
		draw_b3(trans_mtx);
		draw_b4(trans_mtx);
		break;
	case 'U':
		draw_a3(trans_mtx);
		draw_a6(trans_mtx);
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		break;
	case 'V':
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_c2(trans_mtx);
		draw_c3(trans_mtx);
		break;
	case'W':
		draw_b1(trans_mtx);
		draw_b2(trans_mtx);
		draw_b5(trans_mtx);
		draw_b6(trans_mtx);
		draw_c2(trans_mtx);
		draw_c4(trans_mtx);
		break;
	case'X':
		draw_c1(trans_mtx);
		draw_c2(trans_mtx);
		draw_c3(trans_mtx);
		draw_c4(trans_mtx);
		break;
	case 'Y':
		draw_a2(trans_mtx);
		draw_a5(trans_mtx);
		draw_b1(trans_mtx);
		draw_b4(trans_mtx);
		draw_b5(trans_mtx);
		break;
	case 'Z':
		draw_a1(trans_mtx);
		draw_a3(trans_mtx);
		draw_a4(trans_mtx);
		draw_a6(trans_mtx);
		draw_c2(trans_mtx);
		draw_c3(trans_mtx);
		break;
	}


	/*
	draw_a1(trans_mtx);
	draw_a2(trans_mtx);
	draw_a3(trans_mtx);
	draw_a4(trans_mtx);
	draw_a5(trans_mtx);
	draw_a6(trans_mtx);
	draw_b1(trans_mtx);
	draw_b2(trans_mtx);
	draw_b3(trans_mtx);
	draw_b4(trans_mtx);
	draw_b5(trans_mtx);
	draw_b6(trans_mtx);
	draw_c1(trans_mtx);
	draw_c2(trans_mtx);
	draw_c3(trans_mtx);
	draw_c4(trans_mtx);
	break;
	*/
}

void draw_a1(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width2, height1*2+height2*2 , 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_a2(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width2, height1 + height2, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_a3(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width2, 0, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_a4(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width2*2+width1, height1 * 2 + height2*2, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_a5(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width2 * 2 + width1, height1  + height2, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_a6(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width2 * 2 + width1, 0, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_b1(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(0, 2*height1+height2, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_b2(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(0, height1, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_b3(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width1+width2, 2 * height1 + height2, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_b4(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width1 + width2, height1, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_b5(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(2*width1 + 2*width2, 2 * height1 + height2, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_b6(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(2 * width1 + 2 * width2, height1, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void draw_c1(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width1+width2-gap_diag, 2*height1+height2+ gap_diag, 0));
	mat4 rot_mtx = glm::rotate(glm::mat4(1.0), ang, vec3(0, 0, 1));
	mat4 final_mtx = trans_mtx*rot_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_c2(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(gap_diag, height1 + gap_diag, 0));
	mat4 rot_mtx = glm::rotate(glm::mat4(1.0), -ang, vec3(0, 0, 1));
	mat4 final_mtx = trans_mtx*rot_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_c3(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width1 + width2 + gap_diag, 2 * height1 + height2 + gap_diag, 0));
	mat4 rot_mtx = glm::rotate(glm::mat4(1.0), -ang, vec3(0, 0, 1));
	mat4 final_mtx = trans_mtx*rot_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_c4(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(2 * width1 + 2 * width2 - gap_diag, height1 + gap_diag, 0));
	mat4 rot_mtx = glm::rotate(glm::mat4(1.0), ang, vec3(0, 0, 1));
	mat4 final_mtx = trans_mtx*rot_mtx*scale_mtx_col_s;
	vec4 vec_color = vec4(1.0, 0.0, 0.1, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

