// Fichier Evenements.cpp

#include <windows.h> // Si on utilise la fonction Sleep(20)
#include <GL\glut.h>
#include <ctype.h>
#include "evenements.h"
#include "geometrie.h"
#include "global.h"

int xInit;  // Variables globales au niveau du fichier
int yInit;
bool isAnimate = false;
bool isFullWindow = false;

// Fonction de rappel pour Idle Function.
// Cette fonction est appel�e m�me si spinMode est false.
void Animate()
{
    if(isAnimate == true)
    {
        yRot++;
        glutPostRedisplay();
        Sleep(20);
    }
}

// Fonction de rappel pour le timer.
// Cette fonction n'est pas appel�e si spinMode est false.
void evTimer(int valeur)
{
    if(valeur == 1)
    {
        xRot++;
        if(xRot >= 360.0)
            xRot = 0.0;
        glutPostRedisplay();
        if(spinMode)
            glutTimerFunc(DELTA_TIME, evTimer, 1);
    }
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
        DessinerLaScene();                 // Afficher
    glPopMatrix();   // R�cup�rer la matrice de visualisation
    glutSwapBuffers();
}

void Reshape(int w, int h)
{
    if (h == 0)
        h = 1;
    if (w == 0)
        w = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // Charger la matrice de projection identit�

    // Calcul du rapport d'aspect de la fen�tre
    RapportAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(AngleOuverture, RapportAspect, PlanAvant, PlanArriere);

    PositionnerCamera(0.0, 2.0, 5.0);
}

void PositionnerCamera(GLfloat x, GLfloat y, GLfloat z)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  // Charger la matrice de visualisation identit�
  // D�placer le point de vue (la cam�ra)
  // La position de la cam�ra est en (x, y, z)
  // La direction de vis�e de la cam�ra est le point (0, 0, 0)
  // L'axe dirig� vers le haut est le vecteur de composantes (0, 1, 0)
  gluLookAt(x, y, z,   // Position de la cam�ra
            0.0, 0.0, 0.0,   // Direction de vis�e
            0.0, 1.0, 0.0);  // Axe dirig� vers le haut
}

void Mouse(int button, int state, int x, int y)
{
    xInit = x;
    yInit = y;
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)      // Le bouton gauche a �t� press�
            ButtonLeftDown = true;
        else                        // Le bouton gauche a �t� rel�ch�
            ButtonLeftDown = false;
    }

    if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)      // Le bouton gauche a �t� press�
            ButtonRightDown = true;
        else                        // Le bouton gauche a �t� rel�ch�
            ButtonRightDown = false;
    }
}

void Motion(int x, int y) // La souris s'est d�plac�e
{
    if(x > xInit)
        xRot +=2;
    else if(x < xInit)
        xRot-=2;
    xInit = x;
    if(xRot >= 360)
        xRot -= 360;
    if(xRot <= -360)
        xRot += 360;

    if(y > yInit)
        yRot+=2;
    else if(y < yInit)
        yRot-=2;
    yInit = y;
    if(yRot >= 360)
        yRot -= 360;
    if(yRot <= -360)
        yRot += 360;

    glutPostRedisplay();
}

void Keyboard(unsigned char key, int, int)
{
    switch(key)
    {
        case '1': Mode ^= bCull; break;
        case '2': Mode ^= bDepth; break;
        case '3': Mode ^= bOutline; break;
        case '4': Mode ^= bShadeModel; break;
        case 'w' :  if(isFullWindow == false)
                    {
                        glutFullScreen();
                        isFullWindow = true;
                    }
                    else
                    {
                        glutReshapeWindow(500, 500);
                        glutPositionWindow(30, 30);
                        isFullWindow = false;
                    }
                    break;
        case ' ':   if(isAnimate == false)
                    {
                        isAnimate = true;
                        Animate();
                    }
                    else
                        isAnimate = false;
                    break;
        case 't':   isAnimate = !isAnimate; break;
    }
    glutPostRedisplay();
}

