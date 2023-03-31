// Fichier Triangle.cpp

// Voir commentaire dans glut.h sur ATEXIT
#define GLUT_DISABLE_ATEXIT_HACK

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "evenements.h"

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );  	//l'écran sera effacé en noir
	glShadeModel(GL_SMOOTH);					//le triangle sera rempli en dégradé
	glFrontFace(GL_CW);						//on tourne dans le sens horaire
  glEnable(GL_CULL_FACE);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 	//pas de Double-buffering
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur,hauteur);
  glutCreateWindow("Triangle");

  SetupRC();
  glutReshapeFunc(Reshape);				//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();					//boucle principale
  return 0;
}
