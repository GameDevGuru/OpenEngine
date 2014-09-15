//**************************************************************************
//	Daniel Waseem, Copyright 2013
//
//*************************************************************************

// #include "stdafx.h"  <=== automatically done by the compiler
#include "Driver\Headers\DEngine.h"
//#include "DDirectXRenderer\Source\D3DInitializer.h"

#define		WIN32_LEAN_AND_MEAN
#include	<windowsx.h>

HINSTANCE	d_hInstance	=	NULL;
HWND		d_hWND		=	NULL;
DEVMODE		_dDevMode;
BOOL		_ogl		=	FALSE;

HANDLE		hConsole;

enum Color { BLUE = 1, GREEN = 2, RED = 4, YELLOW = 6, INTENSIFY = 8, DEFAULT = 7 };


#pragma region Forward Declarations
// Main window message processor
LRESULT CALLBACK WinProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	);

bool	GenerateConsole();
bool	GenerateWindow(WNDCLASSEX &wcex);
bool	GenerateHWND(HWND &hwnd, const DEngine* const driver, LPCWSTR szClassName);
#pragma endregion

int CALLBACK WinMain( _In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance,
					 _In_  LPSTR lpCmdLine,	_In_  int nCmdShow)
{	
	AllocConsole();
	GenerateConsole();

	DEngine* driver = DEngine::GetInstance();
	if(_ogl)
	{

	}
	else
	{
		//DDirectXRenderer::D3DInitializer::GetInstance()->D3DInitialize();
	}

	//**********************************************************
	// Generate the Window
	//*********************************************
	d_hInstance			= hInstance;
	WNDCLASSEX wcex;
	if(!GenerateWindow(wcex))
		return -1;

	HWND hWnd;
	if(!GenerateHWND(hWnd, driver, wcex.lpszClassName))
		return -1;
	driver->SetHwnd(hWnd);
	driver->Initialize();
	//***********************************************************
	// Show the Window
	//********************************************
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while(msg.message != WM_QUIT && driver->Run())
	{
		driver->Run();
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{ 
			TranslateMessage( &msg );
			DispatchMessage( &msg ); 
		}
	}

	driver->DeleteInstance();

	return (int)msg.wParam;
}

LRESULT CALLBACK WinProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	// sort through and find what code to run for the message given
	switch(uMsg)
	{
	case WM_CREATE:
		{
			RAWINPUTDEVICE		inputDevices[2];

			// RAW Keyboard input
			inputDevices[0].dwFlags = 0;
			inputDevices[0].hwndTarget = NULL;
			inputDevices[0].usUsage = 6;
			inputDevices[0].usUsagePage = 1;

			// RAW Mouse Input
			inputDevices[1].dwFlags = 0;
			inputDevices[1].hwndTarget = NULL;
			inputDevices[1].usUsage = 2;
			inputDevices[1].usUsagePage = 1;

			if(!RegisterRawInputDevices(inputDevices, 2, sizeof(RAWINPUTDEVICE)))
			{
				SetConsoleTextAttribute(hConsole, RED | INTENSIFY);
				printf("Input Error! Error creating the input devices.\n");
			}
			else
			{
				SetConsoleTextAttribute(hConsole, GREEN | INTENSIFY);
				printf("Success! Registered the input devices.\n");
			}
			SetConsoleTextAttribute(hConsole, DEFAULT);
		}
		break;
	case WM_SIZE:
		{
			DEngine::GetInstance()->ResizeWindow();
		}
		break;
	case WM_MOUSEMOVE:
		{
			DEngine::GetInstance()->SetMousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}
		break;
		// this message is read when the window is closed
	case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		{
			// close the application entirely
			FreeConsole();
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

bool	GenerateWindow(WNDCLASSEX &wcex)
{
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize		 = sizeof(WNDCLASSEX);
	wcex.style		 = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_OWNDC;
	wcex.hbrBackground	= NULL;
	wcex.hCursor	 = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon		 = NULL;
	wcex.hInstance	 = d_hInstance;
	wcex.hIconSm	 = NULL;
	wcex.lpfnWndProc = (WNDPROC)WinProc;  
	wcex.lpszClassName = TEXT("DEngine");
	wcex.cbWndExtra	 = NULL;
	wcex.lpszMenuName = NULL;

	if(!RegisterClassEx(&wcex))
	{
		SetConsoleTextAttribute(hConsole, RED | INTENSIFY);
		printf("Error 1 Window class was not created correctly!\n");
		SetConsoleTextAttribute(hConsole, DEFAULT);
		return false;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, GREEN | INTENSIFY);
		printf("Success! Generated the window class\n");
		SetConsoleTextAttribute(hConsole, DEFAULT);
		return true;
	}

}

bool	GenerateHWND(HWND &hwnd, const DEngine* const driver, LPCWSTR szClassName)
{
	UINT winStyle,winStyleX;
	if(driver->IsFullscreen())
	{
		winStyle	= WS_POPUP;
		winStyleX	= WS_EX_TOPMOST;
	}
	else
	{
		winStyle	= WS_OVERLAPPEDWINDOW;
		winStyleX	= NULL;
	}

	RECT	window_size = { 0, 0, (LONG)driver->GetWinWidth(), (LONG)driver->GetWinHeight() };
	if(!AdjustWindowRect(&window_size, winStyle, false))
	{
		printf("Error! Unable to adjust the window rect.\n");
		return false;
	}

	hwnd		= CreateWindowEx(winStyleX, szClassName, L"DEngine Main", winStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		window_size.right - window_size.left,
		window_size.bottom - window_size.top,
		NULL, NULL, d_hInstance, NULL);
	if(!hwnd)
	{
		SetConsoleTextAttribute(hConsole, RED | INTENSIFY);
		printf("HWND Error! HWND is null. Failed to create the HWND.\n");
		SetConsoleTextAttribute(hConsole, DEFAULT);
		return false;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, GREEN | INTENSIFY);
		printf("Success Generated the HWND.\n");
		SetConsoleTextAttribute(hConsole, DEFAULT);
		return true;
	}
}

bool GenerateConsole()
{
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = handle_out;
	int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	SetConsoleTitle(L"Debugger");

	return true;
}