#pragma once

#include <vector>

class DState;

class DGameStateEngine
{
public:
	DGameStateEngine(DState * start_state);
	~DGameStateEngine();

	void Initialize();
	void ChangeState(DState * state);
	void PushState(DState * state);
	DState* PopState();

	bool Input();
	void Update();
	void Render();

	std::vector<DState*>		_states;
};