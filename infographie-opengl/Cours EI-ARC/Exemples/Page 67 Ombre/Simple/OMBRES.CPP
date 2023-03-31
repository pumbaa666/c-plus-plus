// Fichier Ombres.cpp

// Attention, ce programme n'utilise pas le Stencil Buffer.
// Donc si l'ombre sort du sol, on la voit encore dans le "vide".
// On peut essayer avec une position de lumière décalée,
// par exemple (10, 0, 15, 1).

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "lumiere.h"
#include "evenements.h"

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.5f, 0.0f ); // Ce sont les valuers par défaut.
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_POLYGON_SMOOTH);
   SetLight();
}

void reshape (int width, int height)
{
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.0, ((GLfloat) width) / ((GLfloat) height),1.0,100.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (0.0,-7.0,15.0, 0.0, 0.0, 0.0,0.0,0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_SMOOTH);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur,hauteur);
  glutCreateWindow("Ombres sans Stencil Buffer");

  SetupRC();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();				//boucle principale
  return 0;
}

