#ifndef PlayState_h
#define PlayState_h

class PlayState: public BaseState
{
public:
	~PlayState() override;
    
    void enter();
    void update();
    void render(SDL_Renderer* renderer);
	void exit();
	static BaseState& getInstance();

	Tile* tileMap[MAX_TILES+2*INSIDE_WINDOW_WIDTH/TILE_SIZE+2*INSIDE_WINDOW_HEIGHT/TILE_SIZE+4];
	std::vector<int> graf[MAX_TILES];
	int tilesLeft;
	Timer gameTimer;
	Button* menuButton;
	bool pause=false;

private:
	PlayState() {}
	PlayState(const PlayState& other);
	PlayState& operator=(const PlayState& other);

	void tileDiscovery(int start);
};

#endif // PlayState_h