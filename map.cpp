#include <iostream>
#include <vector>
#include "player.cpp"
using namespace std;

class Map {
private:
	enum map_info { wall, empty, item };
	int map_size;
	int** map_arr;
	vector <int> loc_wall;
	vector<Enemy> enem_vec;
	int basic_mode = 0;
	int random_mode = 1;

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
						if (enem_vec[j].get_x == tempx && enem_vec[j].get_y == tempy)
							flag = false;
					}
					if (flag) {
						enem_vec.push_back(Enemy(i, tempx, tempy));
					}
				}
			}
		}
	}
	void player_init(int mode) {
		if (mode == basic_mode) {
			Player(0, 0);
		}		
	}
	void item_init() {

	}
};