#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include "Enemy.h"
using namespace std;
enum map_info { wall, empty, item };
extern GLuint texture[16];
#define map_size 70
class Map {
private:
	
	int view_size;
	int** map_arr;
	int numb_enemy;
	vector <int> loc_wall;
	vector<Enemy> enem_vec;
	vector<Bullet> bull_vec;
	Player player;
	int basic_mode = 0;
	int random_mode = 1;
	int item_numb;
	int bull_length = 8;
	bool win;
	bool end;
	int time_limit;
	int mode = 0;
public:
	Map();
	void draw_map(int y, int x, int e_map[map_size][map_size], Enemy e_list[50], int b_map[map_size][map_size], Bullet b_list[50]);
	bool get_end();
	void timer();
	void print(int x, int y, string string);
	void draw_rec(int x1, int y1, int x2, int y2);
	void display();
	void wall_maker();
	void world_init();
	void map_init();
	void object_init();
	void enemy_init();
	void player_init(int mode);
	void item_init();
	int get_numb_enemy();
	int get_map_size();
	int** get_map_arr();
	bool check_range(pair<int, int> pos);
	bool check_wall(pair<int, int> pos);
	bool update_enemies();
	bool kill_enemies(pair<float, float> pos);
	void update_bullets();
	void create_bullet();
	void valid_move(int dir);
	void valid_move_3d();
	void rotate_3d(int dir);
	bool get_item(pair<int, int> current);
	bool isEnd();
	bool get_win();
	void change_mode();
};