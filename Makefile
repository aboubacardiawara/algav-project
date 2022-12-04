main:
	make warming_up.test.out

CC=g++
LIBS = -Isrc/arithmetic_lib/include/NTL -Lsrc/arithmetic_lib/lib
FLAGS = -std=c++11 $(LIBS) -lntl

warming_up:
	make warming_up.out
	make warming_up.test.out

warming_up.out: src/warming_up/warming_up.cpp
	$(CC) -o $@ $^ $(FLAGS)

warming_up.test.out: src/tests/warming_up.test.cpp src/warming_up/warming_up.cpp
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm *.out