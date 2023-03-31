// Fichier Lumiere.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "lumiere.h"

void SetLight()
{
        GLfloat ambientProperties[] = {0.7f, 0.7f, 0.7f, 1.0f};
        GLfloat diffuseProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat positionProperties[] = {5.0f, 0.0f, 0.0f, 0.0f};
        glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
        glLightfv( GL_LIGHT0, GL_POSITION, positionProperties);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
}

