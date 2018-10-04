///이겼는지 졌는지 하기

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
	Map() {
		win = false;
		map_size = 148;
		numb_enemy = 15;
		wall_maker();
		item_numb = 6;
		world_init();
		map_init();
		object_init();
	}
	/*Initializing Functions*/
	void wall_maker() {
		int i;
		for (i=0;i<map_size;++i)loc_wall.push_back(0 + map_size*i);
		for (i = 0; i<map_size; ++i)loc_wall.push_back(map_size-1 + map_size*i);
		for (i = 0; i<map_size; ++i)loc_wall.push_back(i + map_size*0);
		for (i = 0; i<map_size; ++i)loc_wall.push_back(i + map_size * (map_size-1));
		for (i = map_size-20; i < map_size; ++i) loc_wall.push_back(20+map_size*i);
		for (i = 0; i < 15; ++i) loc_wall.push_back(25 +map_size * i);
		for (i = 0; i < 16; ++i) loc_wall.push_back(25+i + 14*map_size);
		for (i = 15; i < 30; ++i) loc_wall.push_back(40 + map_size * i);
		for (i = 0; i < 20; ++i) loc_wall.push_back(40 + i + 29*map_size);
		for (i = 0;i < 35; ++i) loc_wall.push_back(i+map_size*50);
		for (i = 0; i < 15; ++i) loc_wall.push_back(60 + map_size * i);
		int len, x, y;
		for (i = 0; i < 20; ++i) {
			len = rand() % 25;
			x = rand() % (map_size - 40);
			y = rand() % (map_size);
			for (int j = 0; j < len; ++j) {
				loc_wall.push_back(x + j + map_size*y);
			}
		}
		for (i = 0; i < 15; ++i) {
			len = rand() % 25;
			x = rand() % (map_size);
			y = rand() % (map_size-40);
			for (int j = 0; j < len; ++j) {
				loc_wall.push_back(x + map_size*(y+j));
			}
		}
		
	}
	void world_init() {
		map_arr = new int*[map_size];
		for (int i = 0; i < map_size; ++i)
			map_arr[i] = new int[map_size];
	}
	void map_init() {
		for (int i = 0; i < map_size; ++i) {
			for (int j = 0; j < map_size; ++j) {
				map_arr[j][i] = map_info::empty;
			}
		}
		for (int i = 0; i < (int)loc_wall.size(); ++i) {
			map_arr[loc_wall[i]/ map_size][loc_wall[i] % map_size] = map_info::wall;
		}
	}
	void object_init() {
		enemy_init();
		player_init(basic_mode);
		item_init();
	}
	void enemy_init() {
		int tempx, tempy;
		for (int i = 0; i < numb_enemy; ++i) {
			while (true) {
				tempx = rand() % map_size;
				tempy = rand() % map_size;
				bool flag = true;
				if (map_arr[tempy][tempx] != wall) {
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
			player = Player(2, 2);
		}
	}
	void item_init() {
		int tempx, tempy;
		for (int i = 0; i < item_numb; ++i) {
			while (true) {
				tempx = rand() % map_size;
				tempy = rand() % map_size;
				bool flag = true;
				if (map_arr[tempy][tempx] == map_info::empty) {
					map_arr[tempy][tempx] = item;
					break;
				}
			}
		}
	}
	/*Done Initializing Functions*/

	int get_numb_enemy() {
		return numb_enemy;
	}

	vector<Enemy>& get_enem_vec() {
		return enem_vec;
	}
	Player& get_player() {
		return player;
	}
	vector<Bullet>& get_bullet_vec() {
		return bull_vec;
	}

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
		if (map_arr[pos.second][pos.first] == wall) return true;
		else return false;
	}
	bool update_enemies() {
		enem_vec;
		int direction;
		for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end();it++) {
			if (it->check_chase(player.get_position())) {
				int x = player.get_x() - it->get_x();
				int y = player.get_y() - it->get_y();
				if (x > 0 && !check_wall(it->move_test(direction::right))) it->move(direction::right);
				else if (x < 0 && !check_wall(it->move_test(direction::left))) it->move(direction::left);
				else if (y > 0 && !check_wall(it->move_test(direction::up))) it->move(direction::up);
				else if (y < 0 && !check_wall(it->move_test(direction::down))) it->move(direction::down);
				for (vector<Bullet>::iterator bl = bull_vec.begin(); bl != bull_vec.end();) {
					pair<int, int> bull_pos = bl->get_position();
					if (it->get_position() == bull_pos) {
						it = enem_vec.erase(it);
						bl = bull_vec.erase(bl);
						it--;
					}
					else {
						bl++;
					}
				}
			}
			else {
				direction = rand() % 4;
				pair<int, int> new_pos = it->move_test(direction);
				if (check_range(new_pos) == false) continue;
				if (map_arr[new_pos.second][new_pos.first] == wall) continue;
				it->move(direction);
				for (vector<Bullet>::iterator bl = bull_vec.begin(); bl != bull_vec.end(); bl++) {
					pair<int, int> bull_pos = bl->get_position();
					if (new_pos == bull_pos) {
						it = enem_vec.erase(it);
						it--;
					}
				}
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
	void update_bullets() {
		for (vector<Bullet>::iterator it = bull_vec.begin(); it != bull_vec.end(); ) {
			pair<int, int> new_pos = it->move_test();
			if (check_range(new_pos) == false || kill_enemies(new_pos) || 
					map_arr[new_pos.second][new_pos.first] == wall || !(it->move())) {
				it = bull_vec.erase(it);
			}
			else {
				it++;
			}
		}
	}
	//Bullet 생성
	void create_bullet() {
		int _posx = player.get_x();
		int _posy = player.get_y();
		int _direction = player.get_direction();
		Bullet newbullet = Bullet(_posx, _posy, _direction, bull_length);
		bull_vec.push_back(newbullet);
	}
	//Player에 대하여 Valid한 Move후 Direction update
	void valid_move(int dir) {
		pair<int, int> test_pos = player.move_test(dir);
		if (check_range(test_pos) && map_arr[test_pos.second][test_pos.first] != wall) {
			player.move(dir);
			player.set_direction(dir);
			get_item();
			
		}
	}
	//현재 위치의 item을 주워 없앤 뒤 empty를 return함
	bool get_item() {
		pair<int, int> current = player.get_position();
		if (map_arr[current.second][current.first] == item) {
			map_arr[current.second][current.first] = map_info::empty;
			player.add_num_i();
			bull_length = bull_length + 3;
			return true;
		}
		return false;
	}
	bool isEnd() {
		for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
			if (player.get_position() == it->get_position()) {
				cout << "You lose";
				return true;
			}
		}
		if (enem_vec.size() == 0) {
			cout << "You win";
			win = true;
			return true;
		}
		return false;
	}
	bool get_win() {
		return win;
	}
};
