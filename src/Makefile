CC = clang++
GAME_SOURCE = DeadMen.cpp
GAME_OUTPUT = DeadMen.exe
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lstdc++fs -O3 -std=c++17
INCLUDES = -I/usr/include/SDL2

all: clean heart

heart:
	$(CC) $(GAME_SOURCE) $(LINKER_FLAGS) $(INCLUDES) -o $(GAME_OUTPUT)

clean:
	rm -f *.exe *.o
