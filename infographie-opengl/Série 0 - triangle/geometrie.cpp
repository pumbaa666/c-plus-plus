// Fichier Geometrie.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "geometrie.h"

void DessinerLeTriangle()
{
	glFrontFace(GL_CW);						//on tourne dans le sens horaire
	glBegin(GL_TRIANGLES);					//commence le dessin d'un triangle
		glColor3f(0.0f,1.0f,0.0f);			//couleur du premier sommet
		glVertex3f(-65.0f,65.0f,0.0f);		//coordonn�es du premier sommet

		glColor3f(1.0f,0.0f,0.0f);			//etc ...
		glVertex3f(65.0f,-65.0f,0.0f);

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-65.0f,-65.0f,0.0f);
	glEnd();								//fin du trac� du triangle
	glFrontFace(GL_CCW);		// On remet le d�faut
}
