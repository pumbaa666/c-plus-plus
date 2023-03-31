#include <GL/glut.h>
#include "global.h"
#include "geometrie.h"
#include "evenements.h"
#include "define.h"
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(0.0f, 0.0f, -4.0f);
    Dessiner();
    glTranslatef(0.0f, 0.0f, 4.0f);
	glFlush();
}

void Reshape(int w, int h)
{
	GLfloat clipWidth;
	GLfloat clipHeight;

	if (h == 0) h = 1;
	glViewport(0,0,w,h); //la partie qui va �tre dessin�e va de (0,0) � (w,h)
	if (w<=h)
	{
		clipWidth  = (GLfloat)LARGEUR; // ces calculs ont pour but de garder la proportionnalit� entre les # axes (un carr� doit rester carr� !!!)
		clipHeight = (GLfloat)HAUTEUR * h/w;
	}
	else
	{
		clipWidth  = (GLfloat)LARGEUR * w/h;
		clipHeight = (GLfloat)HAUTEUR;
	}

    /* Mode paral�lle */
    if(mode == 1)
    {
        GLfloat Near = -10.0f;
        GLfloat Far = 10.0f;	// limites visuelles devant/derri�re
        glMatrixMode(GL_PROJECTION); // mode projection
        glLoadIdentity(); // chargement de la matrice identit�
        //          left          right        bottom         top
        glOrtho(-clipWidth/2, clipWidth/2, -clipHeight/2, clipHeight/2, Near, Far);
    }
    /* fin du mode paral�lle */

    /* mode perspective */
    else /* A VOIR */
    {
        glMatrixMode(GL_PROJECTION); // mode projection
        glLoadIdentity(); // chargement de la matrice identit�
        GLdouble angle_de_vue = 45.0f;
        GLdouble aspect = (GLdouble)w / (GLdouble)h;
        gluPerspective(angle_de_vue, aspect, 1.0, 100.0);
    }
   /* fin du mode perspective */

   glMatrixMode(GL_MODELVIEW); // mode modelview
   glLoadIdentity();  // chargement de la matrice identit�
}

void Souris(int bouton, int etat, int, int)
{
    if(bouton == GLUT_LEFT_BUTTON)
    {
        if(etat == GLUT_DOWN)
        {
            objet++;
            if(objet >= 10)
                objet = 0;
            glutPostRedisplay(); // effectue le Display(); avec un message WM_PAINT bien particulier. Il est mis en queue des chose � faire.
        }
    }
    else if(bouton == GLUT_RIGHT_BUTTON)
    {
        if(etat == GLUT_DOWN)
        {
            if(mode == 0)
                mode = 1;
            else
                mode = 0;
            glutPostRedisplay(); // effectue le Display(); avec un message WM_PAINT bien particulier. Il est mis en queue des chose � faire.
        }
    }
}

