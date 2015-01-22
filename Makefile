
CXXFLAGS =  -g -Wall -lnanc++
CC = g++
OBJ = singleton_test range_test 

all : $(OBJ)
	
singleton_test: test_singleton.cpp
	g++ $(CXXFLAGS) test_singleton.cpp	-o singleton_test

range_test: test_range.cpp
	g++ $(CXXFLAGS) $< -o $@

clean : 
	rm -f $(OBJ)
