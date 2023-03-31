// Fichier InitialisationGL.cpp

#include <windows.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <stdio.h>
#include "global.h"
#include "globalWin.h"
#include "texture2.h"

int InitGL(void)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);				// Black Background
//	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
//	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
  texture1 = TextureLoad("lilou.bmp", GL_FALSE,
                                      GL_LINEAR_MIPMAP_LINEAR,
                                      GL_LINEAR,
                                      GL_REPEAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
  char Texte[80];
  sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
  SetWindowText(hWnd, Texte);
  if(texture1 == 0) return 0;
  else return 1;										// Initialization Went OK
}
