#include "..\headers\DEngine.h"
#include "..\..\stdafx.h"

#define		WINWIDTH	1280
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

DEngine::DEngine() : m_fWinWidth(WINWIDTH), m_fWinHeight(WINHEIGHT), m_bRun(true), m_bFullscreen(false)
{
	m_nMousePosX	= 0;
	m_nMousePosY	= 0;



}

DEngine::~DEngine(void)
{
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
	//printf("Mouse Position: (%d, %d)\n", x, y);
#endif
}