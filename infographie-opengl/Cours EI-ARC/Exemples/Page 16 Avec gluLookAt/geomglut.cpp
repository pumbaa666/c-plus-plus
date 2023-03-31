#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"

void myinit()
{
  glClearColor(BLANC, 0.0f);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Translation, rotation, translation (avec gluLookAt)");

  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

