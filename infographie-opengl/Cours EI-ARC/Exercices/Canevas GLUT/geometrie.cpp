// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "normal.h"
#include "geometrie.h"

void DessinerLaScene()
{
  ModeDeDessin(Mode);

  // Positionner la lumière :
  glPushMatrix();
    glRotatef(RotationLumiere, 0.0f, 1.0f, 0.0f); // Rotation de la lampe
    PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3]);
  glPopMatrix();

  glPushMatrix();
    // ...
  glPopMatrix();

  DessinerLesAxes();
  DessinerLeSol();
}

void PositionLumiere(float x, float y, float z, float w)
{
  GLfloat LightPos[4] = {x,y,z,w};  // w = 1 --> Position = (x,y,z)
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);

  // Afficher la lampe
  // Sauvegarde de la matrice de transformation
  glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING); // Désactive l'éclairage
        glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
        glTranslatef(x, y, z);
        glutSolidSphere(.5, 50, 50);
    glPopAttrib();
  glPopMatrix();
}

void DessinerLesAxes()
{
  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING); // Désactive l'éclairage
  glBegin(GL_LINES);
    // Axe X
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, -0.05f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.05f, 0.0f);

    // Axe Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.05f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.8f, 0.0f);

    // Axe Z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 0.0f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.05f, 0.0f, 0.8f);
  glEnd();
  glPopAttrib();
}

void DessinerLeSol()
{
	int r,c;
	int nStep = 3;

  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING);
//   glColor3f(1.0f, 1.0f, 1.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);

	for(r = -100; r  <= 100; r += nStep)
		{
		glVertex3f((float)r, 0.0f, -100.0f);
		glVertex3f((float)r, 0.0f, 100.0f);
		}

	for(c = -100; c <= 100; c += nStep)
		{
		glVertex3f(100.0f, 0.0f, (float)c);
		glVertex3f(-100.0f, 0.0f, (float)c);
		}

	glEnd();
  glPopAttrib();
}

void ModeDeDessin(int mask)
{
	// Turn culling on if flag is set
	if(mask & bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Enable depth testing if flag is set
	if(mask & bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// Draw back side as a polygon only, if flag is set
	if(mask & bOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);

   if(mask & bShadeModel)
      glShadeModel(GL_SMOOTH);  // Interpolation de la couleur
                                // entre les différents sommets
   else
      glShadeModel(GL_FLAT);    // La couleur du polygone est la couleur
                                // du dernier sommet (qui est aussi le premier)
}

