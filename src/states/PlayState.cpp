#include "../dependencies.h"

void PlayState::enter()
{
    gRunning = true;
    tilesLeft = MAX_TILES;

    int idx=0;

    for(int y=90; y<INSIDE_WINDOW_HEIGHT+90; y=y+TILE_SIZE)
    {
        for(int x=90; x<INSIDE_WINDOW_WIDTH+90; x=x+TILE_SIZE)
        {
            tileMap[idx] = new Tile(x, y, TILE_SIZE, TILE_SIZE, random(1, 100)<10);
            if(tileMap[idx]->bomb) tilesLeft--;

            int tabLenght = INSIDE_WINDOW_WIDTH/TILE_SIZE;
            int tabHeight = INSIDE_WINDOW_HEIGHT/TILE_SIZE;
            std::vector<int> entourage;

            if(idx == 0) entourage = {1, tabLenght+1, tabLenght};
            else if(idx == tabLenght-1) entourage = {tabLenght, tabLenght-1, -1};
            else if(idx == (tabHeight * tabLenght)-1) entourage = {-tabLenght-1, -tabLenght, -1};
            else if(idx == (tabHeight-1)*tabLenght) entourage = {-tabLenght, -tabLenght+1, 1};
            else if(idx < tabLenght-1) entourage = {1, tabLenght+1, tabLenght, tabLenght-1, -1};
            else if((idx+1)%tabLenght == 0) entourage = {-tabLenght-1, -tabLenght, tabLenght, tabLenght-1, -1};
            else if(idx > (tabHeight-1)*tabLenght) entourage = {-tabLenght-1, -tabLenght, -tabLenght+1, 1, -1};
            else if(idx%tabLenght == 0) entourage = {-tabLenght, -tabLenght+1, 1, tabLenght+1, tabLenght};
            else entourage = {-tabLenght-1, -tabLenght, -tabLenght+1, 1, tabLenght+1, tabLenght, tabLenght-1, -1};
            
            graf[idx] = entourage;

            idx++;
        }
    }
}

void PlayState::tileDiscovery(int start)
{
    if(tileMap[start]->bomb)
    {
        tileMap[start]->hidden = false;
        tileMap[start]->value = -1;
        gStateMachine.change(GameOverState::getInstance());
        return;
    }

    std::queue<int> Q;
    Q.push(start);
    tileMap[start]->hidden = false;
    while(Q.size())
    {
        int v = Q.front();
        Q.pop();
        tilesLeft--;

        int bombCount = 0;
        for(auto offset : graf[v])
        {
            int u = v + offset;
            if(tileMap[u]->bomb) bombCount++;
        }
            
        
        tileMap[v]->value = bombCount;
        if(bombCount) continue;
        for(auto offset : graf[v])
        {
            int u = v + offset;
            if(!tileMap[u]->hidden) continue;
            tileMap[u]->hidden = false;
            Q.push(u);
        }
    }
}

void PlayState::update()
{   
    if(tilesLeft == 0) std::cout<<"YOU'VE WON!"<<std::endl;
    
    for(int i=0; i<MAX_TILES; i++)
    {   
        if(!mousePressed || !mouseCollision(tileMap[i]->x, tileMap[i]->y, tileMap[i]->width, tileMap[i]->height)) continue;
            
        if(mouseButton == "left" && !tileMap[i]->flagged) tileDiscovery(i);
        else if(mouseButton == "right" && tileMap[i]->hidden) (tileMap[i]->flagged) ? tileMap[i]->flagged=false : tileMap[i]->flagged=true;

        tileMap[i]->update();
    }

    mouseButton = "none";
    mousePressed = false;
}

void PlayState::render(SDL_Renderer* renderer)
{   
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    
    for(int i=0; i<MAX_TILES; i++)
        tileMap[i]->render(renderer);
    
    SDL_RenderPresent(renderer);
}

void PlayState::exit()
{
    for(int i=0; i<MAX_TILES; i++)
    {
        if(tileMap[i]->flagged && tileMap[i]->bomb) continue;
        
        if(tileMap[i]->flagged) tileMap[i]->value=-1;
        if(tileMap[i]->bomb) tileMap[i]->hidden = false;

        std::cout<<"YOU'VE WON!"<<std::endl;
    }
}

PlayState::~PlayState()
{
    for(auto tile : tileMap) { delete tile; }
    //delete objects
}

BaseState& PlayState::getInstance()
{
    static PlayState singleton;
    return singleton;
}