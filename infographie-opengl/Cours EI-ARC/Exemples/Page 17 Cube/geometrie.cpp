// Fichier Geometrie.cpp

#include <GL\glut.h>
#include <math.h>
#include "geometrie.h"
#include "global.h"

void DessinerLaScene()
{
  total %= 360*500;			// temps écoulé en ms
	glPushMatrix();
		glTranslatef(0.0f, 5.0f+(GLfloat)sin(GLfloat(total)/500.0f)*3.0f, 0.0f);
		glRotatef(total/50.0f, 0.3f, 0.5f, 0.8f);
		glBegin(GL_QUADS);
			glColor3f(ROUGE);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f( 0.5f, -0.5f, -0.5f);
			glVertex3f( 0.5f,  0.5f, -0.5f);
			glVertex3f(-0.5f,  0.5f, -0.5f);

			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f,  0.5f);
			glVertex3f( 0.5f, -0.5f,  0.5f);
			glVertex3f( 0.5f,  0.5f,  0.5f);
			glVertex3f(-0.5f,  0.5f,  0.5f);

			glColor3f(BLEU);
			glVertex3f( 0.5f, -0.5f,  0.5f);
			glVertex3f( 0.5f, -0.5f, -0.5f);
			glVertex3f( 0.5f,  0.5f, -0.5f);
			glVertex3f( 0.5f,  0.5f,  0.5f);

			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(-0.5f, -0.5f,  0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f,  0.5f, -0.5f);
			glVertex3f(-0.5f,  0.5f,  0.5f);

			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f,  0.5f,  0.5f);
			glVertex3f(-0.5f,  0.5f, -0.5f);
			glVertex3f( 0.5f,  0.5f, -0.5f);
			glVertex3f( 0.5f,  0.5f,  0.5f);

			glColor3f(VERT);
			glVertex3f(-0.5f, -0.5f,  0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f( 0.5f, -0.5f, -0.5f);
			glVertex3f( 0.5f, -0.5f,  0.5f);
		glEnd();
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

