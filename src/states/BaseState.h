#ifndef BaseState_h
#define BaseState_h

class BaseState
{
    public:
        virtual void enter();
        virtual void update();
        virtual void render(SDL_Renderer* r);
        virtual void exit();

        virtual ~BaseState();
};

#endif // BaseState_h