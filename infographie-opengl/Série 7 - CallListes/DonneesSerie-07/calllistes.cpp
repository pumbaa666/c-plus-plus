// Fichier CallListes.cpp

#include <gl\glut.h>
#include <math.h>
#include <stdlib.h>
#include "global.h"
#include "calllistes.h"

void Make_CallListes()
{
    axes = glGenLists(2);
    cone = axes+1;

	glNewList(axes, GL_COMPILE);
		glColor3f(1.0f,1.0f,1.0f);
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
	glEndList();

	glNewList(cone, GL_COMPILE);
        float angle = 0.0;
        int i;
        /* tour */
        angle = 0.0;
		glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f,0.0f,2.0f);
            for(i = 0; i < 8; i++)
            {
                //glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
                if(i % 2 == 0)
                    glColor3f(1.0f,0.0f,0.0f);
                else
                    glColor3f(0.0f,1.0f,0.0f);
                angle += 2*M_PI/8.0;

                glVertex3f(cos(angle),sin(angle),0.0f);
            }
        glEnd();
        /* base */
        glFrontFace(GL_CW);
		glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f,0.0f,0.0f);
            for(i = 0; i < 17; i++)
            {
                //glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
                if(i % 2 == 0)
                    glColor3f(1.0f,0.0f,0.0f);
                else
                    glColor3f(0.0f,1.0f,0.0f);
                angle += 2*M_PI/16.0;

                glVertex3f(cos(angle),sin(angle),0.0f);
            }
		glEnd();
        glFrontFace(GL_CCW);

    glEndList();
}

