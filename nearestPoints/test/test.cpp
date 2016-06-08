#include "microtime.hpp"
#include "cmdline.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdio>

//using pasl::util::cmdline;;

int mon_algo1(int n) {
	int a = 0;
	for (int i = 0; i < n; i++)
		a += rand();
	return a;
}

int mon_algo2(int n) {
	int a = 0;
	for (int i = 0; i < 3*n; i++)
		a += rand();
	return a;
}

int main(int argc, char** argv) {
	pasl::util::cmdline::set(argc, argv);
	int n = pasl::util::cmdline::parse_int("n");
	int seed = pasl::util::cmdline::parse_int("seed");
	srand(seed);
	std::string algo = pasl::util::cmdline::parse_string("algo");

	uint64_t start_time = pasl::util::microtime::now();
	int result;
	if (algo == "algo1")
		result = mon_algo1(n);
	else if (algo == "algo2")
		result = mon_algo2(n);
	else
		throw "Algo inconnu !";
	std::cout << "result " << result << std::endl;
	double exec_time = pasl::util::microtime::seconds_since(start_time);
	printf ("exectime %.3lf\n", exec_time);
}