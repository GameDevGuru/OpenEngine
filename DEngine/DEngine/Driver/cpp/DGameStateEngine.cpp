#include "..\..\stdafx.h"

#include "..\..\Driver\headers\DState.h"
#include "..\headers\DGameStateEngine.h"

DGameStateEngine::DGameStateEngine(DState * start_state)
{
	_states.push_back(start_state);
}
DGameStateEngine::~DGameStateEngine()
{
	for each (DState* x in _states)
	{
		delete x;
		x = nullptr;
	}
}

void DGameStateEngine::Initialize()
{

}
void DGameStateEngine::ChangeState(DState * state)
{

}
void DGameStateEngine::PushState(DState * state)
{
	_states.push_back(state);
}
DState* DGameStateEngine::PopState()
{
	DState * ret = *(_states.end());
	_states.pop_back();
	return ret;
}

bool DGameStateEngine::Input()
{
	return _states[_states.size() - 1]->Input();
}
void DGameStateEngine::Update()
{
	_states[_states.size() - 1]->Update();
}
void DGameStateEngine::Render()
{
	_states[_states.size() - 1]->Render();
}