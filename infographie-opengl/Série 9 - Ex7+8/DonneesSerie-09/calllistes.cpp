// Fichier CallListes.cpp

#include <GL\glut.h>
#include "global.h"
#include "calllistes.h"
#include <math.h>

void Make_CallListes()
{
    axes = glGenLists(6);
    murs = axes + 1;
    toit = axes + 2;
    maison = axes + 3;
    sol = axes + 4;
    cone = axes + 5;

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

        glColor3f(0.7f, 0.7f, 0.7f);
        glVertex3f(0.0f, 4.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 4.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);

        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex3f(10.0f, 4.0f, 5.0f);
        glVertex3f(10.0f, 0.0f, 5.0f);

        glColor3f(0.4f, 0.4f, 0.4f);
        glVertex3f(0.0f, 4.0f, 5.0f);
        glVertex3f(0.0f, 0.0f, 5.0f);

        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f(0.0f, 4.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glEnd();
        glFrontFace(GL_CW);
    glEndList();

    // Dessin du toit
    glNewList(toit, GL_COMPILE);
        glBegin(GL_TRIANGLE_STRIP);
            glColor3f(1.0f, 0.0f, 0.0f);
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
        glTranslatef(-5.0, 0.0, -2.5);
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

    glNewList(cone, GL_COMPILE);
        float angle = 0.0;
        int j;
        /* tour */
        angle = 0.0;
		glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(0.0f,0.0f,2.0f);
            for(j = 0; j < 17; j++)
            {
                glColor3f(j/16.0, j/16.0, j/16.0);
                angle += 2*M_PI/16.0;

                glVertex3f(cos(angle),sin(angle),0.0f);
            }
        glEnd();

        /* base */
        glFrontFace(GL_CW);
		glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f,0.0f,0.0f);
            for(j = 0; j < 17; j++)
            {
                glColor3f(j/8.0, j/8.0, j/8.0);
                angle += 2*M_PI/16.0;

                glVertex3f(cos(angle),sin(angle),0.0f);
            }
		glEnd();
        glFrontFace(GL_CCW);

    glEndList();
}
