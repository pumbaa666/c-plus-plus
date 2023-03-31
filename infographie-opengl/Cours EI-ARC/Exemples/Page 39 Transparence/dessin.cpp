// Fichier Dessin.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "dessin.h"

void drawFloor()
{
   GLfloat alpha = 0.75f; // Ne change rien dans cet exemle.
		glColor4f(0.5f, 0.5f, 0.5f, alpha);
		glBegin(GL_QUADS);
			  glVertex3f(-4.0,  4.0, 0.0);
			  glVertex3f( 4.0,  4.0, 0.0);
			  glVertex3f( 4.0, -4.0, 0.0);
			  glVertex3f(-4.0, -4.0, 0.0);
		glEnd();
}

