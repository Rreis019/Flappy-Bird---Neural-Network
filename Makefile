CC = g++
CFLAGS 	= -m64 -IC:/MinGW/include -Wall -Iinclude#include flags 
LDFLAGS = -LC:/MinGW/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2 #linker flags
SRC = $(wildcard src/*.cpp) 
OBJ  =  $(SRC:.cpp=.o) 

BIN = bin/Release/FlappyBirdAI.exe
all: CFLAGS += -O3
all : LDFLAGS +=  -static-libstdc++ -static-libgcc #include libstd++ and libgcc on executable to be able run another machine 
all: LDFLAGS += -s #remove debug symbols
all: link 
all: execute


debug: BIN = bin/Debug/dsa.exe
debug: link
debug: execute
dirs:
	mkdir src
	@echo > src/main.cpp
	mkdir include
	mkdir bin
	cd bin && mkdir Debug && mkdir Release
execute: 
	$(BIN)

link: $(OBJ)
	$(CC)   $^ $(LDFLAGS) -o  $(BIN)

%.o: %.cpp
	$(CC) -o $@ -c  $< $(CFLAGS)

clean:
	del src\*.o