#pragma once
#include <vector>

namespace DRenderer
{
	struct DPosColVertex;
}

namespace DRenderer
{
	class DTriangle
	{
		std::vector<DRenderer::DPosColVertex *> verts;
	public:
		DTriangle();
		~DTriangle();
	};
};