// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include "global.h"
#include "geometrie.h"
#include "evenements.h"

void Animate()
{
  if(spinMode)
  {
    yRot++;
    if(yRot >= 360.0) yRot = 0.0;
    glutPostRedisplay();
    Sleep(10);
  }
}

void Display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Effectuer les rotations
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    DessinerLaScene();
  glPopMatrix();   // Récupérer la matrice de visualisation
  glutSwapBuffers();
}

void MyReshape(int w, int h)
{
  if (h == 0) h = 1;
  if (w == 0) w = 1;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  // Charger la matrice de projection identité

  // Calcul du rapport d'aspect de la fenêtre
  RapportAspect = (GLfloat)w / (GLfloat)h;
  gluPerspective(AngleOuverture, RapportAspect, PlanAvant, PlanArriere);

  DeplacerLaCamera(0.0f, Theta);
}

void Souris(int button, int state, int /*x*/, int /*y*/)
{
  if(button == GLUT_LEFT_BUTTON)
    if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
    {
      ButtonLeftDown = true;
    }
    else                        // Le bouton gauche a été relâché
    {
      ButtonLeftDown = false;
    }

  if(button == GLUT_RIGHT_BUTTON)
    if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
    {
      ButtonRightDown = true;
    }
    else                        // Le bouton gauche a été relâché
    {
      ButtonRightDown = false;
    }
}

void DeplacerSouris(int x, int y) // La souris s'est déplacée
{
  static int yOld = 0;
  static int xOld = 0;
  if(ButtonLeftDown) // Le bouton gauche est en bas
  {
    int DeltaAngleX;
    DeltaAngleX = yOld - y;
    if(DeltaAngleX > 0)
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

  if(ButtonRightDown) // Le bouton gauche est en bas
  {
    int DeltaAngleY;
    DeltaAngleY = xOld - x;
    if(DeltaAngleY > 0)
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
  xOld = x;
  yOld = y;
  Display();
}

void Key(unsigned char key, int /*x*/, int /*y*/ )
{
    static float delta = 1.0;
    static float deltaPt = 0.1;
    static int NumPt = 0;
    static int NumKn = 0;
    static bool vision = true;
    key = (unsigned char) tolower(key);
    switch(key)
    {
      case ' ' : spinMode = !spinMode;
                 break;
      case '1' : NumPt = 0; NumKn = 0;
                 break;
      case '2' : NumPt = 1; NumKn = 1;
                 break;
      case '3' : NumPt = 2; NumKn = 2;
                 break;
      case '4' : NumPt = 3; NumKn = 3;
                 break;
      case '5' : NumPt = 4; NumKn = 4;
                 break;
      case '6' : NumPt = 5; NumKn = 5;
                 break;
      case '7' : NumPt = 6; NumKn = 6;
                 break;
      case '8' : NumPt = 6; NumKn = 7;
                 break;
      case '9' : NumPt = 6; NumKn = 8;
                 break;
      case '0' : NumPt = 6; NumKn = 9;
                 break;
      case '+' : delta = -delta; deltaPt = -deltaPt;
                 break;
      case 'x' : ctrlPoints[NumPt][0] += deltaPt; if(!spinMode) Display();
                 break;
      case 'y' : ctrlPoints[NumPt][1] += deltaPt; if(!spinMode) Display();
                 break;
      case 'z' : ctrlPoints[NumPt][2] += deltaPt; if(!spinMode) Display();
                 break;
      case 'w' : ctrlPoints[NumPt][3] += deltaPt; if(!spinMode) Display();
                 break;
      case 'k' : Knots[NumKn] += delta;
                 if(delta > 0 && NumKn < NbKnots-1)
                 {
                   if(Knots[NumKn] > Knots[NumKn+1])
                     Knots[NumKn] = Knots[NumKn+1];
                 }
                 else if(delta < 0 && NumKn > 0)
                 {
                   if(Knots[NumKn] < Knots[NumKn-1])
                     Knots[NumKn] = Knots[NumKn-1];
                 }
                 Display();
                 break;
      case 'v' : vision = !vision;
                 break;
/*
      case 'w' : if(FullScreen)
                 {
                   glutReshapeWindow(500, 500);
                   glutPositionWindow(30, 30);
                 }
                 else
                 {
                   glutFullScreen();
                 }
                 FullScreen = !FullScreen;
                 break;
*/
    }
  char Texte[200];
//  sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %o", Mode);

  if(vision)
  {
    sprintf(Texte, "N° : (x, y, z, w) = %d : (%.2f, %.2f, %.2f, %.2f)", NumPt+1,
                                               ctrlPoints[NumPt][0],
                                               ctrlPoints[NumPt][1],
                                               ctrlPoints[NumPt][2],
                                               ctrlPoints[NumPt][3]);
  }
  else
  {
    sprintf(Texte,
    "%d : (%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f) Knots",
    NumKn+1,
    Knots[0], Knots[1], Knots[2], Knots[3], Knots[4],
    Knots[5], Knots[6], Knots[7], Knots[8], Knots[9]);
  }
  glutSetWindowTitle(Texte);
}

void ToucheSpecial(int key, int /*x*/, int /*y*/)
{
  GLfloat d = 0.0f;
  // Si on appuie sur la touche <flèche en haut>
  if(key == GLUT_KEY_UP)
    d = 1.0f;
  // Si on appuie sur la touche <flèche en bas>
  else if (key == GLUT_KEY_DOWN)
    d = -1.0f;
  else if (key == GLUT_KEY_LEFT)
    Theta += 1.0f;
  else if (key == GLUT_KEY_RIGHT)
    Theta -= 1.0f;

  DeplacerLaCamera(d, Theta);
  Display();
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
            2.0f,
            zPos,   // Position de la caméra
            xPos + fRadius*cos(Theta*M_PI/180.0),
            2.0f,
            zPos - fRadius*sin(Theta*M_PI/180.0),
            0.0f, 1.0f, 0.0f);  // Axe dirigé vers le haut
}

