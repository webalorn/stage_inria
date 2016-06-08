#include "algos.cpp"
#include "test/microtime.hpp"
#include "test/cmdline.hpp"

int main(int argc, char** argv) {
	pasl::util::cmdline::set(argc, argv);
	std::string algo = pasl::util::cmdline::parse_string("algo");

	std::ios_base::sync_with_stdio(false);
	int nbPoints;
	std::cin >> nbPoints;
	std::vector<Point> points(nbPoints);
	for (Point& p : points) {
		std::cin >> p.x >> p.y;
	}
	
	std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
		return isP1BeforeP2_X(a, b);
	});

	PairPoints nearests = PairPoints(points[0], points[1]);

	uint64_t start_time = pasl::util::microtime::now();

	if (algo == "brutal") {
		std::cerr << "============= BRUTAL =============" << std::endl;
		nearests = brutalGetClosestPoints(points, 0, (int)points.size());
		std::cerr << std::endl;
	} else if (algo == "classical") {
		std::cerr << "============= CLASSICAL =============" << std::endl;
		nearests = getNearestPoints(points, 0, (int)points.size(), points[0].x, points.back().x).first;
		std::cerr << std::endl;
	} else if (algo == "optim1") {
		std::cerr << "============= OPTIM 1 =============" << std::endl;
		nearests = getNearestPoints_optimum(points, 0, (int)points.size(), points[0].x, points.back().x).first;
		std::cerr << std::endl;
	} else if (algo == "optim2") {
		std::cerr << "============= OPTIM 2 =============" << std::endl;
		getNearestPoints_optimum2(points, 0, (int)points.size(), points[0].x, points.back().x, nearests);
		std::cerr << std::endl;
	} else {
		std::cerr << "---------------> Erreur: algo " << algo << " inexistant <---------------" << std::endl;
		exit(-1);
	}
	std::cout << "distance " << sqrt(nearests.distanceSquare) << std::endl;
	double exec_time = pasl::util::microtime::seconds_since(start_time);
	//printf ("exectime %.3lf\n", exec_time);
	//std::cout.precision(3);
	std::cout << "exectime " << exec_time << std::endl;
	return 0;
}