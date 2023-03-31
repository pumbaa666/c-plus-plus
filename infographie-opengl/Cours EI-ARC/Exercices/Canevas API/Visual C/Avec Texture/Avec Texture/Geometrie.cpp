// Fichier Geometrie.cpp

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "global.h"
#include "dessin.h"
#include "geometrie.h"

void DessinerLaScene(GLvoid)									// Here's Where We Do All The Drawing
{
  ModeDeDessin(Mode);

  // Positionner la lumière :
  glPushMatrix();
    glRotatef(RotationLumiere, 0.0f, 1.0f, 0.0f); // Rotation de la lampe
    PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3]);
  glPopMatrix();

  glPushMatrix();
    // ...
    DessinerUnRectangle();
  glPopMatrix();

  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING); // Désactive l'éclairage
    DessinerLesAxes();
    glColor3f(0.0f, 0.0f, 0.0f);
    DessinerLeSol();
  glPopAttrib();
}

void PositionLumiere(float x, float y, float z, float w)
{
  GLfloat LightPos[4] = {x, y, z, w};  // ww = 1 --> Position = (x,y,z)
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);

  // Afficher la lampe
  // Sauvegarde de la matrice de transformation
  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING); // Désactive l'éclairage
    glPushMatrix();
      glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
      glTranslatef(x, y, z);
      GLUquadricObj * obj = gluNewQuadric();
      gluQuadricDrawStyle(obj, GLU_FILL);
      gluSphere(obj,
                0.5,         // Rayon de la sphère
                50,          // slices (longitudes)
                50);         // stacks (latitudes)
      gluDeleteQuadric(obj);
    glPopMatrix();
  glPopAttrib();
}

void DessinerLesAxes()
{
//  glDisable(GL_LIGHTING); // Désactive l'éclairage
  glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);   // Axex X rouge
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, -0.05f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.05f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);   // Axex Y vert
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.05f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.8f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);   // Axex Z bleu
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 0.0f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.05f, 0.0f, 0.8f);
  glEnd();
//  glEnable(GL_LIGHTING); // Active l'éclairage
}

void DessinerLeSol()
{
	int r,c;
	int nStep = 3;

//  glColor3f(1.0f, 1.0f, 1.0f);
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
