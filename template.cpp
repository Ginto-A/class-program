#include<iostream>

#define Max(x, y) (x > y ? x : y)

int main() {
	std::cout << Max(9 + 0.9, 8 + 0.8) << std::endl;
	std::cout << Max(9, 8) << std::endl;
	return 0;
}
