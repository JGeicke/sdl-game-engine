#ifndef POSITION_H
#define POSITION_H
#include <iostream>
struct Position {
	int x;
	int y;

	void print() {
		std::cout << "X: " << x  << " | Y: " << y << std::endl;
	}
};
#endif // !POSITION_H

