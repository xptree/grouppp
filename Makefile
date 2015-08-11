#!/bin/bash

CC=g++-5
CFLAGS= -O3 -g -Wall -std=c++11 
LDFLAGS= -O3 -g -Wall -std=c++11 
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
