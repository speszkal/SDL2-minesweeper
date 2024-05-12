OBJS = main.cpp src/StateMachine.cpp src/states/BaseState.cpp src/states/PlayState.cpp src/states/GameOverState.cpp src/Game.cpp src/Texture.cpp src/Tile.cpp src/globals.cpp

OBJS_NAME = main.exe

INCLUDE_PATHS = -Ilibs/SDL2/include -Ilibs/SDL2-image/include -Ilibs/SDL2-ttf/include

LIBRARY_PATHS = -Llibs/SDL2/lib -Llibs/SDL2-image/lib -Llibs/SDL2-ttf/lib

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -fconcepts

all:
	g++ $(INCLUDE_PATHS) $(LIBRARY_PATHS) -o $(OBJS_NAME) $(OBJS) $(LINKER_FLAGS)