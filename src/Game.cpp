#include "dependencies.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    bool success = true;
    
    int flags = 0;
    if(fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout<<"SDL could not initialize! SDL_Error: " << SDL_GetError() <<std::endl;
        success = false;
    }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(window == NULL)
    {
        std::cout<<"Window could not be created! SDL_Error: " << SDL_GetError() <<std::endl;
        success = false;
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if(renderer == NULL)
    {
        std::cout<< "Renderer could not be created! SDL Error: " << SDL_GetError() <<std::endl;
        success = false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if( !(IMG_Init(imgFlags) & imgFlags) )
    {
        std::cout<< "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() <<std::endl;
        success = false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        std::cout<< "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() <<std::endl;
        success = false;
    }
    
    //gStateMachine.change(PlayState::getInstance());
    gRunning = true;
    fpsTimer.start();
    
    return success;
}

bool Game::loadMedia()
{
    bool success = true;
    
    //Fonts
    gFonts["font-s"] = TTF_OpenFont( ".\\fonts\\font.ttf", 25);
    gFonts["font-l"] = TTF_OpenFont( ".\\fonts\\font.ttf", 50 );
    
    for(auto font : gFonts)
    {
        if(font.s == NULL)
        {
            std::cout<< "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() <<std::endl;
            success = false;
        }
    }

    //Textures made from fonts
    gTextTextures["fps"] = new Texture(renderer);    gTextTextures["fps"]->loadFromRenderedText("font-s", "0", {0, 0, 200});
    gTextTextures["game-over"] = new Texture(renderer);    gTextTextures["game-over"]->loadFromRenderedText("font-l", "Game Over!", {0, 0, 0});
    gTextTextures["victory"] = new Texture(renderer);    gTextTextures["victory"]->loadFromRenderedText("font-l", "You've won!", {0, 0, 0});
    gTextTextures["timer"] = new Texture(renderer);    gTextTextures["timer"]->loadFromRenderedText("font-l", "0", {200, 0, 35});

    for(auto tt : gTextTextures)
    {
        if(tt.s == NULL)
        {
            std::cout<< "Failed to render text texture!" <<std::endl;
            success = false;
        }
    }

    //Textures
    gTextures["tiles-spritesheet"] = new Texture(renderer);    gTextures["tiles-spritesheet"]->loadFromFile(".\\graphics\\tiles.png");
    gTextures["background"] = new Texture(renderer);    gTextures["background"]->loadFromFile(".\\graphics\\background.png");
    
    for(auto t : gTextures)
    {
        if(t.s == NULL)
        {
            std::cout<< "Failed to load \'" << t.f << "\' texture image! SDL_image Error: " << IMG_GetError() <<std::endl;
            success = false;
        }
    }

    return success;
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            gRunning = false;
            break;
        }

        //keyboard input event handling
        if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE) gRunning = false;
            if(e.key.keysym.sym == SDLK_F3) showFPS ? showFPS = false : showFPS = true;
            if(e.key.keysym.sym == SDLK_F4)
            {
                if(capFPS)
                {
                    capFPS = false;
                    std::cout<<"FPS cap off."<<std::endl;
                }
                else
                {
                    capFPS = true;
                    std::cout<<"FPS cap on."<<std::endl;
                }
            }
            gKeyPressed[e.key.keysym.sym] = true;
        }

        //mouse input event handling
        if(e.type == SDL_MOUSEMOTION)
            SDL_GetMouseState( &xMouse, &yMouse );

        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            mousePressed = true;
            
            if(e.button.button == SDL_BUTTON_LEFT)
                mouseButton = "left";
            else if (e.button.button == SDL_BUTTON_RIGHT)
                mouseButton = "right";
        }
    }
}

void Game::update()
{   
    gStateMachine.update();
    for(auto key : gKeyPressed) key.s = false;
    
    float fps;
    if(fpsTimer.getTicks()>75)
    {
        fps = frameCounter / (fpsTimer.getTicks() / 1000.f);
        frameCounter = 0;
        fpsTimer.start();

        gTextTextures["fps"]->loadFromRenderedText("font-s", std::to_string(fps), {0, 0, 200});
    }
}

void Game::render()
{   
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    gStateMachine.render(renderer);

    if(showFPS) gTextTextures["fps"]->render(0, 0);

    SDL_RenderPresent(renderer);
    
    frameCounter++;
}

void Game::close()
{   
    for(auto t : gTextures) { t.s->free(); }
    for(auto tt : gTextTextures) { tt.s->free(); }
    for(auto& font : gFonts)
    {
        TTF_CloseFont( font.s );
        font.s = NULL;
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}