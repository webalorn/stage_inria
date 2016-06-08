all: compile runMain plotMain
compile: 
	g++ main.cpp test/cmdline.cpp test/microtime.cpp -o main -std=c++14
compileRead: 
	g++ mainRead.cpp test/cmdline.cpp test/microtime.cpp -o mainRead -std=c++14
runMain:
	~/Documents/informatique/C_C++/stage_inria/nearestPoints/pbench/prun -prog ./main -runs 1 -timeout 5 -n 1000,10000,100000,200000,500000,1000000 -algo optim2,classical,projections -seed 2,3,4
plotMain:
	~/Documents/informatique/C_C++/stage_inria/nearestPoints/pbench/pplot scatter -x n --xlog -y exectime -series algo -group-by seed
	#~/Documents/informatique/C_C++/stage_inria/nearestPoints/pbench/pplot -x n -y exectime -series algo --xtitles-vertical -group-by seed
testOpt2: compileRead
	./mainRead -algo classical < in
	./mainRead -algo optim2 < in
execTests:
	g++ execTests.cpp test/cmdline.cpp -o execTests -std=c++14
	./execTests -n 20 -points 1000 -ref classical -test optim2
	rm execTests