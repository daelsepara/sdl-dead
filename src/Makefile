CC = clang++
GAME_SOURCE = DownAmongTheDeadMen.cpp
GAME_OUTPUT = DownAmongTheDeadMen.exe
LINKER_FLAGS=-O3 -std=c++17 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCLUDES=-I/usr/include/SDL2

UNAME_S=$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LINKER_FLAGS += -stdlib=libc++
	INCLUDES += -I/usr/local/include/SDL2
else
	LINKER_FLAGS += -lstdc++fs
endif

all: clean deadmen

deadmen:
	$(CC) $(GAME_SOURCE) $(LINKER_FLAGS) $(INCLUDES) -o $(GAME_OUTPUT)

clean:
	rm -f *.exe *.o
