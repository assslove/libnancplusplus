
CXXFLAGS =  -I/usr/local/include/libnanc++  -g -Wall
CC = g++
OBJ = singleton_test range_test  util_test xml_test

all : $(OBJ)
	
singleton_test: test_singleton.cpp
	g++ $(CXXFLAGS) test_singleton.cpp	-o singleton_test

range_test: test_range.cpp
	g++ $(CXXFLAGS) $< -o $@

util_test: test_util.cpp
	g++ $(CXXFLAGS) $< -o $@

xml_test: test_xml.cpp
	g++ -o $@ $< -I/usr/local/include/libxml2 $(CXXFLAGS) -L/usr/local/lib -lnanc++ -lxml2

clean : 
	rm -f $(OBJ)
