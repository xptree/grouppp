#!/bin/bash

CC=g++
CFLAGS= -O3 -g -Wall -std=c++0x -I/data/qspace/data/user/hdpzhakeberglu/tangjie/local/include
LDFLAGS= -O3 -g -Wall -std=c++0x -llog4cpp -lrt -L/data/qspace/data/user/hdpzhakeberglu/tangjie/local/lib
EXEC=main
OBJ= group.o util.o main.o disjointSet.o

all: $(EXEC)

main : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

##########################################
# Generic rules
##########################################

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *~ $(EXEC)
