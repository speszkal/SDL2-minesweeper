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
        std::cout<< "Unable to create texture from '" << path << "'! SDL Error: " << SDL_GetError() <<std::endl;
    else
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Texture::loadFromRenderedText(std::string fontName, std::string textureText, SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFonts[fontName], textureText.c_str(), textColor);

    if(textSurface == NULL)
        std::cout<<  "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() <<std::endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == NULL)
            std::cout<< "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() <<std::endl;
        else
        {
            width = textSurface->w;
            height = textSurface->h;

            //SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        }

        SDL_FreeSurface(textSurface);
    }
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

void Texture::render(int x, int y, SDL_Rect* srcrect, float xScale, float yScale, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect dstrect = {x, y, round(xScale*width), round(yScale*height)};

    if(srcrect != NULL)
    {   
        dstrect.w = round(xScale*srcrect->w);
        dstrect.h = round(yScale*srcrect->h);
    }

    SDL_RenderCopyEx(renderer, texture, srcrect, &dstrect, angle, center, flip);
}

int Texture::getWidth() { return width; }
int Texture::getHeight() { return height; }