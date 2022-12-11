main:
	make warming_up.test.out
	make tree.test.out

CC=g++
LIBS = -Isrc/arithmetic_lib/include/NTL -Lsrc/arithmetic_lib/lib
FLAGS = -std=c++11 $(LIBS) -lntl -Wall -Ofast -funroll-loops -finline-functions -pthread

warming_up:
	make warming_up.out
	make warming_up.test.out

warming_up.out: src/warming_up/warming_up.cpp
	$(CC) -o $@ $^ $(FLAGS)

warming_up.test.out: src/tests/warming_up.test.cpp src/warming_up/warming_up.cpp
	$(CC) -o $@ $^ $(FLAGS)

tree:
	make tree.out
	make tree.test.out

tree.out: src/decision_tree/tree.cpp src/warming_up/warming_up.cpp src/decision_tree/treeClasses.cpp
	$(CC) -o $@ $^ $(FLAGS)

tree.test.out: src/tests/tree.test.cpp src/decision_tree/tree.cpp src/warming_up/warming_up.cpp src/decision_tree/treeClasses.cpp
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm *.out *.dot *.jpg