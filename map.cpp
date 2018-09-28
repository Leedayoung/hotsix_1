#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
using namespace std;

class Map {
private:
	enum map_info { wall, empty, item };
	int map_size;
	int** map_arr;
	vector <int> loc_wall;
	vector<Enemy> enem_vec;
	vector<Bullet> bull_vec;
	Player player;
	int basic_mode = 0;
	int random_mode = 1;
	int item_numb;

public:
	Map() {
		world_init();
		map_init();
		object_init();
	}
	void world_init() {
		map_arr = new int*[map_size];
		for (int i = 0; i < map_size; ++i)
			map_arr[i] = new int[map_size];
	}
	void map_init() {
		for (int i = 0; i < map_size; ++i) {
			for (int j = 0; j < map_size; ++j) {
				map_arr[i][j] = empty;
			}
		}
		for (int i = 0; i < loc_wall.size(); ++i) {
			map_arr[loc_wall[i] % map_size][loc_wall[i] / map_size] = wall;
		}

	}
	void object_init() {
		enemy_init();
		player_init(basic_mode);
		item_init();
	}
	void enemy_init() {
		int tempx, tempy;
		for (int i = 0; i < enem_vec.size(); ++i) {
			while (true) {
				tempx = rand() % map_size;
				tempy = rand() % map_size;
				bool flag = true;
				if (map_arr[tempx][tempy] != wall) {
					for (int j = 0; j < i; ++j) {
						if (enem_vec[j].get_x() == tempx && enem_vec[j].get_y() == tempy)
							flag = false;
					}
					if (flag) {
						enem_vec.push_back(Enemy(i, tempx, tempy));
						break;
					}
				}
			}
		}
	}
	void player_init(int mode) {
		if (mode == basic_mode) {
			player = Player(0, 0);
		}		
	}
	void item_init() {
		int tempx, tempy;
		for (int i = 0; i < item_numb; ++i) {
			while (true) {
				tempx = rand() % map_size;
				tempy = rand() % map_size;
				bool flag = true;
				if (map_arr[tempx][tempy] == empty) {
					map_arr[tempx][tempy] == item;
					break;
				}
			}
		}
	}
	bool check_range(pair<int, int> pos) {
		int x = pos.first;
		int y = pos.second;
		if (x < 0 || x >= map_size || y < 0 || y >= map_size)
			return false;
		return true;
	}
	//false 반환시 게임 종료
	bool update_enemies() {
		enem_vec;
		int direction = rand() % 4;
		for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
			pair<int, int> new_pos = it->move_test(direction);
			if (player.get_position() == new_pos) {
				return false;
			}
			if (check_range(new_pos) == false) continue;
			if (map_arr[new_pos.first][new_pos.second] == wall) continue;
			it->move(direction);
		}
	}
	bool kill_enemies(pair<int, int> pos) {
		bool kill = false;
		for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end();) {
			pair<int, int> new_pos = it->get_position();
			if (new_pos == pos) {
				it = enem_vec.erase(it);
				kill = true;
			}
			else it++;
		}
		return kill;
	}
	bool update_bullets() {
		for (vector<Bullet>::iterator it = bull_vec.begin(); it != bull_vec.end(); ) {
			pair<int, int> new_pos = it->move_test();
			if (check_range(new_pos) == false || kill_enemies(new_pos) || 
					map_arr[new_pos.first][new_pos.second] == wall) {
				it = bull_vec.erase(it);
			}
			else it++;
		}
	}

	void player_move(int dir) {
		pair<int, int> test_pos = player.move_test(dir);
		if (check_range(test_pos)) {
			if (map_arr[test_pos.first][test_pos.second] != wall) {
				move(dir);
			}
		}
	}
};
