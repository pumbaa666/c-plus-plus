// Fichier Polygone.CPP
#include <GL\glut.h>
#include "polygone.h"

void DessinerLePolygone(GLenum mode)
{
    glShadeModel(mode);

    glBegin(GL_POLYGON);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex2f(15.0f,15.0f);

		glColor3f(0.0f,1.0f,0.0f);
		glVertex2f(-15.0f,15.0f);

		glColor3f(1.0f,0.0f,1.0f);
		glVertex2f(-25.0f,-5.0f);

		glColor3f(1.0f,1.0f,.0f);
		glVertex2f(-15.0f,15.0f);

		glColor3f(0.0f,0.0f,0.0f);
		glVertex2f(5.0f,0.0f);

		glColor3f(1.0f,0.5f,0.0f);
		glVertex2f(0.0f,-15.0f);

    glEnd();
}

