// Fichier Quads.CPP
#include <GL\glut.h>
#include "quads.h"

void DessinerLesQuads(GLenum mode)
{
    glShadeModel(mode);

    glBegin(GL_QUADS);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex2f(-15.0f,-5.0f);
		glVertex2f(-5.0f,5.0f);
		glVertex2f(-10.0f,15.0f);
		glVertex2f(-25.0f,15.0f);

		glColor3f(0.0f,0.0f,0.0f);
		glVertex2f(5.0f,-20.0f);
		glVertex2f(15.0f,-15.0f);
		glVertex2f(15.0f,-5.0f);
		glVertex2f(0.0f,0.0f);

    glEnd();
}

