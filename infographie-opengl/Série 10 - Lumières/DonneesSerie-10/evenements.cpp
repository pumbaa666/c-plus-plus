// Fichier Evenements.cpp
#include <GL\glut.h>
#include <windows.h>
#include <stdio.h>
#include "global.h"
#include "geometrie.h"
#include "evenements.h"

void Animate()
{
    a++;
    Sleep(50);
    glutPostRedisplay(); // Uniquement pour GLUT
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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,3,3,
              0,0,0,
              0,1,0);
}

void display()  // Lumi�re mobile
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        DessinerLaScene();
    glPopMatrix();
    glutSwapBuffers();
}

