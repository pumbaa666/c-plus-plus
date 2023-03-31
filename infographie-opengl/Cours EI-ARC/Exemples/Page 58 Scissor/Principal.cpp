// Fichier Principal.CPP
#include <GL\glut.h>
#include "global.h"
#include "evenements.h"
#include "principal.h"

void myinit()
{
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Fond blanc
	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
//	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

   // Pour séparer le calculs des faces avant et arrière
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// Enable this light in particular
	glEnable(GL_LIGHT0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Objets solides");

  myinit();
  glutKeyboardFunc(Key);
  glutSpecialFunc(ToucheSpecial);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutIdleFunc( Animate );
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();
  return 0;
}

