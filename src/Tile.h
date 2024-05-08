#ifndef Tile_h
#define Tile_h

class Tile
{
    public:
        int x, y, width, height;
        int value;
        bool hidden, flagged, bomb;

        Tile(int x, int y, int width, int height, bool bomb);
        ~Tile();

        virtual void update();
        virtual void render(SDL_Renderer* renderer);
};

#endif // Tile_h