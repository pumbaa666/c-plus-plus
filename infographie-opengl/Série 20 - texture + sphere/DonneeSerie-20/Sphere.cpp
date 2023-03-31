// Fichier SPHERE.CPP

#include <gl/glut.h>
#include <stdio.h>
#include "global.h"
#include "sphere.h"

//------------------------------------------------------------------------
// Fonction appel�e pour dessiner la sph�re
void DessinerLaSphere(GLfloat radius)
{
    if(radius != 1)
    {
        glScalef(radius, radius, radius);
        glEnable(GL_NORMALIZE);
        glCallList(terre);
        glDisable(GL_NORMALIZE);
    }
    else
        glCallList(terre);
}

