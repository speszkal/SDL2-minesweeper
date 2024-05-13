#include "src/dependencies.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    
    std::cout<<"--- Keystrokes guide ---"<<std::endl;
    std::cout<<"F3 - toggle FPS display"<<std::endl;
    std::cout<<"F4 - toggle FPS cap (30 fps, disabled by default)"<<std::endl;
    
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
    
    Timer fpsCapTimer;
    gStateMachine.render(game.getRenderer());
    while(gRunning)
    {   
        fpsCapTimer.start();

        game.handleEvents();
        game.update();
        game.render();

        if(fpsCapTimer.getTicks() < 1000/FPS_CAP && capFPS) SDL_Delay(1000/FPS_CAP-fpsCapTimer.getTicks());
    }
    game.close();

    return 0;
}