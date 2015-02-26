CXXFLAGS =  -g -Wall -fPIC
LIBS = -I/usr/local/include/libxml2 -L/usr/local/lib -lxml2
OBJECTS = add.o  xml_parser.o util.o dirty.o
CC = g++
INSTALL_DIR = /usr/local/include/libnanc++

all : libnanc++.a  libnanc++.so

libnanc++.a : $(OBJECTS)
	ar -rsv libnanc++.a $(OBJECTS)

libnanc++.so : $(OBJECTS)
	$(CC) -shared -o libnanc++.so $(OBJECTS) $(LIBS)

%.o : %.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) $(LIBS) 

clean:
	-rm $(OBJECTS) libnanc++.a libnanc++.so

install:
	sudo cp -r libnanc++.a /usr/local/lib
	sudo cp -r libnanc++.so /usr/local/lib
	sudo rm -rf $(INSTALL_DIR)
	sudo mkdir $(INSTALL_DIR)
	sudo cp -r *.h $(INSTALL_DIR)
