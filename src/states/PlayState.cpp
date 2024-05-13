#include "../dependencies.h"

void PlayState::enter()
{
    gRunning = true;
    tilesLeft = MAX_TILES;

    int idx=0;

    for(int y=TOP_MARGIN; y<WINDOW_HEIGHT-BOTTOM_MARGIN; y=y+TILE_SIZE)
    {
        for(int x=LEFT_MARGIN; x<WINDOW_WIDTH-RIGHT_MARGIN; x=x+TILE_SIZE)
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

    gameTimer.start();
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
    gTextTextures["timer"]->loadFromRenderedText("font-l", std::to_string(gameTimer.getTicks()/1000), {200, 0, 35});
    
    if(tilesLeft < 0)
    {
        std::cout<<"YOU'VE WON!"<<std::endl;
        gStateMachine.change(VictoryState::getInstance());
    }
    
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
    gTextures["background"]->render(0, 0);
    
    for(int i=0; i<MAX_TILES; i++)
        tileMap[i]->render(renderer);

    gTextTextures["timer"]->render(WINDOW_WIDTH/4, 50-gTextTextures["timer"]->getHeight()/2);
}

void PlayState::exit()
{
    for(int i=0; i<MAX_TILES; i++)
    {
        if(tileMap[i]->flagged && tileMap[i]->bomb) continue;
        
        if(tileMap[i]->flagged) tileMap[i]->value=-1;
        if(tileMap[i]->bomb) tileMap[i]->hidden = false;
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