// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <stdio.h>
#include "define.h"
#include "global.h"
#include "dessin.h"
#include "lumiere.h"
#include "evenements.h"

void Display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glDisable(GL_DEPTH_TEST);

   // On ne va pas dessiner dans le buffer-écran, mais dans les autres buffers
   glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
   glEnable(GL_STENCIL_TEST);
   printf("Stencil : %d\n",glutGet(GLUT_WINDOW_STENCIL_SIZE));
   glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
   glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
   //Dessin de la surface réfléchissante dans le stencil-buffer
   drawFloor();
   //on reactive le dessin à l'ecran
   glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
   glEnable(GL_DEPTH_TEST);

   // Cela va dessiner uniquement dans les endroits du stencil-buffer
   // qui sont à 1 c.a.d. dans le miroir
   glStencilFunc(GL_EQUAL, 1, 0xffffffff);
   glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
   glCullFace(GL_FRONT);
   glPushMatrix();
         // On fait la symétrie par rapport à l'axe des Z
         glScalef(1.0, 1.0, -1.0);
         //les lumières aussi subissent la symétrie
         glEnable(GL_NORMALIZE);
         SetLight();
         // On dessine la scène qui va être reflétée
         glTranslatef(0.0f, 0.0f, 5.0f);
         glRotatef((80.0f), -0.5f, 0.3f, -0.8f);
         glRotatef((10.0f), 0.5f, -0.3f, 0.8f);
         glCallList(cube);
         glDisable(GL_NORMALIZE);
   glPopMatrix();
   // Fin de la symétrie
   // On remet les lumières	et tout le reste
   SetLight();
   glCullFace(GL_BACK);
   glDisable(GL_STENCIL_TEST);

   // On dessine le sol transparent
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glDisable(GL_LIGHTING);
   drawFloor();
   glEnable(GL_LIGHTING);
   glDisable(GL_BLEND);

   // Puis le reste de la scène
   glPushMatrix();
         glTranslatef(0.0f, 0.0f, 5.0f);
         glRotatef((80.0f), -0.5f, 0.3f, -0.8f);
         glRotatef((10.0f), 0.5f, -0.3f, 0.8f);
         glCallList(cube);
   glPopMatrix();
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

