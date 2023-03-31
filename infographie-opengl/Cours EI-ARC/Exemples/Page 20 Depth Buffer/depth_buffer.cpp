// Fichier Depth_buffer.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "evenements.h"

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f ); // Ce sont les valeurs par défaut

  // Anti-aliasing
	glShadeModel(GL_SMOOTH);
//	glShadeModel(GL_FLAT);
  glEnable(GL_POINT_SMOOTH);
//  glDisable(GL_POINT_SMOOTH);

  // Culling
	glFrontFace(GL_CCW);
//	glFrontFace(GL_CW);
  glCullFace(GL_BACK);  // GL_BACK, GL_FRONT ou GL_FRONT_AND_BACK
  glEnable(GL_CULL_FACE);
//  glDisable(GL_CULL_FACE);

	// Depth-buffer
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  // Ne pas oublier d'initialiser le Depth-Buffer
  // Pas de Double-buffering
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(LARGEUR, HAUTEUR);
  glutCreateWindow("Test");

  SetupRC();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();				//boucle principale
  return 0;
}
