// Fichier Evenements.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"

void Display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  DessinerLaScene();
  glFlush();
}

void Reshape(int w, int h)
{
  GLdouble aspect;
  if (h == 0) h = 1;
  if (w == 0) w = 1;
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Projection perspective
  // ...

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Mouse(int button, int state, int /*x*/, int /*y*/)
{
  if(button == GLUT_LEFT_BUTTON)
    if(state == GLUT_DOWN)
    {
      Figure++;
      if (Figure > 18) Figure = 1;
      glutPostRedisplay();
    }
}

void Motion(int x, int y)
{
}

