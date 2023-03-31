// Fichier InitialisationGL.cpp

#include <windows.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <stdio.h>
#include "mur.h"
#include "global.h"
#include "globalWin.h"
#include "texture2.h"

int InitGL(void)										// All Setup For OpenGL Goes Here
{
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Fond blanc

	// Setup and enable light 0
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);

  // Pour séparer le calculs des faces avant et arrière
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// Enable lighting
	glEnable(GL_LIGHTING);
	// Enable this light in particular
	glEnable(GL_LIGHT0);

  int code = MakeMurCallList(100.0, 10.0, 1.0); // longueur x hauteur x épaisseur
  if(code != 0)
		MessageBox(NULL,"Fichier texture pas trouvé",
                          "ERROR",MB_OK|MB_ICONEXCLAMATION);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
  char Texte[80];
  sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
  SetWindowText(hWnd, Texte);
  return 1;										// Initialization Went OK
}
