#include "display.h"
#include <vector>
using namespace glm;
using namespace std;
GLuint program;
GLint ctmParam;
glm::mat4 ortho_mat;
GLint vColor;
treenode * player_down;
treenode * player_up;
treenode * player_left;
treenode * player_right;


void make_player_up_down(treenode * player,vec4 torso_color) {
	//torso
	treenode * torso = player;
	torso->m = glm::translate(glm::mat4(1.0), vec3(0.4, 0.4, 0.0));
	torso->s = glm::scale(glm::mat4(1.0), vec3(0.4, 0.4, 0.0));
	torso->color = torso_color;

	//head
	treenode * head = torso->child = new treenode();
	head->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.4, 0.0));
	head->s = glm::scale(glm::mat4(1.0), vec3(0.2, 0.2, 0.0));
	head->color = vec4(0.0, 0.3, 0.7, 1.0);

	//left upper_leg
	treenode * left_upper_leg = head->sibling = new treenode();
	left_upper_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_upper_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_upper_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->color = vec4(0.0, 0.3, 0.7, 1.0);

	//left lower_leg
	treenode * left_lower_leg = left_upper_leg->child = new treenode();
	left_lower_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_lower_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_lower_leg->color = vec4(1, 0.3, 0.7, 1.0);
	left_lower_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	left_lower_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	
	//right upper_leg
	treenode * right_upper_leg = left_upper_leg->sibling = new treenode();
	right_upper_leg->m = glm::translate(glm::mat4(1.0), vec3(0.3, -0.2, 0.0));
	right_upper_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_upper_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->color = vec4(0.0, 0.3, 0.7, 1.0);

	//right lower_leg
	treenode * right_lower_leg = right_upper_leg->child = new treenode();
	right_lower_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	right_lower_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_lower_leg->color = vec4(1, 0.3, 0.7, 1.0);
	right_lower_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.15, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	right_lower_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.15, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));

	//left_upper_arm
	treenode * left_upper_arm = right_upper_leg->sibling = new treenode();
	left_upper_arm->m = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.2, 0.0));
	left_upper_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_upper_arm->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_arm->color = vec4(1.0, 0.0, 0.0, 1.0);

	//left_lower_arm
	treenode * left_lower_arm = left_upper_arm->child = new treenode();
	left_lower_arm->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_lower_arm->color = vec4(1.0, 1.0, 0.3, 1.0);
	left_lower_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 2.0f, vec3(0.0, 0.0, 1.0));
	left_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	//left_lower_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 2.0f, vec3(0.0, 0.0, 1.0));
	

	//right_upper_arm
	treenode * right_upper_arm = left_upper_arm->sibling = new treenode();
	right_upper_arm->m = glm::translate(glm::mat4(1.0), vec3(0.4, 0.2, 0.0));
	right_upper_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_upper_arm->color = vec4(1.0, 0.0, 0.0, 1.0);
	right_upper_arm->jump1 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	
	//left_lower_arm
	treenode * right_lower_arm = right_upper_arm->child = new treenode();
	right_lower_arm->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	right_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_lower_arm->color = vec4(1.0, 1.0, 0.3, 1.0);
	right_lower_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0)); glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 3.0f, vec3(0.0, 0.0, 1.0));

	//customize up_down
	if (player == player_down) {
		left_lower_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.1, 0.2, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
		right_lower_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 1.14f, vec3(0.0, 0.0, 1.0));
		//gun1
		treenode * gun = left_lower_arm->child = new treenode();
		gun->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
		gun->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
		gun->color = vec4(0.0, 0.0, 0.0, 1.0);
		gun->is_gun = true;

		//gun2
		treenode * gun2 = gun->child = new treenode();
		gun2->m = glm::rotate(glm::mat4(1.0), 0.0f, vec3(0.0, 0.0, 1.0));
		gun2->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.1, 0.0));
		gun2->color = vec4(0.0, 0.0, 0.0, 1.0);
		gun2->is_gun = true;
	}
	else {
		left_upper_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
		right_upper_arm->gun = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
		//gun1
		treenode * gun = left_lower_arm->child = new treenode();
		gun->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
		gun->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
		gun->color = vec4(0.0, 0.0, 0.0, 1.0);
		gun->is_gun = true;

		//gun2
		treenode * gun2 = gun->child = new treenode();
		gun2->m = glm::rotate(glm::mat4(1.0), 2.0f, vec3(0.0, 0.0, 1.0));
		gun2->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.1, 0.0));
		gun2->color = vec4(0.0, 0.0, 0.0, 1.0);
		gun2->is_gun = true;
	}
}

mat4 model_view;
vector<glm::mat4> stack_mat;

void draw(mat4 s, vec4 color) {
	mat4 final_mat = model_view * s;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}

void traverse(treenode* root,int state) {
	//state ==0 normal
	//state == 1 jump1
	//state == 2 jump2
	//state == 3 jump3
	//state == 4 gun
	
	if (state!=4 && root->is_gun == true) return;
	if (root == NULL) return;
	stack_mat.push_back(model_view);
	if(state == 4) model_view = model_view * root->m * root->jump1 * root->gun;
	else if (state == 3) model_view = model_view * root->m * root->jump2;
	else if (state == 2) model_view = model_view * root->m * root->jump1;
	else if (state == 1) model_view = model_view * root->m * root->jump3;
	else model_view = model_view * root->m;
	
	draw(root->s, root->color);
	if (root->child != NULL)
	traverse(root->child,state);
	model_view = stack_mat.back();
	stack_mat.pop_back();
	if (root->sibling != NULL)
	traverse(root->sibling,state);
	return;
}
void make_player() {
	player_down = new treenode();
	player_up = new treenode();
	make_player_up_down(player_down,vec4(0.0,0.0,1.0,1.0));
	make_player_up_down(player_up,vec4(0.0,0.0,0.0,1.0));
}