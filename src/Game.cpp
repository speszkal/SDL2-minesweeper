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
    
    return success;
}

bool Game::loadMedia()
{
    bool success = true;
    
    //Fonts
    gFonts["big"] = TTF_OpenFont( ".\\fonts\\font.ttf", 50 );
    
    for(auto font : gFonts)
    {
        if(font.s == NULL)
        {
            std::cout<< "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() <<std::endl;
            success = false;
        }
    }

    //Textures made from fonts
    gTextTextures["game-over"] = new Texture(renderer);    gTextTextures["game-over"]->loadFromRenderedText("big", "Game Over!", {0, 0, 0});

    for(auto tt : gTextTextures)
    {
        if(tt.s == NULL)
        {
            std::cout<< "Failed to render text texture!" <<std::endl;
            success = false;
        }
    }

    //Textures
    gTextures["background"] = new Texture(renderer);    gTextures["background"]->loadFromFile(".\\graphics\\background.png");
    gTextures["tile-basic"] = new Texture(renderer);    gTextures["tile-basic"]->loadFromFile(".\\graphics\\tile.png");
    gTextures["tile-flagged"] = new Texture(renderer);    gTextures["tile-flagged"]->loadFromFile(".\\graphics\\flagged.png");
    gTextures["tile-incorrectly-flagged"] = new Texture(renderer);    gTextures["tile-incorrectly-flagged"]->loadFromFile(".\\graphics\\flagged-x.png");
    gTextures["bomb"] = new Texture(renderer);    gTextures["bomb"]->loadFromFile(".\\graphics\\bomb.png");
    gTextures["bomb-clicked"] = new Texture(renderer);    gTextures["bomb-clicked"]->loadFromFile(".\\graphics\\bomb-red.png");
    for(int i=0; i<=8; i++)
    {
        std::string filename = ".\\graphics\\" + std::to_string(i) + ".png";
        std::string txtName = "tile" + std::to_string(i);
        gTextures[txtName] = new Texture(renderer);    gTextures[txtName]->loadFromFile(filename);
    }
    
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
}

void Game::render()
{
    gStateMachine.render(renderer);
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