// Fichier Evenements.cpp

// Voir commentaire dans glut.h sur ATEXIT
//#define GLUT_DISABLE_ATEXIT_HACK

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "evenements.h"

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//efface l'�cran
	glBegin(GL_TRIANGLES);					//commence le dessin d'un triangle
		glColor3f(0.0f,1.0f,0.0f);			//couleur du premier sommet
		glVertex3f(-65.0f,65.0f,0.0f);		//coordonn�es du premier sommet

		glColor3f(1.0f,0.0f,0.0f);			//etc ...
		glVertex3f(65.0f,-65.0f,0.0f);

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-65.0f,-65.0f,0.0f);
	glEnd();								//fin du trac� du triangle
	glFlush();
}

void Reshape(int w, int h) //En cas de changement de taille de la fenetre.
{											//et lors du lancement du programme
	GLfloat Near = -100.0f;
	GLfloat Far = 100.0f;					//limites visuelles devant/derri�re

	if (h == 0) h = 1;
	glViewport(0,0,w,h);	  //la partie qui va �tre d�ssin�e va de (0,0) � (w,h)
	glMatrixMode(GL_PROJECTION);			//mode projection
	glLoadIdentity();		  	//chargement de la matrice identit� pour ce mode
	if (w<=h)
	{
		clipWidth  = (GLfloat)largeur;     // ces calculs ont pour but de garder
                                         // la proportionnaliteentre les # axes
		clipHeight = (GLfloat)hauteur * h/w;// (un carr� doit rester carr� !!!)
	}
	else
	{
		clipWidth  = (GLfloat)largeur * w/h;
		clipHeight = (GLfloat)hauteur;
	}
   //          left          right        bottom         top
   glOrtho( -clipWidth/2, clipWidth/2, -clipHeight/2, clipHeight/2, Near, Far);
	glMatrixMode(GL_MODELVIEW);				//mode modelview
	glLoadIdentity();				 //chargement de la matrice identit� pour ce mode
}

