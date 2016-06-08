# coding: utf8
import os

print("Combien de tests ?");
n = int(input())
#compiler
print("Compilation...")
os.system("g++ gen.cpp -o gen -std=c++11 && g++ brutal.cpp -o brutal -std=c++11 && g++ main.cpp -o main -std=c++11")
print("Lancement !")
for i in range(n):
	print("-> test "+str(i+1))
	# executer
	os.system("echo '1000' | ./gen > inPy && ./brutal < inPy > o1 && ./main < inPy > o2")
	f1 = open("o1")
	f2 = open("o2")
	l1 = f1.readline()
	l2 = f2.readline()
	if 	l1 != l2:
		print("==========> ERROR !")
		exit()
print("Aucun problème détecté")