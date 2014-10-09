#pragma once
class DState
{
public:
	DState() { };
	virtual ~DState() = 0 { };

	virtual bool Input() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

