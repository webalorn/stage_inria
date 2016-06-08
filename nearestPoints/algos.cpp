#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <functional>
#include <string>
#include "test/microtime.hpp"
#include <list>

using Integer = long long int;

struct Point {
	Integer x, y;
};

inline Integer carr(Integer n){
	return n*n;
}
Integer getDistBtw(Point& p1, Point& p2) {
	return carr(p1.x-p2.x) + carr(p1.y-p2.y);
}

struct PairPoints {
	Point p1, p2;
	Integer distanceSquare;
	PairPoints(Point a, Point b) {
		p1 = a, p2 = b;
		distanceSquare = carr(p1.x-p2.x) + carr(p1.y-p2.y);
	}
	void update(Point a, Point b) {
		Integer da = carr(a.x-b.x) + carr(a.y-b.y);
		if (da < distanceSquare) {
			p1 = a, p2 = b;
			distanceSquare = da;
		}
	}
};
bool operator < (const PairPoints& pair1, const PairPoints& pair2) {
	return pair1.distanceSquare < pair2.distanceSquare;
}

bool isP1BeforeP2_X(const Point& p1, const Point& p2) {
	return (p1.x != p2.x) ? p1.x < p2.x : p1.y < p2.y;
}
bool isP1BeforeP2_Y(const Point& p1, const Point& p2) {
	return (p1.y != p2.y) ? p1.y < p2.y : p1.x < p2.x;
}

size_t MAX_POINTS_N2 = 8;

std::vector<Point> merge_ySorted_nearLine(std::vector<Point>& points, size_t debInter1, size_t finInter1, size_t debInter2, size_t finInter2, std::function<bool(Point)> matchLines) {
	std::vector<Point> nearLine;
	while (debInter1 < finInter1 && debInter2 < finInter2) {
		if (!matchLines(points[debInter1])) {
			debInter1++;
			continue;
		}
		if (!matchLines(points[debInter2])) {
			debInter2++;
			continue;
		}
		if (isP1BeforeP2_Y(points[debInter1], points[debInter2]))
			nearLine.push_back(points[debInter1++]);
		else
			nearLine.push_back(points[debInter2++]);
	}
	while (debInter1 < finInter1) {
		if (!matchLines(points[debInter1])) {
			debInter1++;
			continue;
		}
		nearLine.push_back(points[debInter1++]);
	}
	while (debInter2 < finInter2) {
		if (!matchLines(points[debInter2])) {
			debInter2++;
			continue;
		}
		nearLine.push_back(points[debInter2++]);
	}
	return nearLine;
}

PairPoints brutalGetClosestPoints(std::vector<Point>& points, size_t debInter, size_t finInter) {
	PairPoints pairMin(points[debInter], points[debInter+1]);
	for (size_t iP1 = debInter; iP1 < finInter; iP1++) {
		for (size_t iP2 = iP1+1; iP2 < finInter; iP2++) {
			pairMin = std::min(pairMin, PairPoints(points[iP1], points[iP2]));
		}
	}
	return pairMin;
}

int nbTab = -1;
char* errTab() {
	for (int i = 0; i < nbTab; i++)
		std::cerr << "|   ";
	return "";
}

std::pair<PairPoints, size_t> getNearestPoints(std::vector<Point>& points, size_t debInter, size_t finInter, Integer xBorneLeft, Integer xBorneRight) {
	/*nbTab++;
	std::cerr << "\n"; errTab(); std::cerr << "--------- getNearestPoints entre " << xBorneLeft << " et " << xBorneRight << "\n"; errTab();
	for (Integer i = debInter; i < finInter; i++)
		std::cerr << points[i].x << "-" << points[i].y << "  ";
	std::cerr << "\n";*/

	if (finInter - debInter < 2) {
		std::cerr << "Erreure sur la taille de l'entrée: trop petite" << std::endl;
	}
	if (finInter - debInter <= MAX_POINTS_N2) {
		PairPoints pairMin = brutalGetClosestPoints(points, debInter, finInter);
		std::sort(points.begin()+debInter, points.begin()+finInter, [](const Point& p1, const Point& p2) {
			return isP1BeforeP2_Y(p1, p2);
		});
		//errTab(); std::cerr << "delta trouvé: " << pairMin.distanceSquare << "\n";
		//nbTab--;
		return std::make_pair(pairMin, finInter);
	}
	// couper en deux, appels récursifs
	size_t indexCoupe = (debInter+finInter)/2;
	Integer xCoupe = points[indexCoupe].x;
	auto coupe1 = getNearestPoints(points, debInter, indexCoupe, xBorneLeft, xCoupe);
	auto coupe2 = getNearestPoints(points, indexCoupe, finInter, xCoupe, xBorneRight);

	PairPoints pairMin = std::min(coupe1.first, coupe2.first);
	std::vector<Point> nearLine = merge_ySorted_nearLine(points, debInter, coupe1.second, indexCoupe, coupe2.second, [&](const Point& p) {
		return carr(p.x - xCoupe) < pairMin.distanceSquare;
	});

	/*errTab(); std::cerr << "Fusion: ";
	for (Point p : nearLine) {
		std::cerr << p.x << "-" << p.y << "  ";
	} std::cerr << "\n";*/

	for (size_t p1 = 0; p1 < nearLine.size(); p1++) {
		for (size_t nx = p1+1; nx < nearLine.size() && nx < p1+8; nx++) {
			pairMin = std::min(pairMin, PairPoints(nearLine[p1], nearLine[nx]));
		}
	}
	// mettre les deux parties au début, triée par y (uniquement ceux près des bords)
	std::vector<Point> nearBords = merge_ySorted_nearLine(points, debInter, coupe1.second, indexCoupe, coupe2.second, [&](const Point& p) {
		return carr(p.x - xBorneLeft) < pairMin.distanceSquare || carr(p.x - xBorneRight) < pairMin.distanceSquare;
	});
	for (size_t iPoint = 0; iPoint < nearBords.size(); iPoint++) {
		points[debInter+iPoint] = nearBords[iPoint];
	}
	//errTab(); std::cerr << "delta trouvé: " << pairMin.distanceSquare << " avec " << pairMin.p1.x << "-" << pairMin.p1.y << "   " << pairMin.p2.x << "-" << pairMin.p2.y << "\n";
	//nbTab--;
	return std::make_pair(pairMin, debInter+(Integer)nearBords.size());
}

PairPoints distMinBetweenSides(std::vector<Point>& points, size_t debInter1, size_t finInter1, size_t debInter2, size_t finInter2, std::function<bool(Point)> matchLines, PairPoints pairMin) {
	std::vector<Point> side1, side2;
	for (int i = debInter1; i < finInter1; i++)
			if (matchLines(points[i]))
				side1.push_back(points[i]);
	for (int i = debInter2; i < finInter2; i++)
			if (matchLines(points[i]))
				side2.push_back(points[i]);

	int iPt1 = 0, iPt2 = 0, size1 = (int)side1.size(), size2 = (int)side2.size();
	while (iPt1 < size1 && iPt2 < size2) {
		if (isP1BeforeP2_Y(side1[iPt1], side2[iPt2])) {
			for (int i = iPt2; i < iPt2+2 && i < size2; i++)
				pairMin = std::min(pairMin, PairPoints(side1[iPt1], side2[i]));
			iPt1++;
		} else {
			for (int i = iPt1; i < iPt1+2 && i < size1; i++)
				pairMin = std::min(pairMin, PairPoints(side2[iPt2], side1[i]));
			iPt2++;
		}
	}
	return pairMin;
}

std::pair<PairPoints, size_t> getNearestPoints_optimum(std::vector<Point>& points, size_t debInter, size_t finInter, Integer xBorneLeft, Integer xBorneRight) {
	if (finInter - debInter < 2) {
		std::cerr << "Erreure sur la taille de l'entrée: trop petite" << std::endl;
	}
	if (finInter - debInter <= MAX_POINTS_N2) {
		PairPoints pairMin = brutalGetClosestPoints(points, debInter, finInter);
		std::sort(points.begin()+debInter, points.begin()+finInter, [](const Point& p1, const Point& p2) {
			return isP1BeforeP2_Y(p1, p2);
		});
		return std::make_pair(pairMin, finInter);
	}
	// couper en deux, appels récursifs
	size_t indexCoupe = (debInter+finInter)/2;
	Integer xCoupe = points[indexCoupe].x;
	auto coupe1 = getNearestPoints_optimum(points, debInter, indexCoupe, xBorneLeft, xCoupe);
	auto coupe2 = getNearestPoints_optimum(points, indexCoupe, finInter, xCoupe, xBorneRight);

	PairPoints pairMin = std::min(coupe1.first, coupe2.first);
	Integer delta = pairMin.distanceSquare;
	pairMin = distMinBetweenSides(points, debInter, coupe1.second, indexCoupe, coupe2.second, [&](const Point& p) {
		return carr(p.x - xCoupe) < pairMin.distanceSquare;
	}, pairMin);
	// mettre les deux parties au début, triée par y (uniquement ceux près des bords)
	delta = pairMin.distanceSquare;
	std::vector<Point> nearBords = merge_ySorted_nearLine(points, debInter, coupe1.second, indexCoupe, coupe2.second, [&](const Point& p) {
		return carr(p.x - xBorneLeft) < delta || carr(p.x - xBorneRight) < delta;
	});
	for (size_t iPoint = 0; iPoint < nearBords.size(); iPoint++) {
		points[debInter+iPoint] = nearBords[iPoint];
	}
	return std::make_pair(pairMin, debInter+(Integer)nearBords.size());
}

void distMinBetweenSides_v2(std::vector<Point>* side1, std::vector<Point>* side2, PairPoints& pairMin, Integer xCoupe) {
	/*errTab(); std::cerr << "------> Fusion de \n";errTab();
	for (Point p : *side1){
		//if (carr(p.x - xCoupe) < pairMin.distanceSquare)
			std::cerr << p.x << "-" << p.y << "  ";
	}
	std::cerr << "\n"; errTab(); std::cerr << "Et:\n";errTab();
	for (Point p : *side2){
		//if (carr(p.x - xCoupe) < pairMin.distanceSquare)
			std::cerr << p.x << "-" << p.y << "  ";
	}
	std::cerr << "\n";*/

	while (!side1->empty() && !side2->empty()) {
		while (!side1->empty() && carr(side1->back().x - xCoupe) >= pairMin.distanceSquare)
			side1->pop_back();
		while (!side2->empty() && carr(side2->back().x - xCoupe) >= pairMin.distanceSquare)
			side2->pop_back();

		if (side1->empty() || side2->empty())
			return ;

		if (isP1BeforeP2_Y(side1->back(), side2->back()))
			std::swap(side1, side2);

		Point fpSide2 = side2->back();
		//std::cerr << "compare: [" << side1->back().x << " " << side1->back().y << "] et [" << side2->back().x << " " << side2->back().y << "]\n";
		pairMin.update(side1->back(), fpSide2);

		side2->pop_back();
		while (!side2->empty() && carr(side2->back().x - xCoupe) >= pairMin.distanceSquare)
			side2->pop_back();
		if (!side2->empty()) {
			//std::cerr << "compare: [" << side1->back().x << " " << side1->back().y << "] et [" << side2->back().x << " " << side2->back().y << "]\n";
			pairMin.update(side1->back() ,side2->back());
		}
		side2->push_back(fpSide2);

		side1->pop_back();
	}
}

void mergeYsorted(std::vector<Point>* left, std::vector<Point>* right, std::vector<Point>* result) {
	size_t iLeft = 0, iRight = 0;
	while (iLeft < left->size() || iRight < right->size()) {
		if (iRight >= right->size() || (iLeft < left->size() && isP1BeforeP2_Y((*left)[iLeft], (*right)[iRight]))) {
			(*result)[iLeft+iRight] = (*left)[iLeft];
			iLeft++;
		} else {
			(*result)[iLeft+iRight] = (*right)[iRight];
			iRight++;
		}
	}
}

std::pair<std::vector<Point>*, std::vector<Point>*> getNearestPoints_optimum2(std::vector<Point>& points, size_t debInter, size_t finInter, Integer xBorneLeft, Integer xBorneRight, PairPoints& pairMin) {
	
	/*nbTab++;
	std::cerr << "\n"; errTab(); std::cerr << "--------- getNearestPoints entre " << xBorneLeft << " et " << xBorneRight << "\n"; errTab();
	for (Integer i = debInter; i < finInter; i++)
		std::cerr << points[i].x << "-" << points[i].y << "  ";
	std::cerr << "\n";*/

	if (finInter - debInter < 2) {
		std::cerr << "Erreure sur la taille de l'entrée: trop petite" << std::endl;
		exit(-1);
	}
	if (finInter - debInter <= MAX_POINTS_N2) {
		pairMin = std::min(pairMin, brutalGetClosestPoints(points, debInter, finInter));
		std::sort(points.begin()+debInter, points.begin()+finInter, [](const Point& p1, const Point& p2) {
			return isP1BeforeP2_Y(p1, p2);
		});
		std::vector<Point>* v1 = new std::vector<Point>(points.begin()+debInter, points.begin()+finInter);
		std::vector<Point>* v2 = new std::vector<Point>(points.begin()+debInter, points.begin()+finInter);
		//errTab(); std::cerr << "delta trouvé: " << pairMin.distanceSquare << "\n";
		//nbTab--;
		return std::make_pair(v1, v2);
	}
	
	size_t indexCoupe = (debInter+finInter)/2;
	Integer xCoupe = points[indexCoupe].x;
	auto coupe1 = getNearestPoints_optimum2(points, debInter, indexCoupe, xBorneLeft, xCoupe, pairMin);
	auto coupe2 = getNearestPoints_optimum2(points, indexCoupe, finInter, xCoupe, xBorneRight, pairMin);

	//errTab(); std::cerr << "delta trouvé: " << pairMin.distanceSquare << "\n";
	//nbTab--;

	std::vector<Point> *side1 = coupe1.first, *side2 = coupe2.second;

	if (pairMin.distanceSquare > carr(xCoupe-xBorneLeft)) {
		//errTab(); std::cerr << "==> Étendre depuis la gauche !"<< xBorneLeft << " " << xBorneRight << "\n";
		side1 = new std::vector<Point>(coupe1.first->size()+coupe2.first->size());
		mergeYsorted(coupe1.first, coupe2.first, side1);
	}

	if (pairMin.distanceSquare > carr(xBorneRight-xCoupe)) {
		//errTab(); std::cerr << "==> Étendre depuis la droite !"<< xBorneLeft << " " << xBorneRight << "\n";
		side2 = new std::vector<Point>(coupe1.second->size() + coupe2.second->size());
		mergeYsorted(coupe1.second, coupe2.second, side2);
	}

	distMinBetweenSides_v2(coupe1.second, coupe2.first, pairMin, xCoupe);

	delete coupe1.second;
	delete coupe2.first;
	if (side1 != coupe1.first)
		delete coupe1.first;
	if (side2 != coupe2.second)
		delete coupe2.second;
	return std::make_pair(side1, side2);
}

void getClosestPoints_projections(std::vector<Point> pointsVect, int debInter, int finInter, PairPoints nearests) {
	std::vector<Point> coords[2];
	std::list<int> actualCoords[2] = {std::list<int>(finInter-debInter), std::list<int>(finInter-debInter)};

}

std::pair<PairPoints, double> execAlgo(std::string algo, std::vector<Point> points) {
	PairPoints nearests = PairPoints(points[0], points[1]);

	uint64_t start_time = pasl::util::microtime::now();

	if (algo == "brutal")
		nearests = brutalGetClosestPoints(points, 0, (int)points.size());
	else if (algo == "classical")
		nearests = getNearestPoints(points, 0, (int)points.size(), points[0].x, points.back().x).first;
	else if (algo == "optim1")
		nearests = getNearestPoints_optimum(points, 0, (int)points.size(), points[0].x, points.back().x).first;
	else if (algo == "optim2") {
		getNearestPoints_optimum2(points, 0, (int)points.size(), points[0].x, points.back().x, nearests);
	} else if (algo == "projections") {
		getClosestPoints_projections(points, 0, (int)points.size(), nearests);
	} else {
		std::cerr << "---------------> Erreur: algo " << algo << " inexistant <---------------" << std::endl;
		exit(-1);
	}
	double exec_time = pasl::util::microtime::seconds_since(start_time);

	return std::make_pair(nearests, exec_time);
}