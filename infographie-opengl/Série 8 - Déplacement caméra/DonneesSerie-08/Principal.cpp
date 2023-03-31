// Exercice 8

#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "evenements.h"
#include "calllistes.h"
#include "principal.h"

void myinit()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Fond noir
//  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Fond blanc

  glEnable(GL_DEPTH_TEST);
  char Texte[80];
  sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
  glutSetWindowTitle(Texte);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Objets solides");

  myinit();
  Make_CallListes();
  
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(ToucheSpecial);
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
//  glutIdleFunc(Animate);
  glutMouseFunc(Mouse);
  glutMotionFunc(Motion);
  glutMainLoop();
  return 0;
}

