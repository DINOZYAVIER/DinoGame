IDIR = ./include
LDIR = ./lib
LIBS = -lFramework -lstdc++
CC = clang
CFLAGS = -I$(IDIR) -L$(LDIR) --std=c++0x

all: source/main.cpp
	$(CC) source/main.cpp -o output/DinoGame $(CFLAGS) $(LIBS)



