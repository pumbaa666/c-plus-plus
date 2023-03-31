// Fichier GlobalWin.h

#ifndef GLOBALWIN_H
#define GLOBALWIN_H

extern bool	fullscreen;
extern HINSTANCE	hInstance;		// Holds The Instance Of The Application
extern HDC		hDC;		// Private GDI Device Context
extern HGLRC	hRC;		// Permanent Rendering Context
extern HWND		hWnd;		// Holds Our Window Handle

//extern bool	keys[];			// Array Used For The Keyboard Routine
extern bool	active;		// Window Active Flag Set To TRUE By Default

#endif
