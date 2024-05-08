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
    std::string txtName = "tile-basic";
    
    if(!hidden)
    {
        if(bomb) (value==-1) ? txtName = "bomb-clicked" : txtName = "bomb";
        else txtName = "tile" + std::to_string(value);
    }
    if(flagged) (value==-1) ? txtName = "tile-incorrectly-flagged" : txtName = "tile-flagged";


    gTextures[txtName]->render(x, y);
}