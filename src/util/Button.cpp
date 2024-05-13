#include "../dependencies.h"

Button::Button(int x, int y, int width, int height, std::string textureName, std::string text, std::string graphic)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->textureName = textureName;
    this->text = text;
    this->graphic = graphic;
}

Button::~Button()
{
    
}

void Button::update()
{
    if(mouseButtonDown && mouseButton=="left" && mouseCollision(x, y, width, height))
    {
        isDown ? isPressed = false : isPressed = true;
        isDown = true;
    }
    else if(mouseButtonUp && mouseButton=="left") isDown = false;
}

void Button::render(SDL_Renderer* renderer)
{
    SDL_Rect sr = {isDown*16, 0, 16, 16};

    gTextures[textureName]->render(x, y, &sr, (float)width/sr.w, (float)height/sr.h);
    //if(graphic != "") gTextures[graphic]->render(x-gTextures[graphic]->getWidth()/2, y-gTextures[graphic]->getHeight()/2);
    if(text != "") gTextTextures[textureName]->render(x-gTextTextures[textureName]->getWidth()/2, y-gTextTextures[textureName]->getHeight()/2);
}