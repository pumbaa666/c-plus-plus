// Fichier GeomGlut.CPP

#include <GL\glut.h>
#include "geomglut.h"
#include "geometrie.h"
#include "evenements.h"

void myinit()
{
  glClearColor(0.0f, 0.0f, 1.0f, 0.0f); // Initialise la couleur du fond (bleu)
  glEnable(GL_DEPTH_TEST); // Active le Depth Buffer
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Objets géométriques avec GLUT");

  myinit();
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutMotionFunc(Motion);
  glutMainLoop();
  return 0;
}
