#include <iostream>
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
	Player player;
	int basic_mode = 0;
	int random_mode = 1;
	int item_numb;

public:
	Map() {
		init_world();
		map_init();
		object_init();
	}
	void init_world() {
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
};