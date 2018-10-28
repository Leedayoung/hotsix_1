#pragma once
#include <iostream>
using namespace std;

class Node {
private:
	int x;
	int y;
	void(*f)();
	Node * sibling;
	Node * child;
public:
	Node() {
	}
	Node(int _x, int _y) {
		x = _x;
		y = _y;
	}
	Node * get_sibling() {
		return sibling;
	}
	Node * get_child() {
		return child;
	}
	

};