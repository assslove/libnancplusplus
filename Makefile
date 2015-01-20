
CXXFLAGS =  -g -Wall
CC = g++
OBJ = singleton_test

all : $(OBJ)
	
singleton_test: test_singleton.cpp
	g++ $(CXXFLAGS) test_singleton.cpp	-o singleton_test

clean : 
	rm -f $(OBJ)
