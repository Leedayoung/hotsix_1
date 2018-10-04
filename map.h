#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
using namespace std;
enum map_info { wall, empty, item };
class Map {
private:
	int map_size;
	int** map_arr;
	int numb_enemy;
	vector <int> loc_wall;
	vector<Enemy> enem_vec;
	vector<Bullet> bull_vec;
	Player player;
	int basic_mode = 0;
	int random_mode = 1;
	int item_numb;
	int bull_length = 4;
	bool win;
public:
	Map();
	void wall_maker();
	void world_init();
	void map_init();
	void object_init();
	void enemy_init();
	void player_init(int mode);
	void item_init();
	int get_numb_enemy();
	vector<Enemy>& get_enem_vec();
	Player& get_player();
	vector<Bullet>& get_bullet_vec();
	int get_map_size();
	int** get_map_arr();
	bool check_range(pair<int, int> pos);
	bool check_wall(pair<int, int> pos);
	bool update_enemies();
	bool kill_enemies(pair<int, int> pos);
	void update_bullets();
	void create_bullet();
	//Player에 대하여 Valid한 Move후 Direction update
	void valid_move(int dir);
	//현재 위치의 item을 주워 없앤 뒤 empty를 return함
	bool get_item();
	bool isEnd();
	bool get_win();
};
