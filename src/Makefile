CFLAGS =  -g -Wall -fPIC  -O2
OBJECTS = add.o range.o
CC = g++
INSTALL_DIR = /usr/local/include/libnanc++

all : libnanc++.a libnanc++.so

libnanc++.a : $(OBJECTS)
	ar -cru libnanc++.a $(OBJECTS)

libnanc++.so : $(OBJECTS)
	$(CC) $< -shared -o libnanc++.so

%.o : %.cpp
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	-rm $(OBJECTS) libnanc++.a libnanc++.so

install:
	sudo cp -r libnanc++.a /usr/local/lib
	sudo cp -r libnanc++.so /usr/local/lib
	sudo rm -rf $(INSTALL_DIR)
	sudo mkdir $(INSTALL_DIR)
	sudo cp -r *.h $(INSTALL_DIR)
