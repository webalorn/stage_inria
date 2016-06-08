#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
	srand(time(0));
	int n;
	std::cin >> n;
	int xyMax = 1000000;
	std::cout << n << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << rand()%xyMax << " " << rand()%xyMax << std::endl;
	}
}