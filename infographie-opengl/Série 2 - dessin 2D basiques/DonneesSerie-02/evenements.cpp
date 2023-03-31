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
  GLfloat left, right, bottom, top;
  if (h == 0) h = 1;
  if (w == 0) w = 1;
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Volume de clipping : (left, right, bottom, top, near, far)
  if (w <= h)
  {
    left = LEFT;
    right = RIGHT;
    bottom = BOTTOM * h/w;
    top = TOP * h/w;
  }
  else
  {
    left = LEFT * w/h;
    right = RIGHT * w/h;
    bottom = BOTTOM;
    top = TOP;
  }
  glOrtho(left, right, bottom, top, -2.0f, 2.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Mouse(int button, int state, int /*x*/, int /*y*/)
{
  if(button == GLUT_LEFT_BUTTON)
    if(state == GLUT_DOWN)
    {
      Figure++;
      if (Figure > 11) Figure = 1;
      glutPostRedisplay();
    }
  if(button == GLUT_RIGHT_BUTTON)
    if(state == GLUT_DOWN)
    {
      Figure--;
      if (Figure < 1) Figure = 10;
        glutPostRedisplay();
    }
}
