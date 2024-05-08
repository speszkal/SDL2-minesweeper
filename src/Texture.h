#ifndef Texture_h
#define Texture_h

class Texture
{   
    public:
        Texture(SDL_Renderer* r);
        ~Texture();

        void loadFromFile(std::string path);
        void free();
        void render(int x, int y, SDL_Rect* clip=NULL, double angle=0.0, SDL_Point* center=NULL, SDL_RendererFlip flip=SDL_FLIP_NONE);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* texture;

        int width;
        int height;

        SDL_Renderer* renderer;
};

#endif // Texture_h