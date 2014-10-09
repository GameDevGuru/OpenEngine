#include "..\..\stdafx.h"

#include "..\headers\DEngine.h"
#include "..\..\Renderer\headers\D3DInitializer.h"

#include "..\headers\DGameStateEngine.h"
#include "..\..\Game States\headers\DGamePlayState.h"

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

	DState * _first_state = new DGamePlayState();
	_player = new DGameStateEngine(_first_state);
}

DEngine::~DEngine(void)
{
	_d3d->DeleteInstance();

	if (_player != nullptr)
	{
		delete _player;
		_player = nullptr;
	}
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
	if (_player->Input() == false)
		m_bRun = false;
	_player->Update();
	_player->Render();

	return m_bRun;
}