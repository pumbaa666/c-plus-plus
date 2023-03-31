// Loïc Correvon
// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "global.h"
#include "geometrie.h"
#include "evenements.h"

#define COS(x) cos((x) *  M_PI/180.0f)
#define SIN(x) sin((x) *  M_PI/180.0f)

int xInit;  // Variables globales au niveau du fichier
int yInit;

// Fonction de rappel pour le timer.
// Cette fonction n'est pas appelée si spinMode est false.
void evTimer(int valeur)
{
  if(valeur == 1)
  {
    yRot++;
    glutPostRedisplay();

    // Timer :
    // DELTA_TIME ms avant de faire appel à la fonction de rappel
    // Afficher : fonction de rappel ( void evTimer(int valeur); )
    // 1 : valeur associée à la minuterie
    if(spinMode) glutTimerFunc(DELTA_TIME, evTimer, 1);
  }
}

void Display()
{
  static GLfloat xX, yX, zX;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
    glPushMatrix();
      glScalef(5.0f, 5.0f, 5.0f);
      DessinerLesAxes();
    glPopMatrix();
      glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        xX = COS(yRot);
        yX = 0.0f;
        zX = SIN(yRot);
  /*      xX = 1.0f;
        yX = 0.0f;
        zX = 0.0f;*/
      glRotatef(xRot, xX, yX, zX); // Effectuer les rotations
    glPushMatrix();
      glScalef(5.0f, 5.0f, 5.0f);
      DessinerLesAxes();
    glPopMatrix();
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
      deltaAngle = 0.0f;
    }

  if(button == GLUT_RIGHT_BUTTON)
    if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
    {
      ButtonRightDown = true;
    }
    else                        // Le bouton gauche a été relâché
    {
      ButtonRightDown = false;
      deltaAngle = 0.0f;
    }
}

void DeplacerSouris(int x, int y) // La souris s'est déplacée
{
  static GLfloat angle = 0.0f;
  if(ButtonLeftDown) // Le bouton gauche est en bas
  {
    int DeltaAngleX;
    DeltaAngleX = yInit - y;

    if(DeltaAngleX > 0)
    {
      if(AxeRotation == 'n')
      {
        xRot++;
        if(xRot >= 360.0f) xRot = 0.0f;
      }
      else
      {
        deltaAngle = 1.0f;
      }
    }
    else
      if(AxeRotation == 'n')
      {
        xRot--;
        if(xRot <= -360.0f) xRot = 0.0f;
      }
      else
      {
        deltaAngle = -1.0f;
      }
  }

  if(ButtonRightDown && AxeRotation == 'n') // Le bouton gauche est en bas
  {
    int DeltaAngleY;
    DeltaAngleY = xInit - x;
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
  xInit = x;
  yInit = y;
  glutPostRedisplay();
}

void Key(unsigned char key, int /*x*/, int /*y*/ )
{
  static char Texte[80];
  sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %x", Mode);
    key = (unsigned char) tolower(key);
    switch(key)
    {
      case ' ' : spinMode = !spinMode;
                 if(spinMode) evTimer(1);
                 break;
      case '1' : Mode ^= 0x1; if(!spinMode) glutPostRedisplay();
         sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %x", Mode);
                 break;
      case '2' : Mode ^= 0x2; if(!spinMode) glutPostRedisplay();
         sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %x", Mode);
                 break;
      case '3' : Mode ^= 0x4; if(!spinMode) glutPostRedisplay();
         sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %x", Mode);
                 break;
      case '4' : Mode ^= 0x8; if(!spinMode) glutPostRedisplay();
         sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %x", Mode);
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
            yPos,
            zPos,   // Position de la caméra
            xPos + fRadius*cos(Theta*M_PI/180.0),
            yPos,
            zPos - fRadius*sin(Theta*M_PI/180.0),
            0.0f, 1.0f, 0.0f);  // Axe dirigé vers le haut
}

