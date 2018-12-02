
#include "sevenseg.h"
#include <vector>
#include "display.h"


mat4 scale_mtx_row;
mat4 scale_mtx_col;
mat4 scale_dots;
double width = 0.01;
double height = 0.03;
double gap = 0.06;

void draw_seven_seg(int num, int pos) {
	glBindVertexArray(vao[RECT]);
	mat4 trans_mtx_base;
	scale_mtx_row = glm::scale(glm::mat4(1.0), glm::vec3(height, width, 0.0));
	scale_mtx_col = glm::scale(glm::mat4(1.0), glm::vec3(width, height, 0.0));
	scale_dots = glm::scale(glm::mat4(1.0), glm::vec3(width, width, 0.0));
	switch (pos) {
	case 0:
		trans_mtx_base = glm::translate(glm::mat4(1.0), glm::vec3(0.9, 0.9, 0));
		break;
	case 1:
		trans_mtx_base = glm::translate(glm::mat4(1.0), glm::vec3(0.9-gap, 0.9, 0));
		break;
	case 2:
		trans_mtx_base = glm::translate(glm::mat4(1.0), glm::vec3(0.9 - 2* gap-0.02, 0.9, 0));
		break;
	case 3:
		trans_mtx_base = glm::translate(glm::mat4(1.0), glm::vec3(0.9 - 3* gap-0.02, 0.9, 0));
		break;
	case -1:
		trans_mtx_base = glm::translate(glm::mat4(1.0), glm::vec3(0.9 - 2 * gap, 0.9, 0));
		break;

	}
	switch (num) {
	case 0:
		draw_a(trans_mtx_base);
		draw_b(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_d(trans_mtx_base);
		draw_e(trans_mtx_base);
		draw_f(trans_mtx_base);
		break;
	case 1:
		draw_b(trans_mtx_base);
		draw_c(trans_mtx_base);
		break;
	case 2:
		draw_a(trans_mtx_base);
		draw_b(trans_mtx_base);
		draw_d(trans_mtx_base);
		draw_e(trans_mtx_base);
		draw_g(trans_mtx_base);
		break;
	case 3:
		draw_a(trans_mtx_base);
		draw_b(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_d(trans_mtx_base);
		draw_g(trans_mtx_base);
		break;
	case 4:
		draw_b(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_f(trans_mtx_base);
		draw_g(trans_mtx_base);
		break;
	case 5:
		draw_a(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_d(trans_mtx_base);
		draw_f(trans_mtx_base);
		draw_g(trans_mtx_base);
		break;
	case 6: 
		draw_a(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_d(trans_mtx_base);
		draw_e(trans_mtx_base);
		draw_f(trans_mtx_base);
		draw_g(trans_mtx_base);
		break;
	case 7:
		draw_a(trans_mtx_base);
		draw_b(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_f(trans_mtx_base);
		break;
	case 8:
		draw_a(trans_mtx_base);
		draw_b(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_d(trans_mtx_base);
		draw_e(trans_mtx_base);
		draw_f(trans_mtx_base);
		draw_g(trans_mtx_base);
		break;
	case 9:
		draw_a(trans_mtx_base);
		draw_b(trans_mtx_base);
		draw_c(trans_mtx_base);
		draw_f(trans_mtx_base);
		draw_g(trans_mtx_base);
		break;
	case -1:
		draw_dots(trans_mtx_base);
	}
}

void draw_a(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width, 2*width+2*height, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_b(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width+height, 2 * width + height, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_c(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width + height, width, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_d(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width,0, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_e(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(0, width, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_f(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(0, 2 * width + height, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_col;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_g(mat4 trans_mtx_base) {
	mat4 trans_mtx = glm::translate(trans_mtx_base, glm::vec3(width, width + height, 0));
	mat4 final_mtx = trans_mtx*scale_mtx_row;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void draw_dots(mat4 trans_mtx_base) {
	mat4 trans_mtx1 = glm::translate(trans_mtx_base, glm::vec3(width + height, 2 * width + height, 0));
	mat4 final_mtx1 = trans_mtx1*scale_dots;
	vec4 vec_color = TIME_SEG_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx1[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	mat4 trans_mtx2 = glm::translate(trans_mtx_base, glm::vec3(width + height, height, 0));
	mat4 final_mtx2 = trans_mtx2*scale_dots;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mtx2[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}