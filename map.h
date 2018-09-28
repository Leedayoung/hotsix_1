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
	vector <int> loc_wall;
	vector<Enemy> enem_vec;
	vector<Bullet> bull_vec;
	Player player;
	int basic_mode = 0;
	int random_mode = 1;
	int item_numb;

public:
	Map() {
		map_size = 100;
		world_init();
		map_init();
		object_init();
	}
	/*Initializing Functions*/
	void world_init() {
		map_arr = new int*[map_size];
		for (int i = 0; i < map_size; ++i)
			map_arr[i] = new int[map_size];
	}
	void map_init() {
		for (int i = 0; i < map_size; ++i) {
			for (int j = 0; j < map_size; ++j) {
				map_arr[i][j] = map_info::empty;
			}
		}
		for (int i = 0; i < (int)loc_wall.size(); ++i) {
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
		for (int i = 0; i < (int)enem_vec.size(); ++i) {
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
				if (map_arr[tempx][tempy] == map_info::empty) {
					map_arr[tempx][tempy] = item;
					break;
				}
			}
		}
	}
	/*Done Functions*/
	int get_map_size() {
		return map_size;
	}
	int** get_map_arr() {
		return map_arr;
	}
	bool check_range(pair<int, int> pos) {
		int x = pos.first;
		int y = pos.second;
		if (x < 0 || x >= map_size || y < 0 || y >= map_size)
			return false;
		return true;
	}
	bool check_wall(pair<int, int> pos) {
		if (map_arr[pos.first][pos.second] == wall) return true;
		else return false;
	}

	//false ��ȯ�� ���� ���� --> �����ؾ���, player�� ���� ������ chase�� �����̱� ������ Random���� �Ǻ� �Ұ�, Chase �Լ� ¥����
	bool update_enemies_random() {
		enem_vec;
		int direction;
		for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
			if (it->check_chase(player.get_position())) {
				int x = player.get_x() - it->get_x();
				int y = player.get_y() - it->get_y();
				if (x > 0 && !check_wall(it->move_test(direction::right))) it->move(direction::right);
				else if (x < 0 && !check_wall(it->move_test(direction::left))) it->move(direction::left);
				else if (y > 0 && !check_wall(it->move_test(direction::up))) it->move(direction::up);
				else if (y < 0 && !check_wall(it->move_test(direction::down))) it->move(direction::down);
				if (player.get_position() == it->get_position()) {
					return false;
				}
			}
			else {
				direction = rand() % 4;
				pair<int, int> new_pos = it->move_test(direction);
				if (check_range(new_pos) == false) continue;
				if (map_arr[new_pos.first][new_pos.second] == wall) continue;
				it->move(direction);
			}
		}
		return true;
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
			else {
				it->move();
				it++;
			}
		}
	}

	//Bullet ����
	void create_bullet() {
		int _posx = player.get_x();
		int _posy = player.get_y();
		int _direction = player.get_direction();
		Bullet newbullet = Bullet(_posx, _posy, _direction);
		bull_vec.push_back(newbullet);
	}
	//Player�� ���Ͽ� Valid�� Move�� Direction update
	void valid_move(int dir) {
		pair<int, int> test_pos = player.move_test(dir);
		if (check_range(test_pos) && map_arr[test_pos.first][test_pos.second] != wall) {
			move(dir);
			player.set_direction(dir);
		}
	}
	//���� ��ġ�� item�� �ֿ� ���� �� empty�� return��
	bool get_item() {
		pair<int, int> current = player.get_position();
		if (map_arr[current.first][current.second] == item) {
			map_arr[current.first][current.second] = map_info::empty;
			player.add_num_i();
			return true;
		}
		return false;
	}
	//Enemy�� �� ��Ƽ� ������ True�� Return��
	bool isEnd() {
		if (enem_vec.size() == 0) return true;
		return false;
	}

};