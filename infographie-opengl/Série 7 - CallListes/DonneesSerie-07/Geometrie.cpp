// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "global.h"

void DessinerLaScene()
{
    ModeDeDessin(Mode);
    glPushMatrix();
        glRotatef(yRot, 1.0, 0.0, 0.0);
        glRotatef(xRot, 0.0, 1.0, 0.0);
        DessinerLesAxes();
        DessinerCone();
    glPopMatrix();
}

void DessinerLesAxes()
{
    glCallList(axes);
}

void DessinerCone()
{
    glCallList(cone);
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
        glPolygonMode(GL_BACK, GL_LINE);
    else
        glPolygonMode(GL_BACK, GL_FILL);

    if(mask & bShadeModel)
        glShadeModel(GL_SMOOTH);  // Interpolation de la couleur entre les différents sommets
    else
        glShadeModel(GL_FLAT);    // La couleur du polygone est la couleur du dernier sommet (qui est aussi le premier)
}
