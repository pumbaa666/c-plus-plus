// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "evenements.h"

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCallList(point);
	glCallList(triangle);
	glCallList(droite);

	glFlush();
}

void Reshape(int w, int h) //En cas de changement de taille de la fenetre.
{											//et lors du lancement du programme
	GLfloat Near = -100.0f;
	GLfloat Far = 100.0f;					//limites visuelles devant/derrière

	if (h == 0) h = 1;
	glViewport(0,0,w,h);	  //la partie qui va être déssinée va de (0,0) à (w,h)
	glMatrixMode(GL_PROJECTION);			//mode projection
	glLoadIdentity();		  	//chargement de la matrice identité pour ce mode
	if (w<=h)
	{
		clipWidth  = (GLfloat)largeur;     // ces calculs ont pour but de garder
                                         // la proportionnaliteentre les # axes
		clipHeight = (GLfloat)hauteur * h/w;// (un carré doit rester carré !!!)
	}
	else
	{
		clipWidth  = (GLfloat)largeur * w/h;
		clipHeight = (GLfloat)hauteur;
	}
   //          left          right        bottom         top
   glOrtho( -clipWidth/2, clipWidth/2, -clipHeight/2, clipHeight/2, Near, Far);
	glMatrixMode(GL_MODELVIEW);				//mode projection
	glLoadIdentity();				 //chargement de la matrice identité pour ce mode
}

