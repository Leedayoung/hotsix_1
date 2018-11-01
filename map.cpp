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
#include "sevenseg.h"
#include <string>
#include "sixteenseg.h"
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
				glBindVertexArray(vao[1]);

				mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0));
				mat4 final_mat = ortho_mat * trans;
				vec4 vec_color = vec4(1.0, 0.0, 0.0, 1.0);
				glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
				glUniform4fv(vColor, 1, &vec_color[0]);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
				
				glBindVertexArray(vao[0]);
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

	int item_size = view_size / 8;
	int item_num = player.get_num_i();
	//string s = " item";
	glColor3f(1.0, 1.0, 0.0);
	int display_num = 5;
	//int display_num = item_num > 3 ? item_num : 3;
	//display_num = display_num * 1 + 1;
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(0.5, -1, 0));
	mat4 scale_mat = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.1, 0));
	mat4 final_mat = trans * scale_mat;
	vec4 vec_color = vec4(1.0, 1.0, 0.0, 1.0);
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, NumPoints);
	//draw item
	glBindVertexArray(vao[1]);
	for (int i = 0; i < player.get_life(); i++) {
		mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(0.5 + 0.1*i +0.01, -1, 0));
		mat4 scale_mat = glm::scale(glm::mat4(1.0), glm::vec3(0.09, 0.09, 0));
		mat4 final_mat = trans * scale_mat;
		vec4 vec_color = vec4(1.0, 0.0, 0.0, 1.0);
		glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
		glUniform4fv(vColor, 1, &vec_color[0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
	}
	glBindVertexArray(vao[0]);

	//display time
	int second = time_limit % 60;
	int minute = time_limit / 60;
	int sec2= second / 10;
	int sec1 = second % 10;
	int min2 = minute / 10;
	int min1 = minute % 10;
	draw_seven_seg(sec1, 0);
	draw_seven_seg(sec2, 1);
	draw_seven_seg(min1, 2);
	draw_seven_seg(min2, 3);
	draw_seven_seg(-1, -1);

	//End
	string msg;
	if (end) {
		string end_msg = "PRESS R TO RESTART";
		if (win) msg = "YOU WIN";
		else msg = "YOU LOSE";
		draw_string(msg, -0.30, 0.5);
		draw_string(end_msg, -0.75, 0.3);
	}
	glFlush();
}

Map::Map() {
	win = false;
	map_size = 70;
	view_size = map_size / 8;
	numb_enemy = 10;
	wall_maker();
	item_numb = 5;
	time_limit = 180;
	world_init();
	map_init();
	object_init();
	end = false;
	player.set_life(2);
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
		len = rand() % 13;
		x = rand() % (map_size - 13);
		y = rand() % (map_size);
		for (int j = 0; j < len; ++j) {
			loc_wall.push_back(x + j + map_size * y);
		}
	}
	for (i = 0; i < 15; ++i) {
		len = rand() % 13;
		x = rand() % (map_size);
		y = rand() % (map_size - 13);
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
			pair<int, int> new_pos;
			float x = player.get_x() - it->get_x();
			float y = player.get_y() - it->get_y();
			if (x > 0 && !check_wall(it->move_test(direction::right))) {
				new_pos = it->move_test(direction::right);
				it->set_direction(direction::right);
				it->move();
				it->add_jump(3);
			}
			else if (x < 0 && !check_wall(it->move_test(direction::left))) {
				new_pos = it->move_test(direction::left);
				it->set_direction(direction::left);
				it->move();
				it->add_jump(3);
			}
			else if (y > 0 && !check_wall(it->move_test(direction::up))) {
				new_pos = it->move_test(direction::up);
				it->set_direction(direction::up);
				it->move();
				it->add_jump(3);
			}
			else if (y < 0 && !check_wall(it->move_test(direction::down))) {
				new_pos = it->move_test(direction::down);
				it->set_direction(direction::down);
				it->move();
				it->add_jump(3);
			}
			bool die = false;
			for (vector<Bullet>::iterator bl = bull_vec.begin(); bl != bull_vec.end();bl++) {
				pair<int, int> bull_pos = bl->get_position();
				if (new_pos == bull_pos) {
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
			if (it->get_jump() != 0) continue;
			it->add_jump(3);
			it->set_direction(direction);
			it->move();
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
	int _posx = (int)player.get_x();
	int _posy = (int)player.get_y();
	int _direction = player.get_direction();
	Bullet newbullet = Bullet(_posx, _posy, _direction, bull_length);
	bull_vec.push_back(newbullet);
	player.set_gun(true);
}
//Player에 대하여 Valid한 Move후 Direction update
void Map::valid_move(int dir) {
	pair<int, int> test_pos = player.move_test(dir);
	if (player.get_jump()==0 && check_range(test_pos) && map_arr[test_pos.second][test_pos.first] != wall) {
		player.set_direction(dir);
		player.move();
		get_item(test_pos);
		player.add_jump(3);
	}
}
//현재 위치의 item을 주워 없앤 뒤 empty를 return함
bool Map::get_item(pair<int, int> current) {
	//pair<int, int> current = player.get_position();
	if (map_arr[current.second][current.first] == item) {
		map_arr[current.second][current.first] = map_info::empty;
		player.add_num_i();
		player.set_life(player.get_life()+1);
		return true;
	}
	return false;
}
void Map::timer() {
	time_limit--;
}
bool Map::isEnd() {
	if (time_limit == 0) {
		cout << "Time out" << endl;
		cout << "You lose"<<endl;
		cout << "Press 'R' to restart"<<endl;
		end = true;
		return true;
	}
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
		if (player.get_position() == it->get_position()) {
			player.die();
			if (player.get_life() == 0)
			{
				cout << "Life =0" << endl;
				cout << "You lose"<<endl;
				cout << "Press 'R' to restart"<<endl;
				end = true;
				return true;
			}
			else break;
		}
	}
	if (enem_vec.size() == 0) {
		cout << "You win"<<endl;
		cout << "Press 'R' to restart"<<endl;
		win = true;
		end = true;
		return true;
	}
	return false;
}
bool Map::get_win() {
	return win;
}
bool Map::get_end() {
	return end;
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