#ifndef _DENGINE_
#define _DENGINE_

class DGameStateEngine;

namespace DRenderer
{
	class	D3DInitializer;
};

// Singleton object
class DEngine
{
public:
	inline float		GetWinWidth()	const		{	return m_fWinWidth; }
	inline float		GetWinHeight()	const		{	return m_fWinHeight; }
	inline bool			IsFullscreen()	const		{	return m_bFullscreen; }
	inline bool			IsRunning()		const		{	return m_bRun; }
	inline bool			IsOGL()			const		{	return m_bOGL; }

	inline HWND			GetHwnd()		const		{	return m_hWnd; }

	inline void			SetWinWidth(float w)	{ this->m_fWinWidth = w; }
	inline void			SetWinHeight(float h)	{ this->m_fWinHeight = h; }
	inline void			IsFullscreen(bool f)	{ this->m_bFullscreen = f; }
	inline void			IsRunning(bool r)		{ this->m_bRun = r; }
	inline void			IsOGL(bool o)			{ this->m_bOGL = o; }
	inline void			SetHwnd(HWND h)			{ this->m_hWnd = h; }


	//*************************************************************************
	// Resize the window
	void				ResizeWindow();
	void				SetMousePos(int, int);

private:
	HWND				m_hWnd;
	float				m_fWinWidth;
	float				m_fWinHeight;

	int					m_nMousePosX;
	int					m_nMousePosY;

	bool				m_bFullscreen;
	bool				m_bRun;
	bool				m_bOGL;
	
	DRenderer::D3DInitializer *		_d3d;
	DGameStateEngine *	_player;
public:
	static DEngine*	GetInstance();
	static bool		DeleteInstance();

	void Initialize();
	bool Run();
private:
	static	DEngine*	m_pInstance;

	DEngine(void);
	~DEngine(void);
};

#endif