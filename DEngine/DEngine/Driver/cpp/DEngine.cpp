#include "..\..\stdafx.h"

#include "..\headers\DEngine.h"
#include "..\..\Renderer\headers\D3DInitializer.h"

#define		WINWIDTH	1024
#define		WINHEIGHT	768

extern		BOOL	_ogl;

DEngine*	DEngine::m_pInstance	=	nullptr;

DEngine*	DEngine::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new DEngine();
	}

	return	m_pInstance;
}

bool		DEngine::DeleteInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		return true;
	}
	printf("Unable to delete the instance. DEngine is pointing to null memory");
	return false;
}

void DEngine::Initialize()
{
	_d3d = DRenderer::D3DInitializer::GetInstance();
	_d3d->Initialize(m_hWnd);
}

DEngine::DEngine() : m_fWinWidth(WINWIDTH), m_fWinHeight(WINHEIGHT), m_bRun(true), m_bFullscreen(false)
{
	m_nMousePosX	= 0;
	m_nMousePosY	= 0;
}

DEngine::~DEngine(void)
{
	_d3d->DeleteInstance();
}

void	DEngine::ResizeWindow()
{
#if _DEBUG
	printf("Resizing the window\n");
#endif
}

void	DEngine::SetMousePos(int x, int y)
{
	m_nMousePosX = x;
	m_nMousePosY = y;
#if _DEBUG
	printf("Mouse Position: (%d, %d)\n", x, y);
#endif
}

bool DEngine::Run()
{
	if (Input() == false)
		m_bRun = false;
	Update();
	Render();

	return m_bRun;
}

bool DEngine::Input()
{
	if (GetAsyncKeyState(VK_RETURN))
		return false;

	return true;

}
void DEngine::Update()
{

}

void DEngine::Render()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	ID3D11RenderTargetView * rtv = _d3d->GetRenderTargetView();

	_d3d->GetDeviceContext()->ClearRenderTargetView(rtv, ClearColor);

	_d3d->GetSwapChain()->Present(0, 0);
}