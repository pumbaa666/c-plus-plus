// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"
#include <stdlib.h>

void DessinerLaScene()
{
    ModeDeDessin(Mode);

    glPushMatrix();
        glScalef(5.0, 5.0, 5.0);
        glCallList(axes);
    glPopMatrix();

    int i, nbMaison = 8;
    GLfloat angle = 0;
    for(i = 0; i < nbMaison; i++)
    {
        angle += 360.0/nbMaison;
        glPushMatrix();
            glRotatef(angle, 0.0, 1.0, 0.0);
            glTranslatef(-20, 0.0, -20);
            glRotatef(360.0/nbMaison, 0.0, 1.0, 0.0);
            glCallList(maison);

            glTranslatef(3.0, 4.5, 3.5);
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            glScalef(cheminee, cheminee, 2.0);
            glCallList(cone);
        glPopMatrix();
    }

    glPushMatrix();
        glScalef(2.0, 2.0, 2.0);
        glCallList(maison);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-100.0, 0.0, -100.0);
        glCallList(sol);
    glPopMatrix();
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

