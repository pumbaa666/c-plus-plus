#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "evenements.h"
#include "triangle.h"
#include "global.h"

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );  	//l'�cran sera effac� en noir
	glShadeModel(GL_SMOOTH);					//le triangle sera rempli en d�grad�
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
  glutReshapeFunc(Reshape);//fonction g�rant le redimensionnement de la fen�tre
  glutDisplayFunc(Display);
  glutMainLoop();					 //boucle principale
  return 0;
}
