// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "dessin.h"
#include "lumiere.h"
#include "evenements.h"

void Display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //on dessine la scène normalement
   glDisable(GL_LIGHTING);
   drawFloor();
   glEnable(GL_LIGHTING);
   glPushMatrix();
      glTranslatef(0.0f, 0.0f, 5.0f);
      glRotatef((80.0f), -0.5f, 0.3f, -0.8f);
      glRotatef((10.0f), 0.5f, -0.3f, 0.8f);
      //dessin du cube en couleur normale
      cube(0);
   glPopMatrix();

   //on initialise la transparence
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   //Calcul de la matrice de projection sur le sol
   MakeShadowMatrix(sol,light_pos,ombre);
   glPushMatrix();
      glMultMatrixf((GLfloat *) ombre);
      //dessin de l'objet
      glTranslatef(0.0f, 0.0f, 5.0f);
      glRotatef((80.0f), -0.5f, 0.3f, -0.8f);
      glRotatef((10.0f), 0.5f, -0.3f, 0.8f);
      //on dessine le cube en noir transparent
      cube(1);
   glPopMatrix();

   glDisable(GL_BLEND);
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

