#ifndef Game_h
#define Game_h

class Game
{   
    public:
        bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        bool loadMedia();

        SDL_Renderer* getRenderer() { return renderer; }
        
        void handleEvents();
        void update();
        void render();

        void close();

    private:
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        SDL_Event e;
};

#endif // Game_h