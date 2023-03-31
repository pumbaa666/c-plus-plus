// Fichier Dessin.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "dessin.h"

void drawFloor()
{
    GLfloat	Blanc[]  = {1.0f, 1.0f, 1.0f, 1.0f};
//		glColor4f(0.5f, 0.5f, 0.5f, 0.75f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Blanc);
		glBegin(GL_QUADS);
			  glVertex3f(-4.0,  4.0, 0.0);
			  glVertex3f( 4.0,  4.0, 0.0);
			  glVertex3f( 4.0, -4.0, 0.0);
			  glVertex3f(-4.0, -4.0, 0.0);
		glEnd();
}

