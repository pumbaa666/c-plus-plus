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

// Fonction de rappel pour Idle Function (pas utilisée ici)
void Animate()
{
    if(spinMode)
    {
        yRot++;
        if(yRot >= 360.0)
            yRot = 0.0;
        glutPostRedisplay();
    }
}

// Fonction de rappel pour le timer.
// Cette fonction n'est pas appelée si spinMode est false.
void evTimer(int valeur)
{
  if(valeur == 1)
  {
    yRot++;
    if(yRot >= 360.0) yRot = 0.0;
    glutPostRedisplay();

    // Timer :
    // DELTA_TIME ms avant de faire appel à la fonction de rappel
    // evTimer : fonction de rappel ( void evTimer(int valeur); )
    // 1 : valeur associée à la minuterie
    if(spinMode) glutTimerFunc(DELTA_TIME, evTimer, 1);
  }
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
        glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Effectuer les rotations
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        //DessinerLesAxes();
        DessinerLaScene();                 // Afficher
    glPopMatrix();   // Récupérer la matrice de visualisation
    glutSwapBuffers();
}

void Reshape(int w, int h)
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

void Mouse(int button, int state, int x, int y)
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

void Motion(int x, int y) // La souris s'est déplacée
{
    //if(ButtonLeftDown) // Le bouton gauche est en bas
    //{
        int DeltaAngleX;
        DeltaAngleX = yInit - y;
        if(DeltaAngleX > 0)
        {
            xRot++;
            if(xRot >= 360.0)
                xRot = 0.0;
        }
        else
        {
            xRot--;
            if(xRot <= -360.0)
                xRot = 0.0;
        }
    //}

    //if(ButtonRightDown) // Le bouton gauche est en bas
    //{
        int DeltaAngleY;
        DeltaAngleY = xInit - x;
        if(DeltaAngleY > 0)
        {
            yRot++;
            if(yRot >= 360.0)
                yRot = 0.0;
        }
        else
        {
            yRot--;
            if(yRot <= -360.0)
                yRot = 0.0;
        }
    //}
    xInit = x;
    yInit = y;
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int /*x*/, int /*y*/ )
{
    key = (unsigned char) tolower(key);
    switch(key)
    {
      case ' ' : spinMode = !spinMode;
                 // Lancer le timer si on est en mode animé.
                 // Timer :
                 // DELTA_TIME ms avant de faire appel à la fonction de rappel
                 // evTimer : fonction de rappel ( void evTimer(int valeur); )
                 // 1 : valeur associée à la minuterie
                 if(spinMode) glutTimerFunc(DELTA_TIME, evTimer, 1);
                 break;
      case '1' : Mode ^= bCull; glutPostRedisplay();
                 break;
      case '2' : Mode ^= bDepth; glutPostRedisplay();
                 break;
      case '3' : Mode ^= bOutline; glutPostRedisplay();
                 break;
      case '4' : Mode ^= bShadeModel; glutPostRedisplay();
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

    char Texte[80];
    sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
    glutSetWindowTitle(Texte);
}

void ToucheSpecial(int key, int /*x*/, int /*y*/)
{
    switch(key)
    {
        case 'd': Theta++; DeplacerLaCamera(0.0, Theta); glutSetWindowTitle("gauche"); break;
        case 'e': DeplacerLaCamera(1.0, Theta);  glutSetWindowTitle("haut"); break;
        case 'f': Theta--; DeplacerLaCamera(0.0, Theta);  glutSetWindowTitle("droite"); break;
        case 'g': DeplacerLaCamera(-1.0, Theta);  glutSetWindowTitle("bas"); break;
    }
}

void DeplacerLaCamera(GLfloat d, GLfloat Theta)
{
    GLfloat yPos = 2.0,
            PVx=0,
            PVy=2,
            PVz=0;

    GLfloat fRadius = 50, fRadiusX, fRadiusZ;

    GLfloat ThetaRad = Theta*M_PI/180.0;
    fRadiusX = fRadius*cos(ThetaRad);
    fRadiusZ = -fRadius*sin(ThetaRad);
    PVx = xPos + fRadiusX;
    PVz = zPos + fRadiusZ;

    xPos += d*cos(ThetaRad);
    zPos += -d*sin(ThetaRad);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xPos, yPos, zPos,
              PVx, PVy, PVz,
              0.0, 1.0, 0.0);
    glutPostRedisplay();
}

