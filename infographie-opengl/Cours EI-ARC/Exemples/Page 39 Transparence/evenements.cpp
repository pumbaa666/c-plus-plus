// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "dessin.h"
#include "evenements.h"

void Display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   drawFloor();
   glPushMatrix();
      //initialisation de la transparence
      glEnable(GL_BLEND);
      glDepthMask (GL_FALSE);
      //la couleur de l'objet va être
      // (1-alpha de l'objet) * couleur du fond +
      // (alpha * couleur de l'objet)
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glTranslatef(0.0f, -2.0f, 5.0f);
      glRotatef((80.0f), -0.5f, 0.3f, -0.8f);
      glRotatef((10.0f), 0.5f, -0.3f, 0.8f);
      glCallList(cube);
      glDepthMask (GL_TRUE);
      //on désactive la transparence
      glDisable(GL_BLEND);
   glPopMatrix();
//   drawFloor();
   glutSwapBuffers();
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
   gluLookAt (0.0,-7.0,15.0, 0.0, 0.0, 0.0,0.0,0.0, 1.0);
}

