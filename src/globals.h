#ifndef globals_h
#define globals_h

extern bool capFPS;

extern StateMachine gStateMachine;

extern std::map<std::string, Texture*> gTextures;

extern std::map<std::string, TTF_Font*> gFonts;
extern std::map<std::string, Texture*> gTextTextures;

extern std::map<SDL_Keycode, bool> gKeyPressed;

extern int random(int a, int b);
extern bool mouseCollision(int x, int y, int width, int height);

extern bool gRunning;

extern int xMouse;
extern int yMouse;
extern bool mouseButtonDown;
extern bool mouseButtonUp;
extern std::string mouseButton;

#endif // globals_h