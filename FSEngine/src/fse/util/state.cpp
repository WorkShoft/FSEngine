#include "pch.h"
#include "state.h"

namespace FSEngine {

State *StateManager::m_currentState;

void StateManager::Update()
{
	m_currentState->onUpdate();
}

void StateManager::Render()
{
	m_currentState->onRender();
}

void StateManager::ChangeState(State *state)
{
	if(m_currentState) m_currentState->onExit();
	m_currentState = state;
	m_currentState->onEnter();
}

}