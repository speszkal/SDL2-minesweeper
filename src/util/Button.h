#ifndef Button_h
#define Button_h

class Button
{   
    public:
        Button(int x, int y, int width, int height, std::string textureName, std::string text="", std::string graphic="");
        ~Button();

        virtual void update();
        virtual void render(SDL_Renderer* renderer);
        
        bool ifPressed() { return isPressed; };
        bool ifDown() { return isDown; };
        bool getWidth() { return width; };
        bool getHeight() { return height; };

        void setText(std::string newText) { text = newText; }
        void setGraphic(std::string newGraphic) { graphic = newGraphic; }

    private:
        int x, y, width, height;
        std::string textureName, text, graphic;

        bool isPressed=false;
        bool isDown=false;
};

#endif // Button_h