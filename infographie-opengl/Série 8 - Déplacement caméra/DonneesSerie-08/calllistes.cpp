// Fichier CallListes.cpp

#include <GL\glut.h>
#include "global.h"
#include "calllistes.h"

void Make_CallListes()
{
    axes = glGenLists(5);
    murs = axes + 1;
    toit = murs + 1;
    maison = toit + 1;
    sol = maison + 1;

    // Dessin des axes
    glNewList(axes, GL_COMPILE);
        glBegin(GL_LINES);
            // Axe Ox
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.8f, -0.05f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.8f, 0.05f, 0.0f);

            // Axe Oy
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.05f, 0.8f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.05f, 0.8f, 0.0f);

            // Axe Oz
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.05f, 0.0f, 0.8f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.05f, 0.0f, 0.8f);
        glEnd();
    glEndList();

    // Dessin des 4 murs
    glNewList(murs, GL_COMPILE);
        glFrontFace(GL_CW);
        glBegin(GL_TRIANGLE_STRIP);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 4.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 4.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 0.8f);
        glVertex3f(10.0f, 4.0f, 5.0f);
        glVertex3f(10.0f, 0.0f, 5.0f);

        glColor3f(0.0f, 0.0f, 0.6f);
        glVertex3f(0.0f, 4.0f, 5.0f);
        glVertex3f(0.0f, 0.0f, 5.0f);

        glColor3f(0.0f, 0.0f, 0.4f);
        glVertex3f(0.0f, 4.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glEnd();
        glFrontFace(GL_CW);
    glEndList();

    // Dessin du toit
    glNewList(toit, GL_COMPILE);
        glBegin(GL_TRIANGLE_STRIP);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, 6.0f, 2.5f);
            glVertex3f(-1.0f, 3.2f, -1.0f);
            glVertex3f(11.0f, 6.0f, 2.5f);
            glVertex3f(11.0f, 3.2f, -1.0f);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
            glColor3f(0.7f, 0.0f, 0.0f);
            glVertex3f(-1.0f, 3.2f, 6.0f);
            glVertex3f(-1.0f, 6.0f, 2.5f);
            glVertex3f(11.0f, 3.2f, 6.0f);
            glVertex3f(11.0f, 6.0f, 2.5f);
        glEnd();
    glEndList();

    // Dessin de la maison (murs + toit)
    glNewList(maison, GL_COMPILE);
        glCallList(murs);
        glCallList(toit);
    glEndList();

    // Dessin du sol
    glNewList(sol, GL_COMPILE);
        glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        GLfloat i;
        for(i = 0.0; i < 200.0; i+=3.0)
        {
            glVertex3f(i, 0.0, 0.0);
            glVertex3f(i, 0.0, 200.0);
        }
        for(i = 0.0; i < 200.0; i+=3.0)
        {
            glVertex3f(0.0, 0.0, i);
            glVertex3f(200.0, 0.0, i);
        }

        glEnd();
    glEndList();
}
