//Fichier Geometrie.cpp

#include <GL\glut.h>
#include <math.h>
#include "global.h"
#include "geometrie.h"

void DessinerLaScene()
{
    ModeDeDessin(Mode);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    DessinerLeSol();

    PositionLumiere(0.0, 5.0, 5.0);

    glPushMatrix();
        glTranslatef(xSphere1, fRadius, 0.0);
        glRotatef(-180.0/M_PI*rotationSphere, 0.0, 0.0, 1.0);
        DessinerSphere1();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5.0, fRadius, zSphere2);
        glRotatef(180.0/M_PI*rotationSphere, 1.0, 0.0, 0.0);
        DessinerSphere2();
    glPopMatrix();
}

void PositionLumiere(float x, float y, float z)
{
    static GLfloat position[]= {x, y, z, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glPushMatrix();
        glTranslatef(x, y, z);
        DessinerLampe();
    glPopMatrix();
}

void DessinerSphere1()
{
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(fRadius, nbSommetSphere, nbSommetSphere);
}

void DessinerSphere2()
{
    glColor3f(0.0, 1.0, 0.0);
    glutSolidSphere(fRadius, nbSommetSphere, nbSommetSphere);
}

void DessinerLampe()
{
    glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 0.0);
        glutSolidSphere(2, 20, 20);
    glPopAttrib();
}


void DessinerLesAxes()
{
    glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.8f, -0.05f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.8f, 0.05f, 0.0f);

            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.05f, 0.8f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.05f, 0.8f, 0.0f);

            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.05f, 0.0f, 0.8f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.05f, 0.0f, 0.8f);
        glEnd();
    glPopAttrib();
}

void DessinerLeSol()
{
    int r,c;
    int nStep = 3;

    glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        for(r = -100; r  <= 100; r += nStep)
        {
            glVertex3f((float)r, 0.0f, -100.0f);
            glVertex3f((float)r, 0.0f, 100.0f);
        }

        for(c = -100; c <= 100; c += nStep)
        {
            glVertex3f(100.0f, 0.0f, (float)c);
            glVertex3f(-100.0f, 0.0f, (float)c);
        }
        glEnd();
    glPopAttrib();
}


void ModeDeDessin(int mask)
{
    // Turn culling on if flag is set
    if(mask & bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    // Enable depth testing if flag is set
    if(mask & bDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    // Draw back side as a polygon only, if flag is set
    if(mask & bOutline)
        glPolygonMode(GL_BACK,GL_LINE);
    else
        glPolygonMode(GL_BACK,GL_FILL);

    if(mask & bShadeModel)
        glShadeModel(GL_SMOOTH);  // Interpolation de la couleur entre les différents sommets
    else
        glShadeModel(GL_FLAT);    // La couleur du polygone est la couleur du dernier sommet (qui est aussi le premier)
}
