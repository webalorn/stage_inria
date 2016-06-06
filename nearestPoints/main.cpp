#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using Point = std::pair<int, int>;
struct PairPoints {
	Point p1, p2;
	int distanceSquare() {
		return (p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second);
	}
	PairPoints(Point a, Point b) {
		p1 = a, p2 = b;
	}
};
bool operator < (const PairPoints& pair1, const PairPoints& pair2) {
	return pair1.distanceSquare() < pair2.distanceSquare();
}

bool isP1BeforeP2_Y(const Point& p1, const Point& p2) {
	return (p1.seoncd != p2.second) ? p1.second < p2.second : p1.first < p2.first;
}

const size_t MAX_POINTS_N2 = 3;

std::pair<PairPoints, std:vector<Points>> getNearestPoints(std::vector<Point> points) { // return pairMin, points sorted by Y
	if (points.size() < 2) {
		std::cerr << "Erreure sur la taille de l'entrée: trop petite" << std::endl;
	}
	if (points.size() <= MAX_POINTS_N2) {
		PairPoints pairMin(points[0], points[1]);
		for (size_t	iP1 = 0; iP1 < points.size(); iP1++) {
			for (size_t iP2 = 0; iP2 < points.size(); iP2++) {
				if (iP1 != iP2)
					pairMin = std::min(pairMin, PairPoints(points[iP1], points[iP2]));
			}
		}
		std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
			return isP1BeforeP2_Y(p1, p2);
		});
		return std::make_pair(pairMin, points);
	}
	// couper en deux, appels récursifs
	size_t indexCoupe = points.size() / 2;
	int xCoupe = points[indexCoupe].first;
	auto coupe1 = getNearestPoints(vector<Point>(points.begin(), points.begin() + indexCoupe));
	auto coupe2 = getNearestPoints(vector<Point>(points.begin() + indexCoupe, points.end()));

	PairPoints pairMin = std::min(coupe1.first, coupe2.first);
	// fusionner les deux tableaux dans points`[ uniquement ceux assez proches de xCoupe, < distMin]
	std::vector<Point> ptsSortedByY;
	size_t iCoupe1 = 0; iCoupe2 = 0;
	while (iCoupe1 < coupe1.second.size() && iCoupe2 < coupe2.second.size()) {
		if () // TODO : comparaison avec isP1BeforeP2_Y
	}
	// TODO
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int nbPoints;
	std::cin >> nbPoints;
	std::std::vector<Point> points(nbPoints);
	for (Point& p : points) {
		std::cin >> p.first >> p.second;
	}
	PairPoints nearests = getNearestPoints(points).first;
	std::cout << "-> Nearest Points: " << std::endl;
	std::cout << nearests.p1.first << " " << nearests.p1.second << std::endl;
	std::cout << nearests.p2.first << " " << nearests.p2.second << std::endl;
	std::cout << "Distance: " << sqrt(nearests.distanceSquare) << std::endl;
}