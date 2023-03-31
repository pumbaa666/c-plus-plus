// Fichier Principal.cpp

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "globalwin.h"
#include "global.h"
#include "MesRessources.rh"
#include "evenements.h"
#include "geometrie.h"
#include "initialisation.h"
#include "principal.h"

int xInit;
int yInit;
bool ButtonLeftDown = false;
bool ButtonRightDown = false;

//***************************************************************************
// Procédure de fenêtre : WndProc
// Cette fonction est appelée lorsqu'un événement survient.
//***************************************************************************
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			            // Message For This Window
							WPARAM	wParam,		         	// Additional Message Information
							LPARAM	lParam)			        // Additional Message Information
{
	switch (uMsg)									  // Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))				// Check Minimization State
			{
				active=TRUE;						  // Program Is Active
			}
			else
			{
				active=FALSE;						  // Program Is No Longer Active
			}
			return 0;								    // Return To The Message Loop
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
        return 0;
			}
			break;
		}
		
		case WM_COMMAND:
		{
	    switch(LOWORD(wParam))
	    {
        case ID_FILE_EXIT:
             PostMessage(hWnd, WM_CLOSE, 0, 0);
		    return 0;
		  }
  	}        

		case WM_CREATE :
		{
		  if(animationOn)
		  {
		    // Pour plus de précision, il faudrait utiliser timeSetEvent()
		    if(!SetTimer(hWnd, ID_TIMER, 10, NULL))
          MessageBox(hWnd, "SetTimer Failed", "Error", MB_OK);
      }    
		  return 0;
		}

    // WM_CLOSE est envoyé par le bouton de fermeture et par <ALT><F4>
    // On peut faire des tests ici, p. ex. demander de sauver un fichier.
		case WM_CLOSE:						// Did We Receive A Close Message?
		{
      PostQuitMessage(0);				// Send A Quit Message
//			DestroyWindow(hWnd);
			return 0;						// Jump Back
		}
/*
    // Il ne faut pas intercepter le message WM_DESTROY ici
    // car quand on passe en mode fullScreen, la fonction envoie
    // justement un message WM_DESTROY.
		case WM_DESTROY :
		{
      PostQuitMessage(0);						// Send A Quit Message
		  return 0;
		}    
*/
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
//			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			EvKeyDown(wParam);
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
//			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		
		case WM_LBUTTONDOWN :
		{
	    SetCapture(hWnd);
	    ButtonLeftDown = true;
	    xInit = LOWORD ( lParam );
	    yInit = HIWORD ( lParam );
			return 0;								// Jump Back
		}    

		case WM_LBUTTONUP :
		{
	    ReleaseCapture();
	    ButtonLeftDown = false;
			return 0;								// Jump Back
		}    

		case WM_RBUTTONDOWN :
		{
      SetCapture(hWnd);
      ButtonRightDown = true;
      xInit = LOWORD ( lParam );
      yInit = HIWORD ( lParam );
			return 0;								// Jump Back
		}    

		case WM_RBUTTONUP :
		{
      ReleaseCapture();
      ButtonRightDown = false;
			return 0;								// Jump Back
	  }    

		case WM_MOUSEMOVE :
		{
      EvMouseMove(LOWORD ( lParam ) /*x*/,
                  HIWORD ( lParam ) /*y*/,
                  xInit, yInit,
                  ButtonLeftDown, ButtonRightDown);
      return 0;								// Jump Back
		}    

		case WM_PAINT:
    {
      PAINTSTRUCT ps;
      BeginPaint(hWnd, &ps);
      if (hRC)
      {
        Display();
      }
      EndPaint(hWnd, &ps);
      return 0;
    }
        
    case WM_TIMER :
    {
      int idTimer = LOWORD (wParam);
      Animation(idTimer);
      return 0;
    }    
//        break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//***************************************************************************
// Point d'entrée du programme : WinMain
//***************************************************************************
int WINAPI WinMain(	HINSTANCE	/*hInstance*/,			// Instance
					HINSTANCE	/*hPrevInstance*/,		// Previous Instance
					LPSTR		/*lpCmdLine*/,			// Command Line Parameters
					int			/*nCmdShow*/)			// Window Show State
{
	MSG		msg;								// Windows Message Structure

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?",
                   "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Canevas OpenGL avec l'API Window",800,600,16,fullscreen))
	{
		return 0;							// Quit If Window Was Not Created
	}

  // process messages
  // Quand l'application envoie le message WM_QUIT, GetMessage()
  // renvoie la valeur 0
  // Si il y a une erreur, GetMessage() renvoie une valeur négative.
  while (GetMessage(&msg, NULL, 0, 0) > 0)
  {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
  }

	// Shutdown
  KillTimer(hWnd, ID_TIMER);
  KillGLWindow();							  // Kill The Window
	return (msg.wParam);					// Exit The Program
}
