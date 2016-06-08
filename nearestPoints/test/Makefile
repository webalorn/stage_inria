all: 
	g++ test.cpp cmdline.cpp microtime.cpp -o test.out -std=c++14
test:
	~/Documents/informatique/C_C++/stage_inria/nearestPoints/pbench/prun -prog ./test.out -runs 1 -timeout 5 -n 1000,10000,100000,1000000,10000000,100000000 -algo algo1,algo2 -seed 2,3,4
plot:
	~/Documents/informatique/C_C++/stage_inria/nearestPoints/pbench/pplot -x n -y exectime -series algo --xtitles-vertical -group-by seed
plot2:
	~/Documents/informatique/C_C++/stage_inria/nearestPoints/pbench/pplot -x n -y exectime -chart algo
plot3:
	~/Documents/informatique/C_C++/stage_inria/nearestPoints/pbench/pplot scatter -x n --xlog -y exectime -series algo
full: all test plot