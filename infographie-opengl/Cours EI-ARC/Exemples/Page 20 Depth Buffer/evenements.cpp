// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "evenements.h"

void Display(void)
{
	//ne pas oublier d'effacer le Depth-buffer
   // à chaque rafraichissement de l'écran
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0f,1.0f,1.0f);
  glPointSize(5.0);
	glBegin(GL_POINTS); // Ne se voit pratiquement pas.
		glVertex2f(-10.0f,-10.0f);
	glEnd();

	glColor3f(1.0f,0.0f,1.0f);
	glBegin(GL_LINES);
		glVertex3f(-10.0f,-10.0f,-50.0f);
		glVertex3f(100.0f,100.0f,50.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,130.0f,0.0f);

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(130.0f,0.0f,0.0f);
	glEnd();
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
		clipWidth  = (GLfloat)LARGEUR;     // ces calculs ont pour but de garder
                                         // la proportionnaliteentre les # axes
		clipHeight = (GLfloat)HAUTEUR * h/w;// (un carré doit rester carré !!!)
	}
	else
	{
		clipWidth  = (GLfloat)LARGEUR * w/h;
		clipHeight = (GLfloat)HAUTEUR;
	}
   //          left          right        bottom         top
   glOrtho( -clipWidth/2, clipWidth/2, -clipHeight/2, clipHeight/2, Near, Far);
	glMatrixMode(GL_MODELVIEW);				//mode projection
	glLoadIdentity();				 //chargement de la matrice identité pour ce mode
}

