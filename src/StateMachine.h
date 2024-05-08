#ifndef StateMachine_h
#define StateMachine_h
#include "states/BaseState.h"

class BaseState;

class StateMachine
{
    public:
        StateMachine();
        ~StateMachine();

        inline BaseState* getCurrentState() const { return currentState; }
        
        void change(BaseState& newState);

        void update() { currentState->update(); }
        void render(SDL_Renderer* r) { currentState->render(r); }

    private:
        BaseState* currentState;
};

#endif // StateMachine_h