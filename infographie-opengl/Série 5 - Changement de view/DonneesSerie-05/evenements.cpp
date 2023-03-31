// Fichier Evenements.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"
#include <iostream.h>

void PositionnerCamera(GLfloat x, GLfloat y, GLfloat z)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();         // Charger la matrice identit�
    gluLookAt(  x,   y,   z,  // Position de la cam�ra          gluLookAt DOIT ETRE APPELE EN 1ER DANS UN PROG, avant tout autre gluPerspective, etc
              0.0, 0.0, 0.0,  // Point de vis�e
              0.0, 1.0, 0.0); // Axe dirig� vers le haut

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Efface le fond | nettoye le Depth Buffer
    DessinerLaScene();
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
    PositionnerCamera(0.0, yCamera, 10.0);
}

void Mouse(int button, int state, int x, int y)
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
            ButtonRightDown = false;
    }
}

void Motion(int x, int y) // La souris s'est d�plac�e
{
    //char text[80];
    //cout << text;

    if(ButtonLeftDown)
    {
        //sprintf(text, "\nyRot = %.2f", yRot);
        if(x > lastX)
            yRot += 5;
        else if(x < lastX)
            yRot -= 5;
        if(yRot < -360)
            yRot = 360;
        else if(yRot > 360)
            yRot = -360;
        lastX = x;
    }
    else
    {
        //sprintf(text, "\nAngle = %.2f", yCamera);
        if(y > lastY && AngleOuverture < 179)
            AngleOuverture++;
        else if(y < lastY && AngleOuverture > 1)
            AngleOuverture--;
        lastY = y;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();  // Charger la matrice de projection identit�
        gluPerspective(AngleOuverture, RapportAspect, PlanAvant, PlanArriere);
        glMatrixMode(GL_MODELVIEW);
    }
    glutPostRedisplay();
}

