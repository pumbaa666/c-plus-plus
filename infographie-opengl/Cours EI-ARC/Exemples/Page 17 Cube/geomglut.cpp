#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"

void myinit()
{
  glClearColor(NOIR, 0.0f);
  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Cube");

  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutIdleFunc(IdleFunction);
  glutMainLoop();
  return 0;
}

