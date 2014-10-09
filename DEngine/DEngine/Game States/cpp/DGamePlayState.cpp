#include "..\..\stdafx.h"

#include "..\..\Renderer\headers\D3DInitializer.h"
#include "..\headers\DGamePlayState.h"

DGamePlayState::DGamePlayState()
{

}
DGamePlayState::~DGamePlayState()
{

}

bool DGamePlayState::Input()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x01)
	{
		return false;
	}

	return true;
}
void DGamePlayState::Update()
{

}
void DGamePlayState::Render()
{
	float ClearColor[4] = { 1.0f, 0.125f, 0.3f, 1.0f };
	
	DRenderer::D3DInitializer * d3d = DRenderer::D3DInitializer::GetInstance();
	ID3D11RenderTargetView * rtv = d3d->GetRenderTargetView();

	d3d->GetDeviceContext()->ClearRenderTargetView(rtv, ClearColor);
	d3d->GetSwapChain()->Present(0, 0);
}