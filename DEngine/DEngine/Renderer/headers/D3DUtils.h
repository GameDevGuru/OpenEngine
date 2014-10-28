#pragma once

#include <D3DX11.h>
#include <xnamath.h>

namespace DRenderer
{
	struct DPosColVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	class D3DUtils
	{
	public:
		D3DUtils();
		~D3DUtils();
	};
};
