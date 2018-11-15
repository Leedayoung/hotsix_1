#include "display.h"
#include <vector>
using namespace glm;
using namespace std;
GLuint program;
GLint ctmParam;
glm::mat4 ortho_mat;
GLint vColor;
GLuint buffer[2];
GLuint vao[3];
int vao_size[3];
GLuint loc;
mat4 per_look;
mat4 look_at;
mat4 perspec;
treenode * player_down;
treenode * player_up;
treenode * player_left;

treenode * enemy_down;
treenode * enemy_up;
treenode * enemy_left;


void make_character_up_down(treenode * player,bool set_color) {
	vec4 grey = vec4(0.5, 0.5, 0.5, 1.0);
	//torso
	treenode * torso = player;
	torso->m = glm::translate(glm::mat4(1.0), vec3(0.4, 0.4, 0.0));
	torso->s = glm::scale(glm::mat4(1.0), vec3(0.4, 0.4, 0.0));
	torso->color = set_color? vec4(0.0, 0.0, 1.0, 1.0): vec4(0.7, 0.7, 0.7, 1.0);

	//head
	treenode * head = torso->child = new treenode();
	head->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.4, 0.0));
	head->s = glm::scale(glm::mat4(1.0), vec3(0.2, 0.2, 0.0));
	head->color = set_color? vec4(0.0, 0.3, 0.7, 1.0):grey;

	//left upper_leg
	treenode * left_upper_leg = head->sibling = new treenode();
	left_upper_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_upper_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_upper_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->color = set_color? vec4(0.0, 0.3, 0.7, 1.0) : grey;

	//left lower_leg
	treenode * left_lower_leg = left_upper_leg->child = new treenode();
	left_lower_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_lower_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_lower_leg->color = set_color? vec4(1, 0.3, 0.7, 1.0) : grey;
	left_lower_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	left_lower_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	
	//right upper_leg
	treenode * right_upper_leg = left_upper_leg->sibling = new treenode();
	right_upper_leg->m = glm::translate(glm::mat4(1.0), vec3(0.3, -0.2, 0.0));
	right_upper_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_upper_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->color = set_color ? vec4(0.0, 0.3, 0.7, 1.0) : grey;

	//right lower_leg
	treenode * right_lower_leg = right_upper_leg->child = new treenode();
	right_lower_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	right_lower_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_lower_leg->color = set_color?vec4(1, 0.3, 0.7, 1.0):grey;
	right_lower_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.15, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	right_lower_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.15, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));

	//left_upper_arm
	treenode * left_upper_arm = right_upper_leg->sibling = new treenode();
	left_upper_arm->m = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.2, 0.0));
	left_upper_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_upper_arm->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_arm->color = set_color?vec4(1.0, 0.0, 0.0, 1.0):grey;

	//left_lower_arm
	treenode * left_lower_arm = left_upper_arm->child = new treenode();
	left_lower_arm->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_lower_arm->color = set_color?vec4(1.0, 1.0, 0.3, 1.0):grey;
	left_lower_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 2.0f, vec3(0.0, 0.0, 1.0));
	left_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	//left_lower_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 2.0f, vec3(0.0, 0.0, 1.0));
	

	//right_upper_arm
	treenode * right_upper_arm = left_upper_arm->sibling = new treenode();
	right_upper_arm->m = glm::translate(glm::mat4(1.0), vec3(0.4, 0.2, 0.0));
	right_upper_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_upper_arm->color = set_color?vec4(1.0, 0.0, 0.0, 1.0):grey;
	right_upper_arm->jump1 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	
	//left_lower_arm
	treenode * right_lower_arm = right_upper_arm->child = new treenode();
	right_lower_arm->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	right_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_lower_arm->color = set_color?vec4(1.0, 1.0, 0.3, 1.0):grey;
	right_lower_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0)); glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 3.0f, vec3(0.0, 0.0, 1.0));

	//customize up_down
	if (player == player_down || player == enemy_down) {
		left_lower_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.1, 0.2, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
		right_lower_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 1.14f, vec3(0.0, 0.0, 1.0));
		//gun1
		treenode * gun = left_lower_arm->child = new treenode();
		gun->m = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.2, 0.0));
		gun->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
		gun->color = set_color?vec4(0.0, 0.0, 0.0, 1.0):grey;
		gun->is_gun = true;

		//gun2
		treenode * gun2 = gun->child = new treenode();
		gun2->m = glm::rotate(glm::mat4(1.0), 0.0f, vec3(0.0, 0.0, 1.0)) * glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0));;
		gun2->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.1, 0.0));
		gun2->color = set_color?vec4(0.0, 0.0, 0.0, 1.0):grey;
		gun2->is_gun = true;
	}
	else {
		treenode * cloth = right_upper_arm->sibling = new treenode();
		cloth->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.1, 0.0));
		cloth->s = glm::scale(glm::mat4(1.0), vec3(0.2, 0.3, 0.0));
		cloth->color = vec4(0.0, 0.0, 0.0, 1.0);

		left_upper_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
		right_upper_arm->gun = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
		//gun1
		treenode * gun = left_lower_arm->child = new treenode();
		gun->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
		gun->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
		gun->color = set_color?vec4(0.0, 0.0, 0.0, 1.0):grey;
		gun->is_gun = true;

		//gun2
		treenode * gun2 = gun->child = new treenode();
		gun2->m = glm::rotate(glm::mat4(1.0), 2.0f, vec3(0.0, 0.0, 1.0));
		gun2->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.1, 0.0));
		gun2->color = set_color?vec4(0.0, 0.0, 0.0, 1.0):grey;
		gun2->is_gun = true;
	}
}
void make_character_left_right(treenode * player, bool set_color) {
	vec4 grey = vec4(0.5, 0.5, 0.5, 1.0);
	//torso
	treenode * torso = player;
	torso->m = glm::translate(glm::mat4(1.0), vec3(0.4, 0.4, 0.0));
	torso->s = glm::scale(glm::mat4(1.0), vec3(0.3, 0.4, 0.0));
	torso->color = set_color?vec4(0.0, 0.0, 1.0, 1.0): vec4(0.7, 0.7, 0.7, 1.0);

	//head
	treenode * head = torso->child = new treenode();
	head->m = glm::translate(glm::mat4(1.0), vec3(0.05, 0.4, 0.0));
	head->s = glm::scale(glm::mat4(1.0), vec3(0.2, 0.2, 0.0));
	head->color = set_color?vec4(0.0, 0.3, 0.7, 1.0): grey;

	//left upper_leg
	treenode * left_upper_leg = head->sibling = new treenode();
	left_upper_leg->m = glm::translate(glm::mat4(1.0), vec3(0.1, -0.2, 0.0));
	left_upper_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	//left_upper_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	//left_upper_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.15, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_leg->color = set_color?vec4(0.0, 0.3, 0.7, 1.0): grey;

	//left lower_leg
	treenode * left_lower_leg = left_upper_leg->child = new treenode();
	left_lower_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_lower_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_lower_leg->color = set_color?vec4(1, 0.3, 0.7, 1.0): grey;
	left_lower_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(0.17, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	left_lower_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(0.17, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	//left_lower_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	//left_lower_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));

	//right upper_leg
	treenode * right_upper_leg = left_upper_leg->sibling = new treenode();
	right_upper_leg->m = glm::translate(glm::mat4(1.0), vec3(0.1, -0.2, 0.0));
	right_upper_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	//right_upper_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->jump2 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	right_upper_leg->color = set_color?vec4(0.0, 0.3, 0.7, 1.0): grey;

	//right lower_leg
	treenode * right_lower_leg = right_upper_leg->child = new treenode();
	right_lower_leg->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	right_lower_leg->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_lower_leg->color = set_color?vec4(1, 0.3, 0.7, 1.0): grey;
	//right_lower_leg->jump1 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.15, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	//right_lower_leg->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.15, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));

	//left_upper_arm
	treenode * left_upper_arm = right_upper_leg->sibling = new treenode();
	left_upper_arm->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_upper_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	//left_upper_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	//left_upper_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_upper_arm->color = set_color?vec4(1.0, 0.0, 0.0, 1.0): grey;
	left_upper_arm->gun = glm::translate(glm::mat4(1.0), vec3(-0.1, 0.1, 0.0)) * glm::rotate(glm::mat4(1.0), -1.5f, vec3(0.0, 0.0, 1.0));
	
	//left_lower_arm
	treenode * left_lower_arm = left_upper_arm->child = new treenode();
	left_lower_arm->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	left_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	left_lower_arm->color = set_color?vec4(1.0, 1.0, 0.3, 1.0): grey;
	left_lower_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(-0.15, 0.15, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	left_lower_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(0.15, 0.05, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	//left_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	//left_lower_arm->gun = glm::scale(glm::mat4(1.0), vec3(0.0, 0.0, 0.0));


	//right_upper_arm
	treenode * right_upper_arm = left_upper_arm->sibling = new treenode();
	right_upper_arm->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_upper_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_upper_arm->color = set_color?vec4(1.0, 0.0, 0.0, 1.0): grey;
	right_upper_arm->gun = left_upper_arm->gun;
	//right_upper_arm->jump2 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));
	//right_upper_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(0.1, 0.0, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0));

	//right_lower_arm
	treenode * right_lower_arm = right_upper_arm->child = new treenode();
	right_lower_arm->m = glm::translate(glm::mat4(1.0), vec3(0.0, -0.2, 0.0));
	right_lower_arm->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	right_lower_arm->color = set_color ? vec4(1.0, 1.0, 0.3, 1.0): grey;
	right_lower_arm->jump2 = left_lower_arm->jump2;
	right_lower_arm->jump3 = left_lower_arm->jump3;
	//right_lower_arm->gun = glm::scale(glm::mat4(1.0), vec3(0.0, 0.0, 0.0));
	//right_lower_arm->gun = glm::scale(glm::mat4(1.0), vec3(0.1, 0.2, 0.0));
	//right_lower_arm->jump3 = glm::translate(glm::mat4(1.0), vec3(0.2, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 1.0f, vec3(0.0, 0.0, 1.0)); glm::translate(glm::mat4(1.0), vec3(0.0, 0.1, 0.0))*glm::rotate(glm::mat4(1.0), 3.0f, vec3(0.0, 0.0, 1.0));
	
	treenode * cloth = right_upper_arm->sibling = new treenode();
	cloth->m = glm::translate(glm::mat4(1.0), vec3(0.25, 0.1, 0.0));
	cloth->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
	cloth->color = vec4(0.0, 0.0, 0.0, 1.0);
	//left_lower_arm->gun = glm::translate(glm::mat4(1.0), vec3(0.1, 0.2, 0.0))*glm::rotate(glm::mat4(1.0), -1.0f, vec3(0.0, 0.0, 1.0));
	
	treenode * gun = left_lower_arm->child = new treenode();
	gun->m = glm::translate(glm::mat4(1.0), vec3(-0.1, -0.3, 0.0));
	gun->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.3, 0.0));
	gun->color = vec4(0.0, 0.0, 0.0, 1.0);
	gun->is_gun = true;

	//gun2
	treenode * gun2 = gun->child = new treenode();
	gun2->m = glm::rotate(glm::mat4(1.0), 0.0f, vec3(0.0, 0.0, 1.0)) * gun->m = glm::translate(glm::mat4(1.0), vec3(0.1, 0.15, 0.0));;
	gun2->s = glm::scale(glm::mat4(1.0), vec3(0.1, 0.1, 0.0));
	gun2->color = vec4(0.0, 0.0, 0.0, 1.0);
	gun2->is_gun = true;
	
	//customize up_down
	/*if (player == player_down) {
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
	}*/
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
	make_character_up_down(player_down,true);
	make_character_up_down(player_up,true);

	player_left = new treenode();
	make_character_left_right(player_left,true);
	
	enemy_down = new treenode();
	enemy_up = new treenode();
	make_character_up_down(enemy_down,false);
	make_character_up_down(enemy_up,false);

	enemy_left = new treenode();
	make_character_left_right(enemy_left,false);
}