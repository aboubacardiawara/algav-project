main:
	make warming_up.out

CC=g++

warming_up.out: src/main/warming_up.cpp
	$(CC) -o $@ $^