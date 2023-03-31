// Fichier GlobalWin.cpp

#include <windows.h>

bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle

//bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default

HINSTANCE	hInstance;		// Holds The Instance Of The Application
