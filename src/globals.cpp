#include "dependencies.h"

bool capFPS = false;

StateMachine gStateMachine = StateMachine();

std::map<std::string, Texture*> gTextures;

std::map<std::string, TTF_Font*> gFonts;
std::map<std::string, Texture*> gTextTextures;

std::map<SDL_Keycode, bool> gKeyPressed;

int random(int a, int b)
{
    return a + rand() % (b-a+1);
}

bool mouseCollision(int x, int y, int width, int height)
{
    if((xMouse > x && xMouse < x+width) && (yMouse > y && yMouse < y+height)) return true;

    return false;
}

bool gRunning = false;

int xMouse = 0, yMouse = 0;
bool mousePressed = false;
std::string mouseButton = "none";