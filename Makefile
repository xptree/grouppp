#!/bin/bash

CC=g++
CFLAGS= -O2 -Wall
LDFLAGS= -O2 -Wall
EXEC=main
OBJ= group.o util.o main.o

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
