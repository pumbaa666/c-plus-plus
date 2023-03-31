// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include "evenements.h"
#include "geometrie.h"
#include "global.h"

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  DessinerLaScene();
  glutSwapBuffers();
}

void myReshape(int w, int h)
{
  GLdouble RapportAspect;
  if (h == 0) h = 1;
  if (w == 0) w = 1;
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Calcul du rapport d'aspect de la fen�tre
  RapportAspect = (GLdouble)w / (GLdouble)h;
  gluPerspective(45.0, RapportAspect, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();          // Charger la matrice de visualisation identit�
  // D�placer le point de vue (la cam�ra) :
  // La position de la cam�ra est en (0, 0, 3)
  // La direction de vis�e de la cam�ra est le point (0, 0, 0)
  // L'axe dirig� vers le haut est le vecteur de composantes (0, 1, 0)
  gluLookAt(0.0, 0.0, 10.0,    // Position de la cam�ra
            0.0, 5.0, 0.0,     // Direction de vis�e
            0.0, 1.0, 0.0);    // Axe dirig� vers le haut
}

void IdleFunction(void)
{
  total += 50;
  Sleep(50);
//  display();
  glutPostRedisplay();
}

