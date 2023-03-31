// Fichier Evenements.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"

int xInit;  // Variables globales au niveau du fichier
int yInit;

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
        DessinerLaScene();                 // Afficher
    glPopMatrix();   // R�cup�rer la matrice de visualisation
    glutSwapBuffers();
}

void myReshape(int w, int h)
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

    PositionnerCamera(0.0, yCamera, 80.0);
}

void Souris(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)      // Le bouton gauche a �t� press�
        {
            ButtonLeftDown = true;
            xInit = x;
        }
        else                        // Le bouton gauche a �t� rel�ch�
        {
            ButtonLeftDown = false;
            RotationOn = false;
        }
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)      // Le bouton droit a �t� press�
        {
            ButtonRightDown = true;
            yInit = y;
        }
        else                        // Le bouton droit a �t� rel�ch�
        {
            ButtonRightDown = false;
        }
    }
}

void Rotation(int x, int y) // La souris s'est d�plac�e
{
    if(ButtonLeftDown) // Le bouton gauche est en bas
    {
        RotationOn = true;
        if((xInit - x) > 0)
        {
            yRot -= Coef;
            if(yRot <= -360)
                yRot = 0;
        }
        else if((xInit - x) < 0)
        {
            yRot += Coef;
            if(yRot >= 360)
                yRot = 0;
        }
        xInit = x;
        glutPostRedisplay();
    }
    else if(ButtonRightDown)  // Le bouton droit est en bas
    {
        int DeltaAngle;
        DeltaAngle = yInit - y;
        if(DeltaAngle > 0)
        {
            AngleOuverture++;
            if(AngleOuverture >= 180.0)
                AngleOuverture = 179.0;
        }
        else
        {
            AngleOuverture--;
            if(AngleOuverture <= 0.0)
                AngleOuverture = 1.0;
        }
        yInit = y;

        // On modifie la matrice de projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(AngleOuverture, RapportAspect, PlanAvant, PlanArriere);

        // La matrice de visualisation devient la matrice courante
        glMatrixMode(GL_MODELVIEW);
        glutPostRedisplay();
    }
}
