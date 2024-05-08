#include "dependencies.h"

StateMachine::StateMachine()
{
    currentState = &PlayState::getInstance();
    currentState->enter();
}

StateMachine::~StateMachine()
{}

void StateMachine::change(BaseState& newState)
{
    currentState->exit();
    currentState = &newState;
    currentState->enter();
}