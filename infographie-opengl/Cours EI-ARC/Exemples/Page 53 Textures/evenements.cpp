// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "lumiere.h"
#include "global.h"
#include "dessin.h"
#include "evenements.h"

void Display(void)
{
   static GLfloat a = 0.0;
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   drawFloor();
   glPushMatrix();
      glTranslatef(0.0f, -2.0f, 5.0f);
      glRotatef((80.0f), -0.5f, 0.3f, -0.8f);
      glRotatef((10.0f), 0.5f, -0.3f, 0.8f);
      glRotatef(a, 0.0f, 0.0f, 1.0f);
      glCallList(cube);
   glPopMatrix();
   glutSwapBuffers();
   a++;
   glutPostRedisplay();
   Sleep(20);
}

void Reshape (int w, int h)
{
   GLdouble RapportAspect;
   GLdouble AngleOuverture = 45.0;
   GLdouble PlanAvant = 1.0;
   GLdouble PlanArriere = 100.0;

   if (h == 0) h = 1;
   if (w == 0) w = 1;
   glViewport (0, 0, w, h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   RapportAspect = (GLdouble)w / (GLdouble)h;
   gluPerspective (AngleOuverture, RapportAspect,PlanAvant,PlanArriere);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   SetLight();
   gluLookAt (0.0,-7.0,15.0, 0.0, 0.0, 0.0,0.0,1.0, 0.0);
}

