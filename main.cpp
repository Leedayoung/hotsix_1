#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
using namespace std;

class Map{
private:
	enum map_info{wall, empty, item};
	int map_size;
	int** map_arr;
	vector<Enemy> enem_vec;

public:
	Map(){
		init_window();
		map_init();
		object_init();
	}
	void init_window() {

	}
	void map_init() {
		
	}
	void object_init() {
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
						enem_vec.push_back(i,tempx,tempy);
					}
				}
			}
		}
		Player(posx, posy);
	}
};

void main(int argc, char **argv) {

}