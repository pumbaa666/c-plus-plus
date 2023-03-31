// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "global.h"
#include "geometrie.h"
#include "evenements.h"

int xOld;
int yOld;

    // Fonction de rappel pour le timer.
// Cette fonction n'est pas appelée si spinMode est false.
void Afficher(int valeur)
{
  if(valeur == 1)
  {
    yRot++;
    if(yRot >= 360.0) yRot = 0.0;
    glutPostRedisplay();
    if(spinMode) glutTimerFunc(20, Afficher, 1);
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Effectuer les rotations
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    DessinerLesAxes();
    DessinerLaScene();                 // Afficher
  glPopMatrix();   // Récupérer la matrice de visualisation
  glutSwapBuffers();

  char Texte[80];
  sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
  glutSetWindowTitle(Texte);
}

void myReshape(int w, int h)
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
  if(button == GLUT_LEFT_BUTTON)
    if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
    {
      xOld = x;
      yOld = y;
      ButtonLeftDown = true;
    }
    else                        // Le bouton gauche a été relâché
    {
      ButtonLeftDown = false;
    }

  if(button == GLUT_RIGHT_BUTTON)
    if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
    {
      xOld = x;
      yOld = y;
      ButtonRightDown = true;
    }
    else                        // Le bouton gauche a été relâché
    {
      ButtonRightDown = false;
    }
}

void DeplacerSouris(int x, int y) // La souris s'est déplacée
{
  static int DeltaX;
  static int DeltaY;

  if(ButtonLeftDown) // Le bouton gauche est en bas
  {
    DeltaX = xOld - x;
    DeltaY = yOld - y;
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

    xOld = x;
    yOld = y;
    glutPostRedisplay();
  }

  if(ButtonRightDown)
  {
    GLfloat d = 0.0f;
    DeltaX = xOld - x;
    DeltaY = yOld - y;

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
    xOld = x;
    yOld = y;
    glutPostRedisplay();
  }
}

void Key(unsigned char key, int /*x*/, int /*y*/ )
{
    key = (unsigned char) tolower(key);
    switch(key)
    {
      case ' ' : spinMode = !spinMode;
                 // Lancer le timer si on est en mode animé.
                 if(spinMode) glutTimerFunc(20, Afficher, 1);
                 break;
      case '1' : Mode ^= 0x1; if(!spinMode) display();
                 break;
      case '2' : Mode ^= 0x2; if(!spinMode) display();
                 break;
      case '3' : Mode ^= 0x4; if(!spinMode) display();
                 break;
      case '4' : Mode ^= 0x8; if(!spinMode) display();
                 break;
      case 'w' : if(FullScreen)
                 {
                   glutReshapeWindow(500, 500);
                   glutPositionWindow(30, 30);
                 }
                 else
                   glutFullScreen();
                 FullScreen = !FullScreen;
                 break;
    }
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
  display();
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

