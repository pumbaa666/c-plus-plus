// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "global.h"

void DessinerLaScene()
{
  glColor3f(NOIR);
  glPushMatrix();
    glScalef(5.0f, 5.0f, 5.0f);
    DessinerLesAxes();
  glPopMatrix();

  glColor3f(ROUGE);
  glTranslatef(5.0f,5.0f, 0.0f);
  glPushMatrix();
    glScalef(5.0f, 5.0f, 5.0f);
    DessinerLesAxes();
  glPopMatrix();

  glColor3f(VERT);
  glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glScalef(5.0f, 5.0f, 5.0f);
    DessinerLesAxes();
  glPopMatrix();

  glColor3f(BLEU);
  glTranslatef(-5.0f,-5.0f, 0.0f);
  glPushMatrix();
    glScalef(5.0f, 5.0f, 5.0f);
    DessinerLesAxes();
  glPopMatrix();
}

void DessinerLesAxes()
{
  glBegin(GL_LINES);
    // Axe X
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, -0.05f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.05f, 0.0f);

    // Axe Y
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.05f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.8f, 0.0f);

    // Axe Z
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 0.0f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.05f, 0.0f, 0.8f);
  glEnd();
}

