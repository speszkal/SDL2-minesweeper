#ifndef VictoryState_h
#define VictoryState_h

class VictoryState: public BaseState
{
public:
	~VictoryState() override;
    
    void enter();
    void update();
    void render(SDL_Renderer* renderer);
	void exit();
	static BaseState& getInstance();;

private:
	VictoryState() {}
	VictoryState(const VictoryState& other);
	VictoryState& operator=(const VictoryState& other);
};

#endif // VictoryState_h