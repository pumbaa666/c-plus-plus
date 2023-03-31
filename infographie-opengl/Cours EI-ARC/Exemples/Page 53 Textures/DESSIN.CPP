// Fichier Dessin.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "dessin.h"

void drawFloor()
{
    GLfloat	Couleur[]  = {0.1f, 0.5f, 0.1f, 1.0f};
    glDisable(GL_TEXTURE_2D);
//		glColor4f(0.5f, 0.5f, 0.5f, 0.75f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Couleur);
		glBegin(GL_QUADS);
    		glNormal3d(0.0,0.0,1.0);
			  glVertex3f(-4.0,  4.0, 0.0);
			  glVertex3f( -4.0,  -4.0, 0.0);
			  glVertex3f( 4.0, -4.0, 0.0);
			  glVertex3f(4.0, 4.0, 0.0);
		glEnd();
    glEnable(GL_TEXTURE_2D);
}

