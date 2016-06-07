#include "algos.cpp"

int main() {
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
	PairPoints nearests = getNearestPoints(points, 0, (int)points.size(), points[0].x, points.back().x).first;
	/*std::cout << "-> Nearest Points: " << std::endl;
	std::cout << nearests.p1.x << " " << nearests.p1.y << std::endl;
	std::cout << nearests.p2.x << " " << nearests.p2.y << std::endl;*/
	std::cout << "Distance: " << sqrt(nearests.distanceSquare) << std::endl;
}