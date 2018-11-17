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
void Map::display() {
	pair<float, float> pos = player.get_jump_position();
	int direc = player.get_direction();
	float e_x = pos.first, e_y = pos.second;
	float c_x=0, c_y=0;
	float s, e, z;
	
	switch (mode) {
	case 0://3 person
		s = 2;
		e = 1;
		z = 2.0f;
		break;
	case 1://1 person
		s = 1.3;
		e = -1;
		z = 1.3f;
		break;
	}

	switch (direc) {
	case direction::up:
		c_y = s;
		e_y -= e;
		break;
	case direction::down:
		c_y = -s;
		e_y += e;
		break;
	case direction::left:
		c_x = -s;
		e_x += e;
		break;
	case direction::right:
		c_x = +s;
		e_x -= e;
		break;
	}
	
	mat4 look_at;
	if (mode == 1) {
		look_at = glm::lookAt(glm::vec3(e_x, e_y, z), glm::vec3(e_x + c_x, e_y + c_y, 0.4f), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else {
		look_at = glm::lookAt(glm::vec3(e_x, e_y, z), glm::vec3(e_x + c_x, e_y + c_y, 0.4f), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	mat4 perspec = glm::perspective(glm::radians(80.0f), 1.0f, 0.000000000001f, 5000.0f);
	per_look = perspec * look_at;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, float(0.7137), float(0.7568));
	glLineWidth(0.01f);
	glPointSize(1.0f);

	int e_map[map_size][map_size] = { 0 };
	Enemy e_list[50];
	int e_index = 1;
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
		pair<float, float> pos = it->get_position();
		e_list[e_index] = *it;
		e_map[(int)pos.second][(int)pos.first] = e_index++;
	}

	int b_map[map_size][map_size] = { 0 };
	Bullet b_list[50];
	int b_index = 1;
	for (vector<Bullet>::iterator it = bull_vec.begin(); it != bull_vec.end(); it++) {
		pair<float, float> pos = it->get_position();
		b_list[b_index] = *it;
		b_map[(int)pos.second][(int)pos.first] = b_index++;
	}

	int index = 0;

	switch (direc) {
	case direction::up:
		for (int y = map_size-1; y >= 0; y--) {
			for (int x = 0; x < map_size; x++) {
				draw_map(y, x, e_map, e_list,b_map, b_list);
			}
		}
		break;
	case direction::down:
		for (int y = 0; y < map_size; y++) {
			for (int x = 0; x < map_size; x++) {
				draw_map(y, x, e_map, e_list, b_map, b_list);
			}
		}
		break;
	case direction::left:
		for (int x = 0; x < map_size; x++) {
			for (int y = 0; y < map_size; y++) {
				draw_map(y, x, e_map, e_list, b_map, b_list);
			}
		}
		break;
	case direction::right:
		for (int x = map_size -1; x >= 0 ; x--) {
			for (int y = 0; y < map_size; y ++) {
				draw_map(y, x, e_map, e_list, b_map, b_list);
			}
		}
		break;
	}
	
	//enemy display
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
		it->update();
	}
	
	player.display();

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	index = RECT;
	glBindVertexArray(vao[index]);
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(0.5, -1, 0));
	mat4 scale_mat = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.1, 0));
	mat4 final_mat = trans * scale_mat;
	vec4 vec_color = LIFE_LIST_COLOR;
	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
	glUniform4fv(vColor, 1, &vec_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vao_size[index]);

	index = HEART;
	glBindVertexArray(vao[index]);
	for (int i = 0; i < player.get_life(); i++) {
		mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(0.5 + 0.1*i + 0.01, -1, 0));
		mat4 scale_mat = glm::scale(glm::mat4(1.0), glm::vec3(0.09, 0.09, 0));
		mat4 final_mat = trans * scale_mat;
		vec4 vec_color = LIFE_COLOR;
		glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
		glUniform4fv(vColor, 1, &vec_color[0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vao_size[index]);
	}

	int second = time_limit % 60;
	int minute = time_limit / 60;
	int sec2 = second / 10;
	int sec1 = second % 10;
	int min2 = minute / 10;
	int min1 = minute % 10;
	draw_seven_seg(sec1, 0);
	draw_seven_seg(sec2, 1);
	draw_seven_seg(min1, 2);
	draw_seven_seg(min2, 3);
	draw_seven_seg(-1, -1);

	string msg;
	if (end) {
		string end_msg = "PRESS R TO RESTART";
		if (win) msg = "YOU WIN";
		else msg = "YOU LOSE";
		draw_string(msg, -0.30, 0.5);
		draw_string(end_msg, -0.75, 0.3);
	}
	glFlush();
	return;
}
void Map::draw_map(int y, int x, int e_map[map_size][map_size], Enemy e_list[50], int b_map[map_size][map_size], Bullet b_list[50]) {
	int index;

	index = WALL;
	glBindVertexArray(vao[index]);
	mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(x, y, -0.05))*scale(mat4(1.0), vec3(1.0, 1.0, 0.1));
	mat4 final_mat = per_look * trans;
	vec4 vec_color;

	glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);

	vec_color = BACK_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);

	vec_color = WALL_COLOR;
	glUniform4fv(vColor, 1, &vec_color[0]);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);

	if (map_arr[y][x] == map_info::wall) {
		index = WALL;
		glBindVertexArray(vao[index]);
		mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.5));
		mat4 final_mat = per_look * trans;
		vec4 vec_color;
		
		glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);
		
		vec_color = BACK_COLOR;
		glUniform4fv(vColor, 1, &vec_color[0]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);

		vec_color = WALL_COLOR;
		glUniform4fv(vColor, 1, &vec_color[0]);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);
	}
	else if (map_arr[y][x] == map_info::item) {
		index = ITEM;
		glBindVertexArray(vao[index]);
		mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.1));
		mat4 scale = glm::scale(mat4(1.0), vec3(0.2, 0.2, 0.2));
		mat4 final_mat = per_look * trans;
		vec4 vec_color;

		glUniformMatrix4fv(ctmParam, 1, GL_FALSE, &final_mat[0][0]);

		vec_color = BACK_COLOR;
		glUniform4fv(vColor, 1, &vec_color[0]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);

		vec_color = ITEM_COLOR;
		glUniform4fv(vColor, 1, &vec_color[0]);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, vao_size[index]);
	}
	else if (e_map[y][x] != 0) {
		e_list[e_map[y][x]].display();
	}
	else if (b_map[y][x] != 0) {
		b_list[b_map[y][x]].display();
	}
}
Map::Map() {
	win = false;
	view_size = map_size / 8;
	numb_enemy = 35;
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
	int len, x, y;
	for (i = 0; i<map_size; ++i)loc_wall.push_back(0 + map_size * i);
	for (i = 0; i<map_size; ++i)loc_wall.push_back(map_size - 1 + map_size * i);
	for (i = 0; i<map_size; ++i)loc_wall.push_back(i + map_size * 0);
	for (i = 0; i<map_size; ++i)loc_wall.push_back(i + map_size * (map_size - 1));
	for (i = 0; i < 20; ++i) {
		len = rand() % 13;
		x = rand() % (map_size - 13);
		y = rand() % (map_size);
		for (int j = 0; j < len; ++j) {
			loc_wall.push_back(x + j + map_size * y);
		}
	}
	for (i = 0; i < 20; ++i) {
		len = rand() % 13;
		x = rand() % (map_size);
		y = rand() % (map_size - 13);
		for (int j = 0; j < len; ++j) {
			loc_wall.push_back(x + map_size * (y + j));
		}
	}
}
void Map::change_mode() {
	mode++;
	mode = mode % 2;
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
	enemy_init();
	item_init();
	player_init(random_mode);
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
	else if (mode == random_mode) {
		int tempx, tempy;
		while (true) {
			tempx = rand() % map_size;
			tempy = rand() % map_size;
			if (map_arr[tempy][tempx] == map_info::empty) {
				player = Player(tempx, tempy);
				break;
			}
		}
	}
}
void Map::item_init() {
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
			pair<float, float> new_pos;
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
				pair<float, float> bull_pos = bl->get_position();
				if (new_pos == bull_pos) {
					die = true;
					bl = bull_vec.erase(bl);
					break;
				}
			}
			if (player.get_position() == it->get_position()) {
				player.die();
			}
			if (die) it = enem_vec.erase(it);
			else it++;
		}
		else {
			direction = rand() % 4;
			pair<float, float> new_pos = it->move_test(direction);
			if (check_range(new_pos) == false) continue;
			if (map_arr[(int)new_pos.second][(int)new_pos.first] == wall) continue;
			if (it->get_jump() != 0) continue;
			it->add_jump(3);
			it->set_direction(direction);
			it->move();
			bool die = false;
			for (vector<Bullet>::iterator bl = bull_vec.begin(); bl != bull_vec.end();bl++) {
				pair<float, float> bull_pos = bl->get_position();
				if (new_pos == bull_pos) {
					bl = bull_vec.erase(bl);
					die = true;
					break;
				}
			}
			if (player.get_position() == it->get_position()) {
				player.die();
			}
			if (die) it = enem_vec.erase(it);
			else it++;
		}
	}
	return true;
}
bool Map::kill_enemies(pair<float, float> pos) {
	bool kill = false;
	for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end();) {
		pair<float, float> new_pos = it->get_position();
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
	float _posx = player.get_x();
	float _posy = player.get_y();
	int _direction = player.get_direction();
	Bullet newbullet = Bullet(_posx, _posy, _direction, bull_length);
	
	player.set_gun(true);

	pair<float, float> new_pos = newbullet.get_position();
	if (kill_enemies(new_pos)) {
		
	}
	else {
		bull_vec.push_back(newbullet);
	}
}
//Player에 대하여 Valid한 Move후 Direction update
void Map::valid_move(int dir) {
	pair<int, int> test_pos = player.move_test(dir);
	if (player.get_jump()==0 && check_range(test_pos) && map_arr[test_pos.second][test_pos.first] != wall) {
		player.set_direction(dir);
		int dir = player.get_direction();
		player.move();
		get_item(test_pos);
		//player.add_jump(3);
		for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
			if (player.get_position() == it->get_position()) {
				player.die();
			}
		}
	}
}
void Map::valid_move_3d() {
	if (player.get_jump() != 0) return;
	int dir = player.get_direction();
	pair<float, float> test_pos = player.move_test(dir);
	if (check_range(test_pos) && map_arr[(int)test_pos.second][(int)test_pos.first] != wall) {
		player.move();
		get_item(test_pos);
		player.add_jump(3);
		for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
			if (player.get_position() == it->get_position()) {
				player.die();
			}
		}
	}
}
void Map::rotate_3d(int dir) {
	player.use_all_jump();
	int new_dir = (player.get_direction() + dir+4) % 4;
	player.set_direction(new_dir);
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
	if (player.get_life() == 0)
	{
		cout << "Life =0" << endl;
		cout << "You lose" << endl;
		cout << "Press 'R' to restart" << endl;
		end = true;
		return true;
	}
	/*for (vector<Enemy>::iterator it = enem_vec.begin(); it != enem_vec.end(); it++) {
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
	}*/
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