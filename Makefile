main:
	make warming_up.test.out

CC=g++
FLAGS = -std=c++11

warming_up:
	make warming_up.out
	make warming_up.test.out

warming_up.out: src/main/warming_up.cpp
	$(CC) -o $@ $^ $(FLAGS)

warming_up.test.out: src/test/warming_up.test.cpp src/main/warming_up.cpp
	$(CC) -o $@ $^ $(FLAGS)