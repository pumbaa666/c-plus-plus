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
  glLoadIdentity();  // Charger la matrice de visualisation identité
  // Déplacer le point de vue (la caméra)
  // La position de la caméra est en (x, y, z)
  // La direction de visée de la caméra est le point (0, 0, 0)
  // L'axe dirigé vers le haut est le vecteur de composantes (0, 1, 0)
  gluLookAt(x, y, z,   // Position de la caméra
            0.0, 0.0, 0.0,   // Direction de visée
            0.0, 1.0, 0.0);  // Axe dirigé vers le haut
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
        DessinerLaScene();                 // Afficher
    glPopMatrix();   // Récupérer la matrice de visualisation
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
    glLoadIdentity();  // Charger la matrice de projection identité

    // Calcul du rapport d'aspect de la fenêtre
    RapportAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(AngleOuverture, RapportAspect, PlanAvant, PlanArriere);

    PositionnerCamera(0.0, yCamera, 80.0);
}

void Souris(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
        {
            ButtonLeftDown = true;
            xInit = x;
        }
        else                        // Le bouton gauche a été relâché
        {
            ButtonLeftDown = false;
            RotationOn = false;
        }
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)      // Le bouton droit a été pressé
        {
            ButtonRightDown = true;
            yInit = y;
        }
        else                        // Le bouton droit a été relâché
        {
            ButtonRightDown = false;
        }
    }
}

void Rotation(int x, int y) // La souris s'est déplacée
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
