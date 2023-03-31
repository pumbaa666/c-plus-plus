// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"

void DessinerLaScene()
{
    ModeDeDessin(Mode);

    glPushMatrix();
        glScalef(5.0, 5.0, 5.0);
        DessinerLesAxes();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5.0, 0.0, -2.0);
        DessinerLaMaison();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-100.0, 0.0, -100.0);
        DessinerLeSol();
    glPopMatrix();
}

void DessinerLesAxes()
{
    glCallList(axes);
}

void DessinerLaMaison()
{
    glCallList(maison);
}

void DessinerLeSol()
{
    glCallList(sol);
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

