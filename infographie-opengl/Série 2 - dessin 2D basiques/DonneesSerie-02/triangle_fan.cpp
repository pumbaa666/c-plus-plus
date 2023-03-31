// Fichier Triangle_Fan.CPP
#include <GL\glut.h>
#include "triangle_fan.h"

void DessinerLesTriangle_fan(GLenum mode)
{
    glShadeModel(mode);

    glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex2f(5.0f,-20.0f);
		glVertex2f(15.0f,-10.0f);
		glVertex2f(7.0f,-15.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex2f(-5.0f,-10.0f);

		glColor3f(0.0f,1.0f,0.5f);
		glVertex2f(-15.0f,10.0f);

		glColor3f(0.0f,0.0f,0.5f);
		glVertex2f(-7.0f,5.0f);
    glEnd();
}

