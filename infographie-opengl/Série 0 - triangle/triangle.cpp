#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "evenements.h"
#include "triangle.h"
#include "global.h"

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );  	//l'écran sera effacé en noir
	glShadeModel(GL_SMOOTH);					//le triangle sera rempli en dégradé
//  glShadeModel(GL_FLAT);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 	//pas de Double-buffering
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Triangle");

  SetupRC();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();					 //boucle principale
  return 0;
}
