// Fichier Quad_Strip.CPP

#include <GL\glut.h>
#include "quad_strip.h"

void DessinerLesQuad_strip(GLenum mode)
{
    glShadeModel(mode);

    glBegin(GL_QUAD_STRIP);
		glColor3f(0.0f,0.0f,0.0f);
		glVertex2f(5.0f,-20.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex2f(15.0f,-15.0f);

		glColor3f(0.0f,1.0f,1.0f);
		glVertex2f(0.0f,0.0f);

		glColor3f(0.0f,1.0f,0.0f);
		glVertex2f(15.0f,-5.0f);

		glColor3f(0.0f,0.0f,1.0f);
		glVertex2f(-15.0f,-5.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex2f(-5.0f,5.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex2f(-25.0f,15.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex2f(-10.0f,15.0f);
    glEnd();
}

