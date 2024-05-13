#include "dependencies.h"

Tile::Tile(int x, int y, int width, int height, bool bomb)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->bomb = bomb;

    value = 0; //0 - undefined/value 0; -1 - incorrect; 0-8 - correct values;
    flagged = false;
    hidden = true;
}

Tile::~Tile()
{}

void Tile::update()
{
    
}

void Tile::render(SDL_Renderer* renderer)
{
    SDL_Rect sr = {64, 16, 16, 16};
    
    /*if(!hidden)
    {
        if(bomb) (value==-1) ? txtName = "bomb-clicked" : txtName = "bomb";
        else txtName = "tile" + std::to_string(value);
    }
    if(flagged) (value==-1) ? txtName = "tile-incorrectly-flagged" : txtName = "tile-flagged";*/
    if(!hidden)
    {
        if(bomb) (value==-1) ? sr={16, 16, 16, 16} : sr={0, 16, 16, 16};
        else sr={value*16, 0, 16, 16};
    }
    if(flagged) (value==-1) ? sr={48, 16, 16, 16} : sr={32, 16, 16, 16};

    gTextures["tiles-spritesheet"]->render(x, y, &sr, width/sr.w, height/sr.h);
}