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
#define v_size 50
#define DEBUG 20

extern GLuint program;
extern GLint ctmParam;
extern glm::mat4 ortho_mat;
extern GLint vColor;
extern mat4 model_view;
extern	GLuint buffer[2];
extern GLuint vao[v_size];
extern int vao_size[v_size];
extern GLuint loc;
extern mat4 per_look;
extern mat4 look_at;
extern mat4 perspec;
extern vec3 hand_loc;
extern bool shading_mode;
extern vec4 cam_position;

extern GLuint light_program;
extern GLint light_ctm;
extern GLint light_view;
extern GLint light_normal;
extern GLint light_diffuse;
extern GLint light_ambient;
extern GLint light_specular;
extern GLint light_shine;
extern GLint light_dir;
extern GLint light_color;
extern GLint light_cam;
extern GLint shading_mod;
extern GLint player_parsing;
extern GLint light_power1;
extern GLint light_power2;
extern GLint light_power3;
extern GLint light_player_dir;

extern GLint v_mod;
extern GLint p_loc;
extern GLint p_dir;
extern GLint p_col;

extern vec3 point_light_loc;
extern vec3 point_light_dir;
extern vec4 point_light_col;


#define LIFE_LIST_COLOR vec4(1.0, 1.0, 0.0, 1.0)
#define LIFE_COLOR vec4(1.0, 0.0, 0.0, 1.0)
#define WALL_COLOR vec4(0.58, 0.29, 0.0, 1.0)
#define ITEM_COLOR vec4(1.0, 0.0, 0.0, 1.0)
#define PLAYER_COLOR vec4(0.01, 0.5, 0.5, 0.5)
#define BULLET_COLOR vec4(0.7, 0.0, 0.7, 1.0)
#define ENEMY_COLOR vec4(0.8, 0.8, 0.8, 0.5)
#define BACK_COLOR vec4(0.5, 0.5, 0.5, 1.0)
#define GUN_COLOR vec4(0.3, 0.3, 0.3, 0.5)
#define TIME_SEG_COLOR vec4(1.0, 0.7, 0.7, 1.0)


#define P_0 0
#define P_1 1
#define P_2 2
#define P_3 3

#define E_0 4
#define E_1 5
#define E_2 6
#define E_3 7


#define GUN v_size-4
#define P_GUN v_size-3
#define RECT 8
#define HEART 9
#define BULL v_size-2
#define WALL v_size-1
#define ITEM v_size-1


class treenode {
public:
	mat4 m;
	mat4 s;
	mat4 jump1;
	mat4 jump2;
	mat4 jump3;
	mat4 gun;
	vec4 color;
	bool is_gun;
	bool left;
	void(*f)(mat4 s);
	treenode * sibling;
	treenode * child;
	treenode() {
		sibling = NULL;
		child = NULL;
		jump1 = glm::mat4(1.0);
		jump2 = glm::mat4(1.0);
		jump3 = glm::mat4(1.0);
		gun = glm::mat4(1.0);
		is_gun = false;
		left = false;
	}
};

extern treenode * player_down;
extern treenode * player_up;
extern treenode * player_left;

extern treenode * enemy_down;
extern treenode * enemy_up;
extern treenode * enemy_left;

void make_player();
void traverse(treenode* root,int state);
