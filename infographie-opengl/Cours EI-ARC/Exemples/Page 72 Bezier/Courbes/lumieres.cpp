// Fichier Lumiere.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "global.h"
#include "lumieres.h"

void SetLight()
{
	GLfloat ambientProperties[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat diffuseProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);

  PositionLumiere();
	glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void PositionLumiere()
{
  static float x, y, z;
  x = positionProperties[0];
  y = positionProperties[1];
  z = positionProperties[2];

	glLightfv( GL_LIGHT0, GL_POSITION, positionProperties);

  // Afficher la lampe
  // Sauvegarde de la matrice de transformation
  glDisable(GL_LIGHTING); // Désactive l'éclairage

  if(positionProperties[3] == 1.0)       // Lumière à la position (x, y, z)
    {
    glPushMatrix();
      glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
      glTranslatef(x, y, z);
      glutSolidSphere(.2, 50, 50);
    glPopMatrix();
  }
  else                                    // Lumière à l'infini
  {
    glPushMatrix();
      glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
      glBegin(GL_LINES);
        glVertex3f(x, y, z);
        glVertex3f(0,0.0,0);
        glVertex3f(x+1.0, y, z);
        glVertex3f(1.0,0.0,0.0);
        glVertex3f(x-1.0, y, z);
        glVertex3f(-1.0,0.0,0.0);
      glEnd();
    glPopMatrix();
  }

  glEnable(GL_LIGHTING); // Active l'éclairage
}

