#include "../dependencies.h"

void VictoryState::enter()
{   
    
}

void VictoryState::update()
{   
    if(mousePressed) gStateMachine.change(PlayState::getInstance());
    
    mouseButton = "none";
    mousePressed = false;
}

void VictoryState::render(SDL_Renderer* renderer)
{   
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    
    PlayState::getInstance().render(renderer);
    gTextTextures["victory"]->render(LEFT_MARGIN+(INSIDE_WINDOW_WIDTH-gTextTextures["victory"]->getWidth())/2, TOP_MARGIN+(INSIDE_WINDOW_HEIGHT-gTextTextures["victory"]->getHeight())/2);
    
    SDL_RenderPresent(renderer);
}

void VictoryState::exit()
{
    
}

VictoryState::~VictoryState()
{
    
    //delete objects
}

BaseState& VictoryState::getInstance()
{
    static VictoryState singleton;
    return singleton;
}