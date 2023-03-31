// Fichier Axes.cpp

#include <GL\glut.h>
#include "global.h"

void DessinerLesAxes()
{
    glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);

		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,30.0f,0.0f);

		glVertex3f(0.0f,30.0f,0.0f);
		glVertex3f(-5.0f,25.0f,0.0f);

		glVertex3f(0.0f,30.0f,0.0f);
		glVertex3f(5.0f,25.0f,0.0f);


		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(30.0f,0.0f,0.0f);

		glVertex3f(30.0f,0.0f,0.0f);
		glVertex3f(25.0f,5.0f,0.0f);

		glVertex3f(30.0f,0.0f,0.0f);
		glVertex3f(25.0f,-5.0f,0.0f);
    glEnd();
}

