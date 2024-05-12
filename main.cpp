#include "src/dependencies.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    
    Game game;
    
    if(!game.init("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, false))
    {
        std::cout<<"ERROR: Game could not be initialized."<<std::endl;
        game.close();
        return 0;
    }
    
    if(!game.loadMedia())
    {
        std::cout<<"ERROR: Failed to load media."<<std::endl;
        game.close();
        return 0;
    }
    
    gStateMachine.render(game.getRenderer());
    while(gRunning)
    {
        game.handleEvents();
        game.update();
        game.render();
    }
    game.close();
    std::cout<<"END"<<std::endl;

    return 0;
}