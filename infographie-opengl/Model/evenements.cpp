#include <GL/glut.h>		// Fonctions GLUT
#include "global.cpp"		// Fonctions GLUT
void Display(void)
{
	glFlush();
}

void Reshape(int w, int h)
{
	GLfloat Near = -100.0f;
	GLfloat Far = 100.0f;	// limites visuelles devant/derrière

	if (h == 0) h = 1;
	glViewport(0,0,w,h); //la partie qui va être dessinée va de (0,0) à (w,h)
    glMatrixMode(GL_PROJECTION); // mode projection
	glLoadIdentity(); // chargement de la matrice identité
	if (w<=h)
	{
		clipWidth  = (GLfloat)largeur; // ces calculs ont pour but de garder la proportionnalité entre les # axes (un carré doit rester carré !!!)
		clipHeight = (GLfloat)hauteur * h/w;
	}
	else
	{
		clipWidth  = (GLfloat)largeur * w/h;
		clipHeight = (GLfloat)hauteur;
	}
   //          left          right        bottom         top
   glOrtho(-clipWidth/2, clipWidth/2, -clipHeight/2, clipHeight/2, Near, Far);
   glMatrixMode(GL_MODELVIEW); // mode modelview
   glLoadIdentity();  // chargement de la matrice identité
}
