// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "evenements.h"
#include "principal.h"

void MyInit()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); // Lumière ambiante generale à TOUTE la scène. "Indispensable" avec un spot à petit rayon
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); // Soit cette ligne, soit celle du dessus.
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);
	glEnable(GL_LIGHT0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Transparence");

  MyInit();
  glutKeyboardFunc(Key);
  glutSpecialFunc(ToucheSpecial);
  glutReshapeFunc(MyReshape);
  glutDisplayFunc(Display);
  glutIdleFunc( Animate );
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();
  return 0;
}

