#include "algos.cpp"
#include "test/cmdline.hpp"
#include <ctime>
#include <fstream>

std::vector<Point> gen(int n) {
	std::vector<Point> v(n);
	int xyMax = 10*n;
	for (int i = 0; i < n; i++) {
		v[i].x = rand()%xyMax;
		v[i].y = rand()%xyMax;
	}
	return v;
}

Integer _execAlgo(std::string algo, std::vector<Point> points) {
	PairPoints nearests = PairPoints(points[0], points[1]);
	if (algo == "brutal")
		nearests = brutalGetClosestPoints(points, 0, (int)points.size());
	else if (algo == "classical")
		nearests = getNearestPoints(points, 0, (int)points.size(), points[0].x, points.back().x).first;
	else if (algo == "optim1")
		nearests = getNearestPoints_optimum(points, 0, (int)points.size(), points[0].x, points.back().x).first;
	else if (algo == "optim2")
		getNearestPoints_optimum2(points, 0, (int)points.size(), points[0].x, points.back().x, nearests);
	else {
		std::cerr << "---------------> Erreur: algo " << algo << " inexistant <---------------" << std::endl;
		exit(-1);
	}
	return nearests.distanceSquare;
}

int main(int argc, char** argv) {
	pasl::util::cmdline::set(argc, argv);
	srand(time(0));
	int n = pasl::util::cmdline::parse_int("n");
	int nbPoints = pasl::util::cmdline::parse_int("points");
	std::string ref = pasl::util::cmdline::parse_string("ref");
	std::string test = pasl::util::cmdline::parse_string("test");

	std::ios_base::sync_with_stdio(false);

	for (int rep = 1; rep <= n; rep++) {
		std::vector<Point> points = gen(nbPoints);
		std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
			return isP1BeforeP2_X(a, b);
		});

		if (_execAlgo(ref, points) == _execAlgo(test, points)) {
			std::cout << "Test " << rep <<" : Success" << std::endl;
		} else {
			std::ofstream myfile;
 			myfile.open ("inputErr");
			std::cout << "Test " << rep <<" : FAIL !" << std::endl;
			myfile << nbPoints << std::endl;
			for (Point p : points) {
				myfile << p.x << " " << p.y << std::endl;
			}
			myfile.close();
			return 0;
		}

	}
	return 0;
}