#pragma once
#include "../../Driver/headers/DState.h"

class DGamePlayState : public DState
{
public:
	DGamePlayState();
	virtual ~DGamePlayState();

	virtual bool Input();
	virtual void Update();
	virtual void Render();
};

