#include "algos.cpp"
#include "test/cmdline.hpp"

std::vector<Point> gen(int n) {
	std::vector<Point> v(n);
	int xyMax = 10*n;
	for (int i = 0; i < n; i++) {
		v[i].x = rand()%xyMax;
		v[i].y = rand()%xyMax;
	}
	return v;
}

int main(int argc, char** argv) {
	pasl::util::cmdline::set(argc, argv);
	int nbPoints = pasl::util::cmdline::parse_int("n");
	int seed = pasl::util::cmdline::parse_int("seed");
	srand(seed);
	std::string algo = pasl::util::cmdline::parse_string("algo");

	std::ios_base::sync_with_stdio(false);
	/*int nbPoints;
	std::cin >> nbPoints;
	std::vector<Point> points(nbPoints);
	for (Point& p : points) {
		std::cin >> p.x >> p.y;
	}*/
	std::vector<Point> points = gen(nbPoints);
	std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
		return isP1BeforeP2_X(a, b);
	});

	auto result = execAlgo(algo, points);
	
	//printf ("exectime %.3lf\n", exec_time);
	//std::cout.precision(3);
	std::cout << "distance " << sqrt(result.first.distanceSquare) << std::endl;
	std::cout << "exectime " << result.second << std::endl;
	return 0;
}