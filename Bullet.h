#pragma once
#include <iostream>
#include "Entity.h"
using namespace std;

class Bullet : public Entity {
private:
	int id;
public:
	int get_id() {
		return id;
	}
};