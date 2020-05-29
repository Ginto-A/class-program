#include<iostream>

float Max(float x, float y){
	std::cout << "float" << std::endl;
	return x > y ? x : y;
}
int Max(int x, int y){
	std::cout << "int" << std::endl;
	return x > y ? x : y;
}
double Max(double x, double y){
	std::cout << "double" << std::endl;
	return x > y ? x : y;
}

int main() {
	std::cout << Max(9.9, 8.8) << std::endl;
	std::cout << Max(9, 8) << std::endl;
	return 0;
}
