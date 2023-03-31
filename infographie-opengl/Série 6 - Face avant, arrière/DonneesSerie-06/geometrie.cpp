// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "global.h"

void DessinerLaScene()
{
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glPushMatrix();
        glScalef(20.0, 20.0, 20.0);
        glColor3f(1.0, 1.0, 1.0);
        DessinerLesAxes();
    glPopMatrix();
    DessinerLeCube();
}

void DessinerLeCube()
{
    /* On ne voit que les faces exterieurs */
    //glFrontFace(GL_CW);

    /* On voit les faces interieurs */
    //glFrontFace(GL_CCW);

    /* On voit tout */
    //glFrontFace(GL_CW);

    /* On voit tout */
    glFrontFace(GL_CCW);

    glBegin(GL_QUAD_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(10.0, -10.0, 10.0); // 1
        glVertex3f(10.0, 10.0, 10.0); // 2
        glVertex3f(10.0, -10.0, -10.0); // 3
        glVertex3f(10.0, 10.0, -10.0); // 4

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-10.0, -10.0, -10.0); // 5
        glVertex3f(-10.0, 10.0, -10.0); // 6

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-10.0, -10.0, 10.0); // 7
        glVertex3f(-10.0, 10.0, 10.0); // 8

        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(10.0, -10.0, 10.0); // 1, 9
        glVertex3f(10.0, 10.0, 10.0); // 2, 10
    glEnd();
}

void DessinerLesAxes()
{
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
}
