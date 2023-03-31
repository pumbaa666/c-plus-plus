// Fichier GeomGlut.CPP

#include <GL\glut.h>
#include "geomglut.h"
#include "geometrie.h"
#include "evenements.h"

void myinit()
{
  // Initialiser la couleur du fond (blanc)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );  	//l'�cran sera effac� en noir
	glShadeModel(GL_FLAT);					//le triangle sera rempli en d�grad�
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Les primitives");

  myinit();
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutMainLoop();
  return 0;
}
