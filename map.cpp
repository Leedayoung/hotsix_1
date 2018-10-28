#pragma once
#include <iostream>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include "map.h"
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
#include "display.h"
using namespace std;
using namespace glm;
void Map::display(GLuint program) {
	pair<int, int> pos = player.get_position();
	int x = pos.first, y = pos.second;
	x -= view_size;
	y -= view_size;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + 2 * view_size > map_size) x = map_size - 2 * view_size;
	if (y + 2 * view_size > map_size) y = map_size - 2 * view_size;
	
	ortho_mat = glm::ortho((float)x, (float)x + 2 * view_size, (float)y, (float)y + 2 * view_size);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	int NumPoints = 4;

	//glm::lookAtRH(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 1));
	//map_display
	double wall_len = 1.0 / map_size;
	for (int y = 0; y < map_size; y++) {
		for (int x = 0; x < map_size; x++) {
			if (map_arr[y][x] == map_info::wall) {
				mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0));
				mat4 final_mat = ortho_mat * trans;
				vec4 vec_color = vec4(0.0, 0.0, 0.0, 1.0);
				glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
				glUniform4fv(vColor, 1, &vec_color[0]);
				glDrawArrays(GL_TRIANGLE_FAN, 0, NumPoints);
			}
			else if (map_arr[y][x] == map_info::item) {
				mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0));
				mat4 final_mat = ortho_mat * trans;
				vec4 vec_color = vec4(1.0, 0.0, 0.0, 1.0);
				glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
				glUniform4fv(vColor, 1, &vec_color[0]);
				glDrawArrays(GL_TRIANGLE_FAN, 0, NumPoints);
			}
		}
	}
	player.display();
	
	//enemy display
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
		it->display();
	}

	//display bullet
	for (vector<Bullet>::iterator it = bull_vec.begin(); it != bull_vec.end(); it++) {
		it->display();
	}

	/*pair<int, int> pos = player.get_position();
	int x = pos.first, y = pos.second;
	x -= view_size;
	y -= view_size;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + 2 * view_size > map_size) x = map_size - 2 * view_size;
	if (y + 2 * view_size > map_size) y = map_size - 2 * view_size;
	*/
	//glm::translate(glm::mat4(), glm::vec3(pos_x, pos_y, 0.0f));
	
		//glDrawArrays(GL_LINES, 1, NumPoints);
		//glDrawArrays(GL_LINES, 2, NumPoints);
		
	/*pair<int, int> pos = player.get_position();
	int x = pos.first, y = pos.second;
	x -= view_size;
	y -= view_size;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + 2 * view_size > map_size) x = map_size - 2 * view_size;
	if (y + 2 * view_size > map_size) y = map_size - 2 * view_size;

	glLoadIdentity();
	gluOrtho2D(x, x + 2 * view_size, y, y + 2 * view_size);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//map display
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	double wall_len = 1.0 / map_size;
	for (int y = 0; y < map_size; y++) {
	for (int x = 0; x < map_size; x++) {
	if (map_arr[y][x] == map_info::wall) {
	glBindTexture(GL_TEXTURE_2D, texture[image::wall_p]);
	draw_rec(x, y, x + 1, y + 1);
	}
	else if (map_arr[y][x] == map_info::item) {
	glBindTexture(GL_TEXTURE_2D, texture[image::item_p]);
	draw_rec(x, y, x + 1, y + 1);
	}
	}
	}
	//enemy display
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
	it->display();
	}

	//display bullet
	for (vector<Bullet>::iterator it = bull_vec.begin(); it != bull_vec.end(); it++) {
	it->display();
	}

	//display player
	player.display();

	//item inventory
	int item_size = view_size / 4;
	int item_num = player.get_num_i();
	string s = " item";
	glColor3f(1.0, 1.0, 0.0);
	int display_num = item_num > 3 ? item_num : 3;
	display_num = display_num * 1 + 1;
	glRecti(x + 7 * item_size, y, x + 8 * item_size, y + display_num);
	glColor3f(0.0, 0.0, 0.0);
	print(x + 7 * item_size, y + display_num + 1, "Item List");
	for (int i = 1; i <= item_num; i++)
	print(x + 7 * item_size, y + display_num - 1 * i, s + to_string(i));

	//Enemy Kills
	int killed = numb_enemy - enem_vec.size();
	string ss = "Killed Enemy ";
	string dash = "/";
	print(x + 1, y + 2 * view_size - 1, ss + to_string(killed) + dash + to_string(numb_enemy));

	if (isEnd()) {
	if (win) {
	print(x + view_size, y + view_size + 2, "You Win");
	}
	else {
	print(x + view_size, y + view_size + 2, "You Lose");
	}
	}
	glutSwapBuffers();*/
	glFlush();
}



Map::Map() {
	win = false;
	map_size = 148;
	view_size = map_size / 12;
	numb_enemy = 15;
	wall_maker();
	item_numb = 6;
	world_init();
	map_init();
	object_init();
}
/*Initializing Functions*/
void Map::wall_maker() {
	int i;
	for (i = 0; i<map_size; ++i)loc_wall.push_back(0 + map_size * i);
	for (i = 0; i<map_size; ++i)loc_wall.push_back(map_size - 1 + map_size * i);
	for (i = 0; i<map_size; ++i)loc_wall.push_back(i + map_size * 0);
	for (i = 0; i<map_size; ++i)loc_wall.push_back(i + map_size * (map_size - 1));
	for (i = map_size - 20; i < map_size; ++i) loc_wall.push_back(20 + map_size * i);
	for (i = 0; i < 15; ++i) loc_wall.push_back(25 + map_size * i);
	for (i = 0; i < 16; ++i) loc_wall.push_back(25 + i + 14 * map_size);
	for (i = 15; i < 30; ++i) loc_wall.push_back(40 + map_size * i);
	for (i = 0; i < 20; ++i) loc_wall.push_back(40 + i + 29 * map_size);
	for (i = 0; i < 35; ++i) loc_wall.push_back(i + map_size * 50);
	for (i = 0; i < 15; ++i) loc_wall.push_back(60 + map_size * i);
	int len, x, y;
	for (i = 0; i < 20; ++i) {
		len = rand() % 25;
		x = rand() % (map_size - 40);
		y = rand() % (map_size);
		for (int j = 0; j < len; ++j) {
			loc_wall.push_back(x + j + map_size * y);
		}
	}
	for (i = 0; i < 15; ++i) {
		len = rand() % 25;
		x = rand() % (map_size);
		y = rand() % (map_size - 40);
		for (int j = 0; j < len; ++j) {
			loc_wall.push_back(x + map_size * (y + j));
		}
	}
}
void Map::world_init() {
	map_arr = new int*[map_size];
	for (int i = 0; i < map_size; ++i)
		map_arr[i] = new int[map_size];
}
void Map::map_init() {
	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j) {
			map_arr[j][i] = map_info::empty;
		}
	}
	for (int i = 0; i < (int)loc_wall.size(); ++i) {
		map_arr[loc_wall[i] / map_size][loc_wall[i] % map_size] = map_info::wall;
	}
}
void Map::object_init() {
	player_init(basic_mode);
	enemy_init();
	item_init();
}
void Map::enemy_init() {
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
					enem_vec.push_back(Enemy(tempx, tempy));
					break;
				}
			}
		}
	}
}
void Map::player_init(int mode) {
	if (mode == basic_mode) {
		player = Player(2, 2);
	}
}
void Map::item_init() {
	int tempx, tempy;
	for (int i = 0; i < item_numb; ++i) {
		while (true) {
			tempx = rand() % map_size;
			tempy = rand() % map_size;
			bool flag = true;
			if (map_arr[tempy][tempx] == map_info::empty && tempx!=2 && tempy!=2) {
				map_arr[tempy][tempx] = item;
				break;
			}
		}
	}
}
int Map::get_numb_enemy() {
	return numb_enemy;
}
int Map::get_map_size() {
	return map_size;
}
int** Map::get_map_arr() {
	return map_arr;
}
bool Map::check_range(pair<int, int> pos) {
	int x = pos.first;
	int y = pos.second;
	if (x < 0 || x >= map_size || y < 0 || y >= map_size)
		return false;
	return true;
}
bool Map::check_wall(pair<int, int> pos) {
	if (map_arr[pos.second][pos.first] == wall) return true;
	else return false;
}
bool Map::update_enemies() {
	int direction;
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); ) {
		if (it->check_chase(player.get_position())) {
			int x = player.get_x() - it->get_x();
			int y = player.get_y() - it->get_y();
			if (x > 0 && !check_wall(it->move_test(direction::right))) it->move(direction::right);
			else if (x < 0 && !check_wall(it->move_test(direction::left))) it->move(direction::left);
			else if (y > 0 && !check_wall(it->move_test(direction::up))) it->move(direction::up);
			else if (y < 0 && !check_wall(it->move_test(direction::down))) it->move(direction::down);
			bool die = false;
			for (vector<Bullet>::iterator bl = bull_vec.begin(); bl != bull_vec.end();bl++) {
				pair<int, int> bull_pos = bl->get_position();
				if (it->get_position() == bull_pos) {
					die = true;
					bl = bull_vec.erase(bl);
					break;
				}
			}
			if (die) it = enem_vec.erase(it);
			else it++;
		}
		else {
			direction = rand() % 4;
			pair<int, int> new_pos = it->move_test(direction);
			if (check_range(new_pos) == false) continue;
			if (map_arr[new_pos.second][new_pos.first] == wall) continue;
			it->move(direction);
			bool die = false;
			for (vector<Bullet>::iterator bl = bull_vec.begin(); bl != bull_vec.end();bl++) {
				pair<int, int> bull_pos = bl->get_position();
				if (new_pos == bull_pos) {
					bl = bull_vec.erase(bl);
					die = true;
					break;
				}
			}
			if (die) it = enem_vec.erase(it);
			else it++;
		}
	}
	return true;
}
bool Map::kill_enemies(pair<int, int> pos) {
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
void Map::update_bullets() {
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
void Map::create_bullet() {
	int _posx = player.get_x();
	int _posy = player.get_y();
	int _direction = player.get_direction();
	Bullet newbullet = Bullet(_posx, _posy, _direction, bull_length);
	bull_vec.push_back(newbullet);
}
//Player에 대하여 Valid한 Move후 Direction update
void Map::valid_move(int dir) {
	pair<int, int> test_pos = player.move_test(dir);
	if (check_range(test_pos) && map_arr[test_pos.second][test_pos.first] != wall) {
		player.move(dir);
		player.set_direction(dir);
		get_item();

	}
}
//현재 위치의 item을 주워 없앤 뒤 empty를 return함
bool Map::get_item() {
	pair<int, int> current = player.get_position();
	if (map_arr[current.second][current.first] == item) {
		map_arr[current.second][current.first] = map_info::empty;
		player.add_num_i();
		bull_length = bull_length + 3;
		return true;
	}
	return false;
}
bool Map::isEnd() {
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
bool Map::get_win() {
	return win;
}

void Map::draw_rec(int x1, int y1, int x2, int y2) {
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(x1, y1);
	glTexCoord2i(1, 0); glVertex2i(x2, y1);
	glTexCoord2i(1, 1); glVertex2i(x2, y2);
	glTexCoord2i(0, 1); glVertex2i(x1, y2);
	glEnd();
}
void Map::print(int x, int y, string string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2i(x, y);
	//get the length of the string to display
	//loop to display character by character
	for (int i = 0; i < int(string.size()); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
};