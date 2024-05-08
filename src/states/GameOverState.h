#ifndef GameOverState_h
#define GameOverState_h

class GameOverState: public BaseState
{
public:
	~GameOverState() override;
    
    void enter();
    void update();
    void render(SDL_Renderer* renderer);
	void exit();
	static BaseState& getInstance();;

private:
	GameOverState() {}
	GameOverState(const GameOverState& other);
	GameOverState& operator=(const GameOverState& other);
};

#endif // GameOverState_h