// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include "evenements.h"
#include "geometrie.h"
#include "global.h"

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  DessinerLaScene();

  glPopMatrix();
  glutSwapBuffers();
}

void myReshape(int w, int h)
{
  if (h == 0) h = 1;
  if (w == 0) w = 1;
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Volume de clipping : (left, right, bottom, top, near, far)
  if (w <= h)
  {
    left = -10.0f;
    right = 10.0f;
    bottom = -10.0f * h/w;
    top = 10.0f * h/w;
  }
  else
  {
    left = -10.0f * w/h;
    right = 10.0f * w/h;
    bottom = -10.0f;
    top = 10.0f;
  }

  glOrtho(left, right, bottom, top, -10.0f, 10.0f);
  glMatrixMode(GL_MODELVIEW);
}

