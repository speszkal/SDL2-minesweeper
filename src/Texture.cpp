#include "dependencies.h"

Texture::Texture(SDL_Renderer* r)
{
    this->texture = NULL;

    this->width = 0;
    this->height = 0;

    this->renderer = r;
}

Texture::~Texture()
{
    free();
}

void Texture::loadFromFile(std::string path)
{
    free();
    
    texture = IMG_LoadTexture(renderer, path.c_str());

    if(texture == NULL)
        std::cout<< "Unable to create texture from '" << path<< "'! SDL Error: " << SDL_GetError() <<std::endl;
    else
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Texture::free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect* srcrect, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect dstrect = {x, y, width, height};

    if(srcrect != NULL)
    {
        dstrect.w = srcrect->w;
        dstrect.h = srcrect->h;
    }

    SDL_RenderCopyEx(renderer, texture, srcrect, &dstrect, angle, center, flip);
}

int Texture::getWidth() { return width; }
int Texture::getHeight() { return height; }