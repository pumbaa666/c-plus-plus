// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "global.h"
#include "geometrie.h"
#include "evenements.h"

int xInit;  // Variables globales au niveau du fichier
int yInit;

void Animate()
{
    if(spinMode)
    {
        RotationLumiere++;
        if(RotationLumiere > 360)
            RotationLumiere = 0;
        glutPostRedisplay();
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

void Souris(int button, int state, int x, int y)
{
  xInit = x;
  yInit = y;
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
  if(ButtonLeftDown) // Le bouton gauche est en bas
  {
    int DeltaAngleX;
    DeltaAngleX = yInit - y;
    if(DeltaAngleX > 0)
    {
      xRot+=2;
      if(xRot >= 360.0) xRot = 0.0;
    }
    else
    {
      xRot-=2;
      if(xRot <= -360.0) xRot = 0.0;
    }
  }

  if(ButtonRightDown) // Le bouton gauche est en bas
  {
    int DeltaAngleY;
    DeltaAngleY = xInit - x;
    if(DeltaAngleY > 0)
    {
      yRot+=2;
      if(yRot >= 360.0) yRot = 0.0;
    }
    else
    {
      yRot-=2;
      if(yRot <= -360.0) yRot = 0.0;
    }
  }
  xInit = x;
  yInit = y;
  glutPostRedisplay();
}

void Key(unsigned char key, int /*x*/, int /*y*/ )
{
    key = (unsigned char) tolower(key);
    switch(key)
    {
      case ' ' : spinMode = !spinMode;
                 break;
      case '1' : Mode ^= 0x1; glutPostRedisplay();
                 break;
      case '2' : Mode ^= 0x2; glutPostRedisplay();
                 break;
      case '3' : Mode ^= 0x4; glutPostRedisplay();
                 break;
      case '4' : Mode ^= 0x8; glutPostRedisplay();
                 break;
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
      case 'f' : alpha += 0.1;
                 if(alpha >= 1)
                    alpha = 1;
                 glutPostRedisplay();
                 break;
      case 'g' : alpha -= 0.1;
                 if(alpha <= 0)
                    alpha = 0;
                 glutPostRedisplay();
                 break;
    }

  char Texte[80];
  sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
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
  glutPostRedisplay();
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

