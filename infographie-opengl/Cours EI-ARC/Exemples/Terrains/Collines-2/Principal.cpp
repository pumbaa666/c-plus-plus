// Fichier Principal.CPP

#include <GL\glut.h>
#include "evenements.h"
#include "calllistes.h"
#include "principal.h"

void myinit()
{
//  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearColor(0.0f, 0.0f, 0.8f, 0.0f);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Objets solides");

  myinit();
  Make_CallListes();
  glutKeyboardFunc(Key);
  glutSpecialFunc(ToucheSpecial);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();
  return 0;
}

