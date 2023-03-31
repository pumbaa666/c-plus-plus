// Fichier Evenements.cpp

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "global.h"
#include "globalwin.h"
#include "initialisation.h"
#include "geometrie.h"
#include "evenements.h"

#define COS(X) cos( (X) * M_PI/180.0)
#define SIN(X) sin( (X) * M_PI/180.0)

void ReSizeGLScene(int width, int height)		// Resize And Initialize The GL Window
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By
	if (width == 0) width = 1;

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,500.0f);

  DeplacerLaCamera(0.0f, Theta);
}

void Display(void)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glPushMatrix();
      glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Effectuer les rotations
      glRotatef(yRot, 0.0f, 1.0f, 0.0f);
      DessinerLaScene();
	glPopMatrix();
	SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
}

void EvKeyDown(unsigned char key)
{
  static char Texte[80];
  key = (unsigned char) tolower(key);
  switch(key)
  {
  	// Si la touche F1 a été pressée :
  	case VK_F1 :						// Is F1 Being Pressed?
  		KillGLWindow();						// Kill Our Current Window
  		fullscreen=!fullscreen;		// Toggle Fullscreen / Windowed Mode
  		// Recreate Our OpenGL Window
  		if (!CreateGLWindow("Canevas OpenGL avec l'API Window",800,600,16,fullscreen))
  		{
  			PostQuitMessage(0);				// Send A Quit Message
  		}
  		break;
  	
  	case VK_ESCAPE : // Quitter l'application avec ESC
  	    PostQuitMessage(0);
  	    break;
   
    case ' ' :
       if (animationOn)    KillTimer(hWnd, ID_TIMER);
       animationOn = !animationOn;
       if (animationOn)
       {
         // Pour plus de précision, il faudrait utiliser timeSetEvent()
         if(!SetTimer(hWnd, ID_TIMER, 10, NULL))
           MessageBox(hWnd, "SetTimer Failed", "Error", MB_OK);
       }
       break;

    case '1' : Mode ^= 0x1; InvalidateRect(hWnd, NULL, FALSE);
               sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
               SetWindowText(hWnd, Texte);
               break;
    case '2' : Mode ^= 0x2; InvalidateRect(hWnd, NULL, FALSE);
               sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
               SetWindowText(hWnd, Texte);
               break;
    case '3' : Mode ^= 0x4; InvalidateRect(hWnd, NULL, FALSE);
               sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
               SetWindowText(hWnd, Texte);
               break;
    case '4' : Mode ^= 0x8; InvalidateRect(hWnd, NULL, FALSE);
               sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
               SetWindowText(hWnd, Texte);
               break;
  
  	case VK_UP :
      DeplacerLaCamera(1.0f, Theta);
      InvalidateRect(hWnd, NULL, FALSE);
      break;
  
  	case VK_DOWN :
      DeplacerLaCamera(-1.0f, Theta);
      InvalidateRect(hWnd, NULL, FALSE);
      break;
  
  	case VK_LEFT :
      Theta += 1.0f;
      DeplacerLaCamera(0.0f, Theta);
      InvalidateRect(hWnd, NULL, FALSE);
      break;
  
  	case VK_RIGHT :
      Theta -= 1.0f;
      DeplacerLaCamera(0.0f, Theta);
      InvalidateRect(hWnd, NULL, FALSE);
      break;
  }
}

void EvMouseMove(int x, int y, int & xInit, int & yInit,
                 bool ButtonLeftDown, bool ButtonRightDown)
{
  static int DeltaX;
  static int DeltaY;

  if(ButtonLeftDown) // Le bouton gauche est en bas
  {
    DeltaX = xInit - x;
    DeltaY = yInit - y;
    if(abs(DeltaY) > abs(DeltaX))
    {
      if(DeltaY > 0)
      {
        xRot++;
        if(xRot >= 360.0) xRot = 0.0;
      }
      else
      {
        xRot--;
        if(xRot <= -360.0) xRot = 0.0;
      }
    }
    else
    {
      if(DeltaX > 0)
      {
        yRot++;
        if(yRot >= 360.0) yRot = 0.0;
      }
      else
      {
        yRot--;
        if(yRot <= -360.0) yRot = 0.0;
      }
    }

    xInit = x;
    yInit = y;
    InvalidateRect(hWnd, NULL, FALSE);
  }

  if(ButtonRightDown)
  {
    GLfloat d = 0.0f;
    DeltaX = xInit - x;
    DeltaY = yInit - y;

    if(abs(DeltaY) > abs(DeltaX))
    {
      // Si on a déplacé la souris vers le haut
      if(DeltaY > 0)
        d = 1.0f;
      // Si on a déplacé la souris vers le bas
      else
        d = -1.0f;
    }
    else
    {
      // Si on a déplacé la souris à droite
      if (DeltaX > 0)
        Theta += 1.0f;
      // Si on a déplacé la souris à gauche
      else
        Theta -= 1.0f;
    }

    DeplacerLaCamera(d, Theta);
    xInit = x;
    yInit = y;
    InvalidateRect(hWnd, NULL, FALSE);
  }
}    

void Animation(int Id)
{
  // Pour faire tourner la lumière
  if(Id == ID_TIMER)
  {
    RotationLumiere++;
    if(RotationLumiere >= 360.0) RotationLumiere = 0.0;
    InvalidateRect(hWnd, NULL, FALSE);
  }
}

void DeplacerLaCamera(GLfloat d, GLfloat Theta)
{
  static GLfloat fRadius = 50.0f;
  GLfloat xDelta, zDelta;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  // Charger la matrice de visualisation identité

  xDelta = d*cos(Theta*M_PI/180.0);
  zDelta = -d*sin(Theta*M_PI/180.0);
  xPos += xDelta;
  zPos += zDelta;

  gluLookAt(xPos,
            yPos,
            zPos,   // Position de la caméra
            xPos + fRadius*COS(Theta),
            yPos,
            zPos - fRadius*SIN(Theta),
            0.0f, 1.0f, 0.0f);  // Axe dirigé vers le haut
}
