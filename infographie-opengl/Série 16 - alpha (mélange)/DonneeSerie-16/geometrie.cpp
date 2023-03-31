// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"

void DessinerLaScene()
{
    ModeDeDessin(Mode);
    glPushMatrix();
        glRotatef(RotationLumiere, 0.0f, 1.0f, 0.0f);
        PositionLumiere(lightPos[0], lightPos[1], lightPos[2]);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0, -2.0);
        {
        GLfloat ambientMaterial[] =  {0.2f, 0.0f, 0.0f, 1.0};
        GLfloat diffuseMaterial[] =  {0.5f, 0.0f, 0.0f, 1.0};
        DessinerPlaque(ambientMaterial, diffuseMaterial, 6.0f);
        }
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        {
        GLfloat ambientMaterial[] =  {0.0f, 0.2f, 0.0f, 1.0};
        GLfloat diffuseMaterial[] =  {0.0f, 0.5f, 0.0f, 1.0};
        DessinerPlaque(ambientMaterial, diffuseMaterial, 4.0f);
        }
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0, 2.0);
        {
        GLfloat ambientMaterial[] =  {0.0f, 0.0f, 0.2f, 1.0};
        GLfloat diffuseMaterial[] =  {0.0f, 0.0f, 0.5f, 1.0};
        DessinerPlaque(ambientMaterial, diffuseMaterial, 5.0f);
        }
    glPopMatrix();
    DessinerLeSol();
}

void DessinerPlaque(GLfloat couleurAmbiant[4], GLfloat couleurDiffuse[4], GLfloat taille)
{
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE); // Z-Buffer en lecture seule !
    glMaterialfv(GL_FRONT, GL_AMBIENT, couleurAmbiant);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, couleurDiffuse);

    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(-taille/2, 0.0, 0.0);
        glVertex3f(taille/2, 0.0, 0.0);
        glVertex3f(taille/2, taille, 0.0);
        glVertex3f(-taille/2, taille, 0.0);
    glEnd();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void PositionLumiere(float x, float y, float z)
{
  GLfloat LightPos[4] = {x,y,z,1.0};  // ww = 1 --> Position = (x,y,z)
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);

  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glPushMatrix();
          glColor3f(1.0f, 1.0f, 0.0f);
          glTranslatef(x, y, z);
          glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
  glPopAttrib();
}

void DessinerLesAxes()
{
  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);    glBegin(GL_LINES);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.8f, -0.05f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.8f, 0.05f, 0.0f);

      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(-0.05f, 0.8f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.05f, 0.8f, 0.0f);

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
	if(mask & bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if(mask & bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if(mask & bOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);

   if(mask & bShadeModel)
      glShadeModel(GL_SMOOTH);
   else
      glShadeModel(GL_FLAT);
}

