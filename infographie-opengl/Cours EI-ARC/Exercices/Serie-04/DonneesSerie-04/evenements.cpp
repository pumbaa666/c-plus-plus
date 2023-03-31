// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include "evenements.h"
#include "geometrie.h"
#include "global.h"

void Display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
      glScalef(5.0f, 5.0f, 5.0f);
      DessinerLesAxes();
    glPopMatrix();

    DessinerLaScene();
  glPopMatrix();
  glutSwapBuffers();
//  glFlush();
}

void Reshape(int w, int h)
{
  if (h == 0) h = 1;
  if (w == 0) w = 1;
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Volume de clipping : (left, right, bottom, top, near, far)
  if (w <= h)
  {
    left = -20.0f;
    right = 20.0f;
    bottom = -20.0f * h/w;
    top = 20.0f * h/w;
  }
  else
  {
    left = -20.0f * w/h;
    right = 20.0f * w/h;
    bottom = -20.0f;
    top = 20.0f;
  }
  glOrtho(left, right, bottom, top, -2.0f, 2.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

