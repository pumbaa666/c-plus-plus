// Fichier CallListes.cpp

#include <GL\glut.h>
#include <math.h>
#include <stddef.h>
#include "global.h"
#include "calculhauteur.h"
#include "calllistes.h"

void Make_CallListes()
{
  axes = glGenLists(6);
  murs = axes + 1;
  toit = murs + 1;
  maison = toit + 1;
  sol = maison + 1;
  cone = sol + 1;

  // Dessin des axes
  glNewList(axes, GL_COMPILE);
  glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
      // Axe Ox
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.8f, -0.05f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.8f, 0.05f, 0.0f);

      // Axe Oy
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(-0.05f, 0.8f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.05f, 0.8f, 0.0f);

      // Axe Oz
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(-0.05f, 0.0f, 0.8f);
      glVertex3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.05f, 0.0f, 0.8f);
    glEnd();
  glEndList();

  // Dessin des 4 murs
  glNewList(murs, GL_COMPILE);
    glFrontFace(GL_CW);           // Dans le sens des aiguilles d'une montre
    glBegin(GL_QUAD_STRIP);
       glColor3f(.9f, .9f, .9f);  // La couleur est différente pour chaque face
                                  // pour donner l'illusion d'un éclairage.
       glVertex3f(0.0f, 0.0f, 0.0f);   // 0
       glVertex3f(0.0f, 4.0f, 0.0f);   // 1
       glVertex3f(10.0f, 0.0f, 0.0f);  // 2
       glVertex3f(10.0f, 4.0f, 0.0f);  // 3
       glVertex3f(10.0f, 0.0f, -5.0f); // 4
       glColor3f(0.7f, .7f, .7f);
       glVertex3f(10.0f, 4.0f, -5.0f); // 5
       glVertex3f(0.0f, 0.0f, -5.0f);  // 6
       glColor3f(.6f, 0.6f, .6f);
       glVertex3f(0.0f, 4.0f, -5.0f);  // 7
       glVertex3f(0.0f, 0.0f, 0.0f);   // 8
       glColor3f(.5f, .5f, .5f);
       glVertex3f(0.0f, 4.0f, 0.0f);   // 9
    glEnd();
  glEndList();

  // Dessin du toit
  glNewList(toit, GL_COMPILE);
    glFrontFace(GL_CW);           // Dans le sens des aiguilles d'une montre
    glBegin(GL_QUAD_STRIP);
       glColor3f(0.8f, .0f, .0f);
       glVertex3f(10.5f, 4.0f, 0.5f);   // 0
       glVertex3f(-0.5f, 4.0f, 0.5f);   // 1
       glVertex3f(10.5f, 6.0f, -2.5f);  // 2
       glVertex3f(-0.5f, 6.0f, -2.5f);  // 3
       glVertex3f(10.5f, 4.0f, -5.5f); // 4
       glColor3f(1.0f, .0f, .0f);
       glVertex3f(-0.5f, 4.0f, -5.5f); // 5
    glEnd();
  glEndList();

  // Dessin de la maison (murs + toit)
  glNewList(maison, GL_COMPILE);
    glCallList(murs);
    glCallList(toit);
  glEndList();

  // Dessin du sol
  int xx,c;
  int zz;
  int zDebut, zFin, nStepZ = 1;
  int nStep = 1;
  GLfloat ** hauteur = NULL;
  zDebut = LARGEUR_TERRAIN;
  zFin = 0;

  InitialiserHauteurs(hauteur);

  glNewList(sol, GL_COMPILE);
    glFrontFace(GL_CW);           // Dans le sens des aiguilles d'une montre
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
      glScalef(1.0f, 40.0f, 1.0f);
      glTranslatef(-LARGEUR_TERRAIN/2, 0, -LARGEUR_TERRAIN/2);

      glBegin(GL_TRIANGLE_STRIP);
        for(xx = 0; xx  < LARGEUR_TERRAIN-1; xx += nStep)
        {
          if(zDebut == 0)
          {
            zDebut = LARGEUR_TERRAIN;
            zFin = 0;
            nStepZ = -nStep;
            for(zz = zDebut-1; zz  >= zFin; zz += nStepZ)
            {
              glColor3f(0.0f, (float)hauteur[xx+1][zz], 0.0f);
              glVertex3f((float)xx+nStep, hauteur[xx+1][zz], (float)zz);
              glColor3f(0.0f, (float)hauteur[xx][zz], 0.0f);
              glVertex3f((float)xx, hauteur[xx][zz], (float)zz);
            }
          }
          else
          {
            zDebut = 0;
            zFin = LARGEUR_TERRAIN;
            nStepZ = nStep;
            for(zz = zDebut; zz  < zFin; zz += nStepZ)
            {
              glColor3f(0.0f, (float)hauteur[xx][zz], 0.0f);
              glVertex3f((float)xx, hauteur[xx][zz], (float)zz);
              glColor3f(0.0f, (float)hauteur[xx+1][zz], 0.0f);
              glVertex3f((float)xx+nStep, hauteur[xx+1][zz], (float)zz);
            }
          }
        }
      glEnd();
    glPopMatrix();
  glEndList();

  DetruireLesHauteurs(hauteur);
  // Dessin du cône
  GLfloat delta1 = M_PI/180.0f, delta2 = M_PI/180.0f;
  GLfloat x,y,angle;  // Storage for coordinates and angles
  GLfloat S, C;       // Sinus et Cosinus de l'angle
  GLfloat Aux;        // Variable auxiliaire

  glNewList(cone, GL_COMPILE);
    S = sin(delta1);
    C = cos(delta1);
    x = 0.0f;
    y = 1.0f;

    glFrontFace(GL_CW);

    // Begin a triangle fan
    glBegin(GL_TRIANGLE_FAN);
      // Pinnacle of cone is shared vertex for fan, moved up Z axis
      // to produce a cone instead of a circle
      glVertex3f(0.0f, 0.0f, 2.0f);
      glVertex2f(x, y);

      // Loop around in a circle and specify even points along the circle
      // as the vertices of the triangle fan
      for(angle = 0.0f; angle < (2.0f*M_PI); angle += (delta1))
      {
        Aux = y*C - x*S;  // cos(angle + delta)
        // Calculate x and y position of the next vertex
        x = y*S + x*C;    // sin(angle + delta)
        y = Aux;          // cos(angle + delta)

        // Specify the next vertex for the triangle fan
        glVertex2f(x, y);
      }
    // Done drawing fan for cone
    glEnd();

    S = sin(delta2);
    C = cos(delta2);
    x = 0.0f;
    y = 1.0f;

    glFrontFace(GL_CCW);
    // Begin a new triangle fan to cover the bottom
    glBegin(GL_TRIANGLE_FAN);
      // Center of fan is at the origin
      glVertex2f(0.0f, 0.0f);
      glVertex2f(x, y);
      for(angle = 0.0f; angle < (2.0f*M_PI); angle += (delta2))
      {
        // Calculate x and y position of the next vertex
        Aux = y*C - x*S;  // cos(angle + delta)
        x = y*S + x*C;    // sin(angle + delta)
        y = Aux;          // cos(angle + delta)

        // Specify the next vertex for the triangle fan
        glVertex2f(x, y);
      }

    // Done drawing the fan that covers the bottom
    glEnd();
  glEndList();
}

