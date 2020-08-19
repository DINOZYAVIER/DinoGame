SRCS = source/main.cpp  
IDIR = ./include
LDIR = ./lib
LIBS = -lFramework  -lstdc++ 
CC = clang
CFLAGS = -I$(IDIR) -L$(LDIR) --std=c++0x

all: $(SRCS)
	$(CC) $(SRCS) -o output/DinoGame $(CFLAGS) $(LIBS)



