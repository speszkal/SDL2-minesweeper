#include "../dependencies.h"

void GameOverState::enter()
{
    std::cout<<"GAME OVER"<<std::endl;
}

void GameOverState::update()
{   
    if(mousePressed) gStateMachine.change(PlayState::getInstance());
    
    mouseButton = "none";
    mousePressed = false;
}

void GameOverState::render(SDL_Renderer* renderer)
{   
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    
    PlayState::getInstance().render(renderer);
    
    SDL_RenderPresent(renderer);
}

void GameOverState::exit()
{
    
}

GameOverState::~GameOverState()
{
    
    //delete objects
}

BaseState& GameOverState::getInstance()
{
    static GameOverState singleton;
    return singleton;
}